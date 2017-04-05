//-------------------------------------------------- 
// finiteDiff: Defines finite difference approximations. 
//
// 12/3/2016 - (gry88) Written for CSE380 final project. 
//--------------------------------------------------
#include "finiteDiff.h"
#include<gsl/gsl_vector.h>
#define _USE_MATH_DEFINES // Needed for M_PI
#include<math.h>
#include <iostream>
using namespace std;

const double remap_param = 0.97;
const double a = sin(remap_param*M_PI/2);

inline double dXidY(double xi) {
  return 2.0*a/(remap_param*M_PI*sqrt(1.0 - pow(a*remap(xi),2)));
}

inline double d2XidY2(double xi) {
  return (2.0*a*a*a*remap(xi))/
      (remap_param*M_PI*pow(1.0-pow(a*remap(xi),2),1.5));
}

inline double remap(double xi) {
  return sin(remap_param*xi*M_PI/2)/sin(remap_param*M_PI/2);
}

inline double CentralDiff2(gsl_vector * x,double deltaEta,double bdry,int i)
{
  // i = xiCounter indices
  //if i < 5 use value at boundary. 5 for the index of xi.
  if (i<5)
    return (gsl_vector_get(x,i+5) - 2*gsl_vector_get(x,i) + bdry)/pow(deltaEta,2);
  else
    return ( gsl_vector_get(x,i+5) - 2*gsl_vector_get(x,i) + gsl_vector_get(x,i-5))/pow(deltaEta,2); //i+5 corresponds to i+1 for single terms. U_2 = xi_1+5 for example.
}

inline double CentralDiff1(gsl_vector *x, double deltaEta,double bdry, int i)
{
  //same structure as above but for first derivative.
  if (i<5)
    return (gsl_vector_get(x,i+5)-bdry)/(2*deltaEta);
  else
    return (gsl_vector_get(x,i+5)-gsl_vector_get(x,i-5))/(2*deltaEta);
}

double Deriv2(gsl_vector * x,double deltaEta,double bdry,int i)
{
  double xi = -1.0+(i/5)*deltaEta;
  return d2XidY2(xi)*CentralDiff1(x, deltaEta, bdry, i) +
      pow(dXidY(xi),2)*CentralDiff2(x, deltaEta, bdry, i);
}

double Diff2(gsl_vector * x,double deltaEta,double bdry,int i)
{

	double val;
	// i = xiCounter indices
	//if i < 5 use value at boundary. 5 for the index of xi. 
	if (i<5)
		val =(gsl_vector_get(x,i+5) - 2*gsl_vector_get(x,i) + bdry)/pow(deltaEta,2);
	else
		val = ( gsl_vector_get(x,i+5) - 2*gsl_vector_get(x,i) + gsl_vector_get(x,i-5))/pow(deltaEta,2); //i+5 corresponds to i+1 for single terms. U_2 = xi_1+5 for example. 
	return val;
}

double Deriv1(gsl_vector *x, double deltaEta,double bdry, int i)
{
  double xi = -1.0+(i/5)*deltaEta;
  return CentralDiff1(x, deltaEta, bdry, i)*dXidY(xi);
}



double Diff1(gsl_vector *x, double deltaEta,double bdry, int i)
{
	//same structure as above but for first derivative. 
	double val; 
	
	if (i<5)
		val = (gsl_vector_get(x,i+5)-bdry)/(2*deltaEta);
	else
		val = (gsl_vector_get(x,i+5)-gsl_vector_get(x,i-5))/(2*deltaEta);
	return val; 
}

double BdryDiff2(gsl_vector * x ,double deltaEta,int i)
{
	//Using zero Nuemann boundary condition we use ghost points for second derivative.  
	double val = ( 2*gsl_vector_get(x,i-5) - 2*gsl_vector_get(x,i))/pow(deltaEta,2);
	return val; 
}

double Diff1vT(gsl_vector * x,double deltaEta,int i)
{
	// for vT we use normal finite difference approximation. 
	double val=  (gsl_vector_get(x,i+1) - gsl_vector_get(x,i-1))/(2*deltaEta);
	return val; 
}

