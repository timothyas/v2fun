//--------------------------------------------------
// systemSolve: Sets up system to be solved for gsl_multiroot solver. 
//
// 12/3/2016 - (gry88) Written for CSE380 final project. 
//--------------------------------------------------
#include<math.h>
#include<gsl/gsl_multiroots.h>
#include<grvy.h>
#include"computeTerms.h"
#include"systemSolve.h"
#include"finiteDiff.h"
using namespace std; 
using namespace GRVY;

// The structure of this function is fixed by the definition of gsl_multiroot solvers. 
int SysF(const gsl_vector * xi, void * p, gsl_vector * sysF)
{
	
	Log(logDEBUG2) << "Setting up system F(xi)";
	struct FParams * params = (struct FParams *)p; //reference void pointer to parameter struct; 

	int vecSize = ((xi->size))/double(5)+1;  // size of single vector. I in doc. 
	
	//first paramter must be const. But since we need do access vector, we have to define
	//a temporary vector so work with. Perhaps there is a way around this. 
	gsl_vector * tempxi = gsl_vector_alloc(xi->size);  
	gsl_vector_memcpy(tempxi,xi);

	// Enough functions need eddy viscosity so we store results, same as T.
	// Note each of the Term vectors are full size (starting at i=0)
	gsl_vector * vT = gsl_vector_calloc(vecSize);
	gsl_vector * T  = gsl_vector_calloc(vecSize);
	for (unsigned int i = 1; i<vT->size;i++)
	{
		gsl_vector_set(T,i,ComputeT(tempxi,params->modelConst,i));
		gsl_vector_set(vT,i,ComputeEddyVisc(tempxi,T,params->modelConst,i));
	}

	GRVY_Timer_Class gt; 
	gt.BeginTimer("Setting up system");
	//Set each term based on functions below. 
	if(SetUTerms(tempxi,vT,params,sysF))
	{
		Log(logERROR) << "Error setting U terms in system";
		exit(1);
	}
	if(SetKTerms(tempxi,vT,params,sysF))
	{
		Log(logERROR) << "Error setting k terms in system";
		exit(1); 
	}

	if(SetEpTerms(tempxi,vT,T,params,sysF))
	{
		Log(logERROR) << "Error setting ep terms in system";
		exit(1); 
	}

	if(SetV2Terms(tempxi,vT,params,sysF))
	{
		Log(logERROR) << "Error setting v2 terms in system";
		exit(1); 
	}

	if(SetFTerms(tempxi,vT,T,params,sysF))
	{
		Log(logERROR) << "Error setting F terms in system";
		exit(1); 
	}
	gt.EndTimer("Setting up system");
//	for(unsigned int i = 0; i<sysF->size;i++)
//	{
//		cout << gsl_vector_get(sysF,i) << endl; 
//	}
	
	gsl_vector_free(tempxi);

	return 0; 
}

int SetFTerms(gsl_vector * xi, gsl_vector * vT, gsl_vector * T, FParams * params, gsl_vector * sysF)
{
	
	Log(logDEBUG2) << "Setting f terms\n";
	double firstTerm,secondTerm,thirdTerm,fourthTerm; //terms as defined in doc.  
	double val; 
	unsigned int i; 
	unsigned int size = xi->size/float(5) + 1; //size of single vectors. Comes from old structure of code before restructure branch in git.  
	double xiCounter; 
	double f0 = Computef0(xi,params->modelConst,params->deltaEta);

	for(i = 1; i<size-1; i++)
	{
		xiCounter=5*(i-1); 
		firstTerm = -(gsl_vector_get(xi,xiCounter+4)-gsl_vector_get(params->XiN,xiCounter+4))/params->deltaT;	
		secondTerm = pow(ComputeL(xi,params->modelConst,i),2)*Diff2(xi,params->deltaEta,f0,xiCounter+4); 
		thirdTerm = params->modelConst->C2*(ComputeP(xi,vT,params->deltaEta,i)/gsl_vector_get(xi,xiCounter+1)) - gsl_vector_get(xi,xiCounter+4);     
		fourthTerm = -(params->modelConst->C1/gsl_vector_get(T,i))*( (gsl_vector_get(xi,xiCounter+3)/gsl_vector_get(xi,xiCounter+1))-float(2)/3); 
		val = firstTerm + secondTerm + thirdTerm + fourthTerm;
		if (!isfinite(val))
			return 1; 
		gsl_vector_set(sysF,xiCounter+4,val); 
		Log(logDEBUG3) << "f term = " << val<< " at " << i;
	}

	//boundary terms. 
	i=size-1;  
	xiCounter=5*(i-1); 
	firstTerm = -(gsl_vector_get(xi,xiCounter+4)-gsl_vector_get(params->XiN,xiCounter+4))/params->deltaT;	
	secondTerm = pow(ComputeL(xi,params->modelConst,i),2)*BdryDiff2(xi,params->deltaEta,xiCounter+4); 
	thirdTerm = -gsl_vector_get(xi,xiCounter+4) -(params->modelConst->C1/gsl_vector_get(T,i))*( (gsl_vector_get(xi,xiCounter+3)/gsl_vector_get(xi,xiCounter+1))-float(2)/3); 
	val = firstTerm+secondTerm+thirdTerm;
	Log(logDEBUG3) << "f term = " << val << " at " << i;
	if(!isfinite(val))
		return 1; 
	gsl_vector_set(sysF,xiCounter+4,val);
	return 0; 
}

int SetV2Terms(gsl_vector * xi,gsl_vector * vT,FParams * params, gsl_vector * sysF)
{
	
	Log(logDEBUG2) << "Setting V2 terms";
	double firstTerm,secondTerm,thirdTerm,fourthTerm;  //as defined in doc. 
	double val; 
	unsigned int i; 
	unsigned int size = xi->size/float(5)+1; 
	double xiCounter; //counter for xi vector. 

	// i loops of size of U,k,ep,v2,f. 
	for(i = 1; i<size-1; i++)
	{
		xiCounter=5*(i-1); //xiCounter is the counter for xi. 
		firstTerm = -(gsl_vector_get(xi,xiCounter+3)-gsl_vector_get(params->XiN,xiCounter+3))/params->deltaT;	
		secondTerm = gsl_vector_get(xi,xiCounter+1)*gsl_vector_get(xi,xiCounter+4) - gsl_vector_get(xi,xiCounter+2)*( ( gsl_vector_get(xi,xiCounter+3)/gsl_vector_get(xi,xiCounter+1)));
		thirdTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i))*Diff2(xi,params->deltaEta,0,xiCounter+3);
		fourthTerm = Diff1(xi,params->deltaEta,0,xiCounter+3)*Diff1vT(vT,params->deltaEta,i); 
		val = firstTerm + secondTerm + thirdTerm + fourthTerm;
		Log(logDEBUG3) << "V2 term = " << val<< " at " << i;
		if (!isfinite(val))
			return 1; 
		gsl_vector_set(sysF,xiCounter+3,val); 
	}

	// compute boundary terms. 
	i=size-1; 
	xiCounter=5*(i-1); 
	firstTerm = -(gsl_vector_get(xi,xiCounter+3)-gsl_vector_get(params->XiN,xiCounter+3))/params->deltaT;	
	secondTerm = gsl_vector_get(xi,xiCounter+1)*gsl_vector_get(xi,xiCounter+4) - gsl_vector_get(xi,xiCounter+2)*( (gsl_vector_get(xi,xiCounter+3)/gsl_vector_get(xi,xiCounter+1)));
	thirdTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i))*BdryDiff2(xi,params->deltaEta,xiCounter+3);
	val = firstTerm + secondTerm + thirdTerm;
	Log(logDEBUG3) << "V2 term = " << val<< " at " << i;
	if (!isfinite(val))
		return 1; 
	gsl_vector_set(sysF,xiCounter+3,val); 

	return 0; 
}


int SetEpTerms(gsl_vector * xi, gsl_vector * vT,gsl_vector * T,FParams * params, gsl_vector * sysF)
{
	Log(logDEBUG2) << "Setting Ep terms";
	double firstTerm,secondTerm,thirdTerm,fourthTerm;  //as defined in doc. 
	double val; 
	unsigned int i; 
	unsigned int size = vT->size;
	double xiCounter; 
	double ep0 = ComputeEp0(xi,params->modelConst,params->deltaEta); 

	//same loop as above. 
	for (i = 1; i<size-1;i++)
	{
		xiCounter=5*(i-1); 
		firstTerm = -(gsl_vector_get(xi,xiCounter+2)-gsl_vector_get(params->XiN,xiCounter+2))/params->deltaT;	
		secondTerm = (params->modelConst->Cep1*ComputeP(xi,vT,params->deltaEta,i) - params->modelConst->Cep2*gsl_vector_get(xi,xiCounter+2))/gsl_vector_get(T,i); 
		thirdTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i)/params->modelConst->sigmaEp)*Diff2(xi,params->deltaEta,ep0,xiCounter+2);
		fourthTerm = (1/params->modelConst->sigmaEp)*Diff1(xi,params->deltaEta,ep0,xiCounter+2)*Diff1vT(vT,params->deltaEta,i); 
		val = firstTerm + secondTerm + thirdTerm + fourthTerm;
		Log(logDEBUG3) << "Ep term = " << val << " at " << i;
		if (!isfinite(val))
			return 1; 
		gsl_vector_set(sysF,xiCounter+2,val); 
	}

	i=size-1;  
	xiCounter=5*(i-1); 
	firstTerm = -(gsl_vector_get(xi,xiCounter+2)-gsl_vector_get(params->XiN,xiCounter))/params->deltaT;	
	secondTerm = - (params->modelConst->Cep2*gsl_vector_get(xi,xiCounter+2))/gsl_vector_get(T,i); 
	thirdTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i)/params->modelConst->sigmaEp)*BdryDiff2(xi,params->deltaEta,xiCounter+2);
	val = firstTerm + secondTerm + thirdTerm;
	Log(logDEBUG3) << "Ep term = " << val << " at " << i;
	if (!isfinite(val))
		return 1; 
	gsl_vector_set(sysF,xiCounter+2,val);
	return 0; 
}


int SetKTerms(gsl_vector * xi, gsl_vector* vT,FParams * params,gsl_vector *sysF)
{
	Log(logDEBUG2) <<"Setting K terms";
	double firstTerm, secondTerm,thirdTerm,fourthTerm;  //as in doc. 
	double val; 
	unsigned int i;  
	unsigned int size=vT->size; 
	double xiCounter; 
	//same loops as above. 
	for(i=1; i<size-1;i++)
	{
		xiCounter=5*(i-1);
		firstTerm = -(gsl_vector_get(xi,xiCounter+1)-gsl_vector_get(params->XiN,xiCounter+1))/params->deltaT;	
		secondTerm = ComputeP(xi,vT,params->deltaEta,i)-gsl_vector_get(xi,xiCounter+2); 
		thirdTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i))*Diff2(xi,params->deltaEta,0,xiCounter+1); 
		fourthTerm = Diff1(xi,params->deltaEta,0,xiCounter+1)*Diff1vT(vT,params->deltaEta,i); 
		val = firstTerm + secondTerm + thirdTerm + fourthTerm; 
		Log(logDEBUG3) << "K term = " << val<< " at "<<i;
		if(!isfinite(val))
			return 1; 
		gsl_vector_set(sysF,xiCounter+1,val); 
	}

	i = size-1;  
	xiCounter = 5*(i-1); 
	firstTerm = -(gsl_vector_get(xi,xiCounter+1)-gsl_vector_get(params->XiN,xiCounter+1))/params->deltaT;	
	secondTerm = -gsl_vector_get(xi,xiCounter+2); 
	thirdTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i))*BdryDiff2(xi,params->deltaEta,xiCounter+1); 
	val = firstTerm+secondTerm+thirdTerm; 
	Log(logDEBUG3) << "K term = " << val<< " at "<<i;
	if(!isfinite(val))
		return 1; 
	gsl_vector_set(sysF,xiCounter+1,val); 
	return 0; 

}

int SetUTerms( gsl_vector * xi, gsl_vector * vT, FParams * params,gsl_vector * sysF)
{
	Log(logDEBUG2) << "Setting U terms";
	//same structure as other functions. 
	double firstTerm, secondTerm, thirdTerm;
	double val; 
	unsigned int i; 
	unsigned int size=vT->size; 
	double xiCounter;

	for(i=1; i<size-1; i++)
	{
		xiCounter = 5*(i-1);

		firstTerm = -(gsl_vector_get(xi,xiCounter)-gsl_vector_get(params->XiN,xiCounter))/params->deltaT;	
		secondTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i))*Diff2(xi,params->deltaEta,0,xiCounter);
		thirdTerm = Diff1(xi,params->deltaEta,0,xiCounter)*Diff1vT(vT,params->deltaEta,i);
		val = firstTerm + secondTerm + thirdTerm+1;  
		Log(logDEBUG3) << "U term = " << val << " at " << i;
		if(!isfinite(val))
			return 1; 
		gsl_vector_set(sysF,xiCounter,val);
	}

	i =size-1; 
	xiCounter = 5*(i-1); 
	firstTerm = -(gsl_vector_get(xi,xiCounter)-gsl_vector_get(params->XiN,xiCounter))/params->deltaT;	
	secondTerm = (1/params->modelConst->reyn + gsl_vector_get(vT,i))*BdryDiff2(xi,params->deltaEta,xiCounter);
	val = firstTerm+secondTerm + 1; 
	Log(logDEBUG3) << "U term = " << val << " at " << i;
	if(!isfinite(val))
		return 1; 
	gsl_vector_set(sysF,xiCounter,val); 	
	return 0; 
}


