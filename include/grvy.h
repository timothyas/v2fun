// -*-c++-*-
//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// libGRVY - a utility library for scientific computing.
//
// Copyright (C) 2008,2009,2010,2011,2012 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, 
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
//
// grvy.h: Basic API Definitions
//
// $Id: grvy.h.in 30237 2012-05-23 03:43:14Z karl $
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#include<stddef.h>

#ifndef GRVY_H_
#define GRVY_H_

/** \file 
 *
 * This section outlines the available GRVY functions for C/C++.  To
 * access, make sure to \#include <grvy.h> within your source code
 * files. Several simple examples using these functions are provided
 * in the examples section.  Unless specified otherwise, functions
 * which have an integer return value return "0" upon success (and the
 * primary excepton to this rule is with a subset of the Input Parsing
 * routines).    <hr>
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/** \cond */

/* Library version/build information */

#define GRVY_MAJOR_VERSION  0
#define GRVY_MINOR_VERSION  32
#define GRVY_MICRO_VERSION  0

#define GRVY_BUILD_USER     "clarkp"
#define GRVY_BUILD_ARCH     "x86_64-unknown-linux-gnu"
#define GRVY_BUILD_HOST     "knossos.ices.utexas.edu"
#define GRVY_BUILD_DATE     "2017-04-04 11:44"
#define GRVY_BUILD_VERSION  "Unversioned directory"

#define GRVY_LIB_VERSION    "0.32.0"
#define GRVY_LIB_RELEASE    "Development Build"

#define GRVY_CXX            "g++"
#define GRVY_CXXFLAGS       "-g -O2"

#define GRVY_FC             "gfortran"
#define GRVY_FCFLAGS        "-g -O2"

/** \endcond */

  /** @defgroup Capi C API
   *
   * \brief This page provides links to all of the C style utilities which
   * are available in libGRVY (organized by functionality). To access
   * these routines from C/C++, make sure to \#include <grvy.h> within
   * your source code files. Unless specified otherwise, functions
   * which have an integer return value return "0" upon success (and
   * the primary exception to this rule is with a subset of the Input
   * Parsing routines).
   * 
   * Click on one of the links below to see more details on the routines
   * available for each utility. Alternatively, if you prefer to see
   * all of the available routines as part of the C API on a single
   * page, refer to the header file, grvy.h directly.
   *
   * \li \ref Cinput
   * \li \ref Ctimer
   * \li \ref Cmath
   * \li \ref Clog
   * \li \ref Cmisc
   * \li \ref Cocore
   * \li \ref Cversioning
   *
   */

  //-----------------------------------------------------------------
  // Versioning Utilities
  //-----------------------------------------------------------------

  /**
   * @defgroup Cversioning Runtime Versioning Information
   * @ingroup Capi 
   * @ingroup CXXapi 
   * 
   * \brief Obtain libGRVY runtime versioning information.
   */

  /**
   * \ingroup Cversioning
   * \name Versioning Routines:
   *
   * Obtain libGRVY runtime versioning information.
   */

  /** 
   * \ingroup Cversioning 
   * @{
   */

  /** \brief Echo library versioning and configuration information to stdout */

  extern void grvy_version_stdout           ();

  /**
   * \brief Obtain numeric library version 
   * \return running version
   */

  extern int grvy_get_numeric_version       ();

  /** @} */  

  //-----------------------------------------------------------------
  // Input Parsing Utilities
  //-----------------------------------------------------------------

  /** 
   * \defgroup Cinput Input Parsing
   * @ingroup Capi
   *
   * \brief This section presents available C routines for accessing
   * input parameters from a libGRVY style input file. See the \ref
   * inputFile "example input file" for more information on the file
   * format. Unless specified otherwise, functions which have an
   * integer return value return "0" upon success. The primary
   * exception to this rule is with the read() routines.  All
   * grvy_input_fread_() routines return 1 on success and 0 on failure.
   * This return behavior is intended as a convenience for
   * applications to check input file parsing errors over consecutive
   * reads via multiplicative operations.
   *
   * <b> Code Example:</b> A specific C example using the input parsing
   * routines is available in \ref CinputExample "input.c".
   * <hr>
   */

  /** 
   * \ingroup Cinput
   * \name Input Parsing - File open/close:
   *
   * Routines for accessing input parameters from a libGRVY style
   * input file. Note that an input file must be opened prior to reading
   * any keyword/value pairs or performing input file dump
   * operations. 
   *
   */

  /**
   * \ingroup Cinput
   * @{ 
   */

  /**
   * \brief Open a libGRVY style input file
   * \param filename desired input filename
   */

  extern int grvy_input_fopen               (const char *filename);

  /** \brief Close the currently open libGRVY style input file */

  extern int grvy_input_fclose              ();

  /** @} */

  /** \ingroup Cinput
   *  \name Input Parsing - Dump input file contents:
   * 
   * The following routines are used to dump the entire contents of
   * a parsed libGRVY style input file to stdout or to an ASCII file
   * (note that all comments within the original input file are
   * stripped). The prefix variable can be used to include an
   * additional delimiter which prepends each line of the output. Note
   * that an input file must be open prior to reading any performing
   * input file dump operations. These routines are normally used to
   * save all relevant input parameters in the application output for
   * future traceability and repeatability.
   *
   */

  /** \ingroup Cinput
   * @{
   */

  /** \brief Dump input file settings to stdout. */

  extern int grvy_input_fdump               ();

  /** \brief Dump input file settings to stdout prefixed by a delimiter */

  extern int grvy_input_fdump_delim         (const char* prefix);

  /** \brief Dump input file settings to an open file with a provided prefix delimiter */

  extern int grvy_input_fdump_file          (const char* prefix, const char *filename);

  /** @} */

  /** \ingroup Cinput
   *  \name Input Parsing - Read scalar values:
   *
   * The following routines are used to read individual input values
   * for common intrinsic datatypes given a desired keyword character
   * string (keyword).  All grvy_input_fread_() routines return 1 on sucess and 0
   * on failure.  This return behavior is intended as a convenience
   * for applications to check input file parsing errors over consecutive reads
   * via multiplicative operations. 
   * 
   */


  /** \ingroup Cinput
   * @{
   */

   /** \brief Read a single input integer \e value corresponding to the \e keyword path
    *  \param keyword input keyword path
    *  \param corresponding value in input file
    */

   extern int grvy_input_fread_int           (const char* keyword, int *value);

   /** \brief Read a single input float \e value corresponding to the \e keyword path
    *  \param keyword input keyword path
    *  \param corresponding value in input file
    */

   extern int grvy_input_fread_float         (const char* keyword, float *value);

   /** \brief Read a single input double \e value corresponding to the \e keyword path
    *  \param keyword input keyword path
    *  \param corresponding value in input file
    */

   extern int grvy_input_fread_double        (const char* keyword, double *value);

   /** \brief Read a single input character string \e value
    * corresponding to the \e keyword path.  For convenience, libGRVY
    * will allocate memory for the the character string based on the
    * size of the string present in the input file (including null
    * terminator). 
    *
    *  \param keyword input keyword path
    *  \param corresponding value in input file
    */

   extern int grvy_input_fread_char          (const char* keyword, char **value);

  /** @} */

  /** 
   * \ingroup Cinput
   * \name Input Parsing - Read vector values:
   *
   * The following routines are used to read vector valued input
   * values for common intrinsic datatypes given a desired keyword
   * character string (\e keyword).  If successful, the resulting data
   * is stored in the array \e values.
   */

  /** \ingroup Cinput
   * @{
   */

  /** \brief Read an integer array of size \e nelems corresponding to
   * the \e keyword path.
   */

  extern int grvy_input_fread_int_vec       (const char* keyword, int *values,    int nelems);

  /** \brief Read a float array of size \e nelems corresponding to
   * the \e keyword path.
   */

  extern int grvy_input_fread_float_vec     (const char* keyword, float *values,  int nelems);

  /** \brief Read a double array of size \e nelems corresponding to
   * the \e keyword path.
   */

  extern int grvy_input_fread_double_vec    (const char* keyword, double *values, int nelems);

  /** \brief Read a character array of size \e nelems corresponding to
   * the \e keyword path.
   */

  extern int grvy_input_fread_char_ivec     (const char* keyword, char **values,  int elem);


  /** @} */  

  /** \ingroup Cinput
   *  \name Input Parsing - Read ith vector values:
   *
   * The following routines are used to read the ith entry (\e elem)
   * of vector valued input values for common intrinsic datatypes
   * given a desired keyword character string (\e keyword). If
   * successful, the resulting data is stored in \e value.
   */

  /** \ingroup Cinput
   * @{
   */

  /** \brief Read the ith entry (\e elem) from an array of integers
      corresponding to the \e keyword path.
   */

  extern int grvy_input_fread_int_ivec      (const char* keyword, int *value,    int elem);

  /** \brief Read the ith entry (\e elem) from an array of doubles 
      corresponding to the \e keyword path.
   */

  extern int grvy_input_fread_float_ivec    (const char* keyword, float *value,  int elem);

  /** \brief Read the ith entry (\e elem) from an array of doubles
      corresponding to the \e keyword path.
   */

  extern int grvy_input_fread_double_ivec   (const char* keyword, double *value, int elem);

  /** @} */

  /** 
   * \ingroup Cinput 
   * \name Input Parsing  - Default value registration:
   *
   * The following routines provide a mechanism to register a default
   * value with the input parsing mechanism. If a particular \e keyword
   * has a registered default value and is subsequently queried
   * with an input file which does not contain the keyword, the
   * registered default value will be returned instead. A convenient
   * use for these registration functions is to provide sensible
   * defaults to newly added input keywords which are not present in
   * older input file revisions.
   */

  /** \ingroup Cinput
   * @{
   */

  /** \brief Register default integer \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_int        (const char *keyword,     int value);

  /** \brief Register default float \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_float      (const char *keyword,   float value);

  /** \brief Register default double \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_double     (const char *keyword,  double value);

  /** \brief Register default character string \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_char       (const char *keyword,   char *value);

  /** @} */

  /** 
   * \ingroup Cinput 
   * \name Input Parsing  - Default registration query:
   *
   * The following routines can be used to query the current hashed
   * values of any keyword variables which have been registered
   * previously.
   */

  /** \ingroup Cinput
   * @{
   */

   /** \brief Retrieve registered default integer \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_get_int    (const char *keyword,    int *value);

  /** \brief Retrieve registered default float \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_get_float  (const char *keyword,  float *value);

  /** \brief Retrieve registered default double \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_get_double (const char *keyword, double *value);

  /** \brief Retrieve registered default character string \e value corresponding to the \e keyword path. */
  extern int grvy_input_register_get_char   (const char *keyword,  char **value);

  /** @} */

  //-----------------------------------------------------------------
  // Performance Timer Utilities
  //-----------------------------------------------------------------

  /** \defgroup Ctimer Performance Timer Utilities 
   *  \ingroup Capi
   *
   * \brief This section presents available C routines for measuring
   * runtime performance of specific code sections to aid in overall
   * performance/statistical analysis, and to maintain historical
   * performance records as application codes evolve or across
   * alternate compute platforms.  Individual code timers are defined
   * based on begin/end demarcation around the desired code snippet to
   * measure along with a unique user-provided id string. Note that
   * individual timers can be nested and the library will report
   * exclusive timing of the innermost timers. Various options are
   * provided to interrogate timer measurements, statistics, and
   * relative timer comparisons. A convenient use of these routines is
   * to define timers around various important work constructs within
   * your application and use the grvy_timer_summarize() function to
   * obtain a concise summary of the runtime performance, variability,
   * and relative wallclock comparisions. Example output using this
   * approach is shown below:
   *
   *  \code 
   * -----------------------------------------------------------------------------------------------
   * GRVY Example Timing - Performance Timings:              |      Mean      Variance       Count
   * --> foo                 : 3.00978e+00 secs ( 64.0889 %) | [3.00978e-01  2.70727e-08         10]
   * --> boo                 : 1.17648e+00 secs ( 25.0513 %) | [1.17648e-01  2.35981e-08         10]
   * --> bar                 : 5.09513e-01 secs ( 10.8493 %) | [5.09513e-02  5.02795e-08         10]
   * --> Main Program        : 4.48704e-04 secs (  0.0096 %) | [4.48704e-04  0.00000e+00          1]
   * --> GRVY_Unassigned     : 4.02927e-05 secs (  0.0009 %)
   * 
   *     Total Measured Time = 4.69626e+00 secs (100.0000 %)
   * -----------------------------------------------------------------------------------------------
   *  \endcode
   *
   * <b> Code Example</b>: A specific C example using the performance timing
   * routines is available in \ref CtimerExample "timer.c".
   *
   * <hr>
   */

  /**
   * \ingroup Ctimer
   * \name Performance Timer - Initialization and Timer Demarcation:
   *
   * The following routines provide support for defining one or more
   * wall-clock timers around specific code regions. Individual timers are
   * delineated by a unique \e id.  In addition to timing specific code
   * regions identified with begin/end calls, the library also
   * tracks the total application time from when the timing library
   * was first initialized.
   */

  /** \ingroup Ctimer
   * @{
   */

  /** \brief Initialize timer library with a \e description string
      which initiates the global timing process (the description
      string is used to customize grvy_timer_summarize() output). Note
      that you are not required to call this function prior to
      defining specific timers.  If you do not specificaly call
      grvy_timer_init(), then the global timer will begin on the first
      call to grvy_timer_begin() (and a default description string
      will be defined).
   */

  extern   void grvy_timer_init                (const char *description);

  /** \brief Identify beginning of code section to time with unique \e id string. */
  extern   void grvy_timer_begin               (const char *id);

  /** \brief Identify end of code section to time with a matching \e id string. */
  extern   void grvy_timer_end                 (const char *id);

  /** \brief Resets all actively defined timers (accumulated time and
   *  calling statistics are reinitialized). */
  extern   void grvy_timer_reset               ();

  /** \brief Finalize global timing process - stops the active global timer */
  extern   void grvy_timer_finalize            ();

  /** \brief Basic wallclock timer which provides the time since epoch in seconds.
   * \return time since epoch in seconds
   */

  extern double grvy_timer                     ();

  /** @} */

  /**
   * \ingroup Ctimer
   * \name Performance Timer - Query Tools:
   *
   * The following routines allow for the querying of defined
   * performance timers.
   */

  /**
   * \ingroup Ctimer
   * @{ */

  /** \brief Returns total elapsed time (in seconds) for defined timer \e id */
  extern double grvy_timer_elapsedseconds      (const char *id);
  /** \brief Returns total elapsed time (in seconds) for the global timer */
  extern double grvy_timer_elapsed_global      ();
  /** \brief Returns the total number of timer calls for defined timer \e id */
  extern    int grvy_timer_stats_count         (const char *id);
  /** \brief Returns the mean value (in seconds) for defined timer \e id */
  extern double grvy_timer_stats_mean          (const char *id);
  /** \brief Returns the variance for defined timer \e id */
  extern double grvy_timer_stats_variance      (const char *id);
  /** \brief Returns the minimum measured timing (in seconds) for defined timer \e id */
  extern double grvy_timer_stats_min           (const char *id);
  /** \brief Returns the largest measured timing (in seconds) for defined timer \e id */
  extern double grvy_timer_stats_max           (const char *id);


  /** \brief 
   *  Print a concise summary of all defined timers to
   *  stdout. This routine shows the relative runtime percentages
   *  between all defined timers along with statistics for each
   *  timer. Global time that is not associated with any
   *  user-defined timers is associated with an unassigned timer
   *  (GRVY_Unassigned).
  */

  extern   void grvy_timer_summarize           ();

  /** \brief Set max allowed width of grvy_timer_summarize()
  * output. The normal default is to limit output width to 120
  * characters which can truncate long \e description strings provided
  * to grvy_timer_init().  This routine can be used to customize
  * the max output width as desired.
  */

  int grvy_timer_set_summarize_width (const int maxwidth);

  /** @} */

  /**
   * \ingroup Ctimer
   * \name Performance Timing - Historical Logging:
   *
   * These routines provide support to store measured runtime
   * performance into an HDF5 file for logging purposes (this
   * functionality requires HDF5 library linkage during the libGRVY
   * configuration phase). Results are stored on a per-machine basis
   * and are appended to the HDF5 file with timestamps to document
   * historical performance over time.  Stored results can be
   * retrieved using the API below or via standalone executables
   * installed with libGRVY.
   * 
   * There are two primary modes for saving historical performance
   * data:
   * 
   * <b>Mode 1</b>: you are using the grvy_timer_* class of routines to
   *         define individual sections to monitor and want to save
   *         the global runtime measurement along with all individually
   *         defined subtimers.
   * 
   * <b>Mode 2</b>: you are using other means to profile the application code
   *         and want to save a single global timing value. Routines
   *         for this mode are distinguished by the presence of an
   *         extra "timing" argument in the calling sequence.
   * 
   * In both modes, standard and expanded (exp) calling sequences are supported
   * with the expanded version allowing additional optional runtime
   * documentation (e.g. flops, code revision) to be provided.
   * 
   */
  
  // Mode 1: Saving internal GRVY timer values to historical repository

  /** \ingroup Ctimer
   * @{
   */

  /** \brief Save current libGRVY timing results to HDF file for logging. */
  extern    int grvy_timer_save_hist         (const char *experiment_name, const char *comment, 
					      int num_procs, const char *filename);

  /** \brief Save current libGRVY timing results to HDF file for logging (expanded version). */	
				
  extern    int grvy_timer_save_hist_exp     (const char *experiment_name, const char *comment, 
					      int num_procs, int jobId, const char *code_revision, 
					      double flops, const char *filename);
					      
  // Mode 2: Saving external user-provided global timing to historical repository

  /** \brief Save a single \e timing result to HDF file for logging. */	

  extern    int grvy_timer_save_hist_ext     (double timing, const char *machinename,const char*experiment, 
					      const char *comment,int num_procs, const char *filename);

  /** \brief Save a single \e timing result to HDF file for logging (expanded version).. */	
					      
  extern    int grvy_timer_save_hist_ext_exp (double timing, const char *machinename, const char*experiment, 
					      const char *comment, int num_procs, int jobId, 
					      const char *code_revision, double flops, const char *filename);

  /** \brief Summarize and dump historical timing information to ascii
   * files from logged results stored previously in \e
   * filename. Timing data is dumped to files individual on a per-machine basis in the \e
   * outdir directory using the provided \e delimiter.
   */

  void grvy_summarize_hist_timing            (const char *filename, const char *delimiter, 
					      const char *outdir);

  /** @} */

  //-----------------------------------------------------------------
  // MPI Out-of-Core Utilities
  //-----------------------------------------------------------------

  /** \defgroup Cocore MPI Out-of-Core Utilities 
   *  \ingroup Capi
   *
   * \brief Routines to offload out-of-core read/write operations to a
   * pool of distributed shared-memory nodes using MPI for data
   * transfer.  An additional level of indirection can be enabled to
   * offload less-frequently accessed data to one or more disk-based files.
   */

  /** 
   * \ingroup Cocore
   * \name MPI Out-of-Core - Initialization and runtime queries:
   *
   * Routines to initialize/finalize out-of-core suport (requires MPI
   * enabled libGRVY build) and runtime utilities.
   */

  /** \ingroup Cocore 
   * @{ 
   */
      
  extern    int grvy_ocore_init                (const char *input_file);
  extern   void grvy_ocore_finalize            ();

  extern    int grvy_ocore_master              ();
  extern    int grvy_ocore_enabled             ();
  extern    int grvy_ocore_blocksize           ();
  extern size_t grvy_ocore_num_active          ();

  /** @}
   *
   * \ingroup Cocore 
   * \name MPI Out-of-Core - Read/Write:
   *
   * Routines to read and write blocks of data to remote memory pools
   * for standard intrinsic datatypes.
   *
   */

  /** \ingroup Cocore
   * @{
   */

  extern    int grvy_ocore_write_double        (size_t record_id,    double     *data);
  extern    int grvy_ocore_write_float         (size_t record_id,     float     *data);
  extern    int grvy_ocore_write_int           (size_t record_id,       int     *data);
  extern    int grvy_ocore_write_int64         (size_t record_id, long long int *data);

  extern    int grvy_ocore_read_double         (size_t record_id,    double     *data);
  extern    int grvy_ocore_read_float          (size_t record_id,     float     *data);
  extern    int grvy_ocore_read_int            (size_t record_id,       int     *data);
  extern    int grvy_ocore_read_int64          (size_t record_id, long long int *data);

  /** @}
   * \ingroup Cocore
   * \name MPI Out-of-Core - Record retreival:
   * 
   * Routines to query the state of an existing remote out-of-core
   * memory pool and read the next available record.  These routines
   * are primarily used to save the state to disk.
   */

  /** \ingroup Cocore
   * @{ */

  extern size_t grvy_ocore_pop_record_float         (        float *data);
  extern size_t grvy_ocore_pop_record_double        (       double *data);
  extern size_t grvy_ocore_pop_record_int           (          int *data);
  extern size_t grvy_ocore_pop_record_int64          (long long int *data);

  /** @} */
					      
  //-----------------------------------------------------------------
  // Floating-Point Utilities
  //-----------------------------------------------------------------

  /** 
   * \defgroup Cmath Floating-Point Math Utilities 
   * \ingroup  Capi
   * 
   * \brief Routines for detecting floating-point errors.
   */

  /**
   * \ingroup Cmath
   * \name Floating-Point Utilities
   *
   * Routines for detecting floating-point errors. Return value is set
   * to 1 if the input \value matches the requested floating point
   * exception.
   */

  /** \ingroup Cmath
   * @{ 
   */

  /** \brief Check if input double \e value is not a number (NaN) */
  extern int grvy_double_isnan            (double *value);
  /** \brief Check if input double \e value is infinite (Inf) */
  extern int grvy_double_isinf            (double *vauel);
  /** \brief Check if input float \e value is not a number (NaN) */
  extern int grvy_float_isnan             (float  *value);
  /** \brief Check if input float \e value is infinite (Inf) */
  extern int grvy_float_isinf             (float  *value);

  /** @} */

  //-----------------------------------------------------------------
  // Logging Utilities
  //-----------------------------------------------------------------

  /**
   * \defgroup Clog Logging Utilities
   * \ingroup Capi
   *
   * \brief This section highlights available C logging routines that
   * provide a priority-based printf style logging mechanism to
   * control application messages.  A set of default priority
   * definitions are provided to define messages at various priority
   * levels. Available priority levels are enumerated as follows:
   *
   * - GRVY_NOLOG
   * - GRVY_FATAL
   * - GRVY_ERROR
   * - GRVY_WARN 
   * - GRVY_INFO 
   * - GRVY_DEBUG
   * - GRVY_ALL
   *
   * <b> Code Example:</b> A specific C example illustrating priority logging usage
   * is available in \ref CloggingExample "messages.c".
   * 
   * <hr>
   */

  /** \cond */

  /* Available logging priorities; roughly mimics syslog priority levels.
   * Also provides a NOLOG option to disable all log messages. 
   */

  typedef enum {GRVY_NOLOG  =  -1,
		GRVY_FATAL  =   0,
		GRVY_ERROR  = 100,
		GRVY_WARN   = 200,
		GRVY_INFO   = 300,
		GRVY_DEBUG  = 400,
		GRVY_ALL    = 500
  } PriorityLevel;

  /** \endcond */

  /**
   * \ingroup Clog
   * \name Logging Utilities
   *
   * Logging utilities. Note that the default logging priority is set to GRVY_ERROR.
   */

  /** \ingroup Clog
   * @{ */

  /** \brief Set current logging priority level */
  extern void grvy_log_setlevel           (int priority);
  /** \brief Get current logging priority level */
  extern int  grvy_log_getlevel           ();
  /** \brief Set logging mask \e delimiter which prepends messages of \e loglevel priority */
  extern void grvy_log_setmask            (int loglevel, const char *delimiter);
  /** \brief Post log message at \e loglevel priority using printf() style formatting */
  extern  int grvy_printf                 (int loglevel, const char *format,...);

  /** @} */

  /** 
   * \defgroup Cmisc Miscellaneous File Path Utilities
   * \ingroup Capi
   * \ingroup CXXapi
   * 
   * \brief I/O utilities for file path interaction.
   */

  /**
   * \ingroup Cmisc
   * \name Miscellaneous File Path Utilities
   *
   * I/O Utilities for directory creation and various copy utilities.
   * These routines all return 0 on success.
   */

  /** \ingroup Cmisc
   * @{ */

  /**
   * \brief Checks a desired output \a pathname and creates any non-existing
   * parent directories.  The Unix pathname to check can be a relative
   * or absolute path.
   *
   * \param[in] pathname.
   * \return \c 0 if succeeds.
   *
   */

  extern int  grvy_check_file_path        (const char *pathname);

  /** 
   * \brief Creates a new, unique directory with 0700 permissions using the
   * provided \a name_template.  The last six characters of \e name_template
   * must be XXXXXX, and \a name_template is modified with the unique
   * name upon return.
   *
   * \param[in,out] name_template. 
   * \return \c 0 if succeeds.
   */

  extern int  grvy_create_unique_dir      (      char *name_template);

  /** 
   * \brief Identical to grvy_create_unique_dir(), except that the new directory and
   * all of its contents are deleted when the process exits.
   * 
   * \param[in,out] name_template. 
   * \return \c 0 if succeeds.
   */

  extern int  grvy_create_scratch_dir     (      char *name_template);

  /** 
   * \brief Recursively copies contents of existing directory
   * (\a from_dir) to a new directory (\a to_dir).  If \a to_dir does not
   * exist, it will be created; otherwise it must be empty.
   * 
   * \param[in] from_dir
   * \param[in] to_dir
   * \return \c 0 if succeeds.
   */

  extern int  grvy_copy_dir              (const char *from_dir, const char *to_dir);

  /** @} */

  /*
   * Doxygen API Definitions
   */

  /*! \page apiC
   * \section input Input Parsing Routines
   *
   * <b>Open/close a libGRVY style input file:</b>
   * \code
   * int grvy_input_fopen               (const char *filename);
   * int grvy_input_fclose              ();
   * \endcode
   *
   * <b> Dump the contents of a libGRVY style input file :</b>
   * 
   * The following routines can be used to dump the entire contents of
   * a parsed libGRVY style input file to \e stdout or to an ASCII
   * file (note that all comments within the original input file are
   * stripped). The prefix variable can be used to include an
   * additional delimiter which prepends each line of the output.
   * These routines are normally used to save all relevant input
   * parameters in the application output for future traceability and
   * repeatability.
   *
   * \code
   * int grvy_input_fdump               ();
   * int grvy_input_fdump_delim         (const char* prefix);
   * int grvy_input_fdump_file          (const char* prefix, const char *filename);
   * \endcode
   *
   * <b>Read a single int, float, double, or char string for input keyword \e var:</b>
   * \code
   * int grvy_input_fread_int           (const char* var, int    *value);
   * int grvy_input_fread_float         (const char* var, float  *value);
   * int grvy_input_fread_double        (const char* var, double *value);
   * int grvy_input_fread_char          (const char* var, char  **value);
   * \endcode
   *
   * <b>Read a vector of ints, floats, or doubles for input keyword \e var:</b>
   * \code
   * int grvy_input_fread_int_vec       (const char* var, int    *value, int nelems);
   * int grvy_input_fread_float_vec     (const char* var, float  *value, int nelems);
   * int grvy_input_fread_double_vec    (const char* var, double *value, int nelems);
   * \endcode
   *
   * <b>Read the \e ith entry (elem) of a vector of ints, floats,
   * doubles, or characters for input keyword \e var:</b>
   *
   * \code
   * int grvy_input_fread_int_ivec      (const char* var, int *value,    int elem);
   * int grvy_input_fread_float_ivec    (const char *var, float *value,  int elem);
   * int grvy_input_fread_double_ivec   (const char* var, double *value, int elem);
   * int grvy_input_fread_char_ivec     (const char* var, char **value,  int elem);
   * \endcode
   *
   * <b> Support for the creation of backwards compatible input files:</b>
   *
   * The following routines provide a mechanism to register a default
   * value with the input parsing mechanism.  If a particular keyword
   * (\e var) has a registered default value and is subsequently
   * queried with an input file which does not contain the keyword, the
   * registered default value will be returned instead.  A convenient
   * use for these registration functions is to provide sensible
   * defaults to newly added input keywords which are not present in
   * older input file revisions.
   *
   * \code
   * int grvy_input_register_int        (const char *var,     int value);
   * int grvy_input_register_float      (const char *var,   float value);
   * int grvy_input_register_double     (const char *var,  double value);
   * int grvy_input_register_char       (const char *var,   char *value);
   * \endcode
   *
   * The following routines can be used to query the current hashed
   * values of any keyword variables which have been registered
   * previously.
   *
   * \code
   * int grvy_input_register_get_int    (const char *var,    int *value);
   * int grvy_input_register_get_float  (const char *var,  float *value);
   * int grvy_input_register_get_double (const char *var, double *value);
   * int grvy_input_register_get_char   (const char *var,  char **value);
   * \endcode
   *
   * \section timing Performance Timing Routines
   * \code
   * double grvy_timer                  ();
   * void   grvy_timer_init             (const char *id);
   * void   grvy_timer_reset            ();
   * void   grvy_timer_finalize         ();
   * void   grvy_timer_begin            (const char *id);
   * void   grvy_timer_end              (const char *id);
   * double grvy_timer_elapsedseconds   (const char *id);
   * double grvy_timer_elapsed_global   ();
   * void   grvy_timer_summarize        ();
   *
   *    int grvy_timer_stats_count      (const char *id);
   * double grvy_timer_stats_mean       (const char *id);
   * double grvy_timer_stats_variance   (const char *id);
   * \endcode

   * \section logging Logging Utilities
   *
   * The following routines provide a priority-based logging mechanism
   * to control application messages.  A set of default priority definitions are
   * provided to define messages of the following form:
   *
   * - GRVY_FATAL
   * - GRVY_ERROR
   * - GRVY_WARN 
   * - GRVY_INFO 
   * - GRVY_DEBUG
   *
   * The suggested usage of the logging mechanism is to use the
   * following routine to generate messages as opposed to writing to \e stdout
   * or \e stderr directly.  Note that to use, each message must also be assigned a 
   * priority loglevel (e.g. GRVY_WARN).
   *
   * \code void grvy_log                    (int loglevel, const char *mesg); \endcode
   * 
   * For finer control over log messages, a printf style logger is
   * available which follows the normal printf() variable argument
   * list calling sequence with the addition of a priority loglevel.
   *
   * \code int grvy_printf                  (int loglevel, const char *format,...); \endcode
   *
   * Additional type-specific functions are also available for
   * convenience to include intrinsic values (and a calling function
   * name) within the log message.
   *
   * \code
   * void grvy_log_int                (int loglevel, const char *func, const char *mesg, int var);
   * void grvy_log_float              (int loglevel, const char *func, const char *mesg, float var);
   * void grvy_log_double             (int loglevel, const char *func, const char *mesg, double var);
   * void grvy_log_char               (int loglevel, const char *func, const char *mesg, const char *char_item);
   * \endcode
   * 
   * The verbosity of the application output can then be controlled by
   * setting the current loglevel as desired (for example, the
   * GRVY_INFO mode would show all messages except those set to the
   * GRVY_DEBUG loglevel).  The default loglevel is set to GRVY_ERROR
   * but can be altered via the following:
   *
   * \code void grvy_log_setlevel           (int priority);\endcode
   *
   * Note that two additional default priority loglevels exist,
   * GRVY_NOLOG and GRVY_ALL which can be used to disable or enable
   * all log output, respectively.
   *
   * \section math Math Utilities
   * 
   * The following routines provide unified floating-point checks for NANs and INFs.
   *
   * \code
   * int grvy_double_isnan              (double *val);
   * int grvy_double_isinf              (double *val);
   *   				  
   * int grvy_float_isnan               (float  *val);
   * int grvy_float_isinf               (float  *val);
   * \endcode
   *
   */

#ifdef __cplusplus
}

/// @defgroup CXXapi C++ API
/// 
/// \brief This page provides links to all of the C++ utilities which
/// are available in libGRVY (organized by functionality). To access
/// these routines from C++, make sure to \#include <grvy.h> within
/// your source code files. Unless specified otherwise, functions
/// which have an integer return value return "0" upon success (and
/// the primary exception to this rule is with a subset of the Input
/// Parsing routines).
///
/// \li \ref CXXinput
/// \li \ref CXXtimer
/// \li \ref CXXocore
/// \li \ref Cmisc
/// \li \ref Cversioning

//--------------------------
// C++ GRVY Interfaces
//--------------------------

#include<vector>
#include<map>
#include<string>
#include<memory>

// Forward declare GetPot class so we don't need
// to include getpot.h here.

namespace GRVYGetPot
  {
    class GetPot;
  }

//--------------------
// Input Parsing Class
//--------------------

/// 
/// \defgroup CXXinput Input Parsing
/// @ingroup CXXapi
///
/// \brief This section presents available C++ routines for accessing
/// input parameters from a libGRVY style input file. See the \ref
/// inputFile "example input file" for more information on the file
/// format. Unless specified otherwise, functions which have an
/// integer return value return "0" upon success. The primary
/// exception to this rule is with the read() routines.  All
/// grvy_input_fread_() routines return 1 on success and 0 on failure.
/// This return behavior is intended as a convenience for
/// applications to check input file parsing errors over consecutive
/// reads via multiplicative operations.
///
/// \b Namespace: All libGRVY C++ classes are contained with the GRVY namespace. 
///
/// <b>Class Name:</b> GRVY::GRVY_Input_Class
///
/// <b> Code Example:</b> A specific C++ example using the input parsing
/// routines is available in \ref CXXinputExample "cpp-input.cpp".
/// 
/// <hr>

// \namespace GRVY 
// \brief Namespace containing all libGRVY classes.

namespace GRVY {

  void GRVY_version_stdout();
  int  GRVY_get_numeric_version();

 /** 
   * \ingroup CXXinput
   * @{
   */

  /* \brief Input Parsing Class 
   * 
   */

class GRVY_Input_Class {

 public:
  GRVY_Input_Class  ();
 ~GRVY_Input_Class  ();

  /** 
   * \ingroup CXXinput
   * \name File open/close:
   *
   * Class member functions for accessing input parameters from a libGRVY style
   * input file. Note that an input file must be opened prior to reading
   * any keyword/value pairs or performing input file dump
   * operations. 
   */

  /**
   * \ingroup CXXinput
   * @{ 
   */

  /// \brief open \e filename for parsing
  int  Open         (const char *filename);

  /// \brief close previously opened input file.
  int  Close        ();

  /** @} */

  void MsgToggle    (int flag);

  /** \ingroup CXXinput
   *  \name Dump input file contents:
   * 
   * The following member functions are used to dump the entire
   * contents of a parsed libGRVY style input file to stdout or
   * appended to an ASCII file (note that all comments within the
   * original input file are stripped). The prefix variable can be
   * used to include an additional delimiter which prepends each line
   * of the output. Note that an input file must be open prior to
   * reading any performing input file dump operations. These routines
   * are normally used to save all relevant input parameters in the
   * application output for future traceability and repeatability.
   *
   */

  /** \ingroup CXXinput
   * @{
   */

  /** \brief Dump input file settings to stdout. */
  int  Fdump        ();

  /** \brief Dump input file settings to stdout prefixed by a delimiter */
  int  Fdump        (const char *prefix);

  /** \brief Dump input file settings to an open file with a provided prefix delimiter */
  int  Fdump        (const char *prefix, const char *filename);

  /** @} */

  /** \ingroup CXXinput
   *  \name Read scalar values
   * 
   * The following member functions are used to read a scalar input \e
   * value associated with the \e keyword string. The \e keyword can
   * be provided as a string or const char* pointer. If desired, a \e
   * vardef argument can be included which provides a default value
   * for the scalar if the requested \e keyword is not present in the
   * input file.. Alternatively, you can use the Register_Var family
   * of functions to provide default values.  Supported numeric template 
   * datatypes include int, float, and double.
   */

  /** \ingroup CXXinput
   * @{
   */

  template <typename T> int Read_Var      (std::string keyword, T *value );           ///< Scalar read
  template <typename T> int Read_Var      (std::string keyword, T *value, T vardef);  ///< Scalar read with default

  template <typename T> int Read_Var      (const char *keyword, T *value );           ///< Scalar read
  template <typename T> int Read_Var      (const char *keyword, T *value, T vardef);  ///< Scalar read with default

  // Character string reads

  int Read_Var                            (const char *keyword, std::string *value);                     ///< Scalar
  int Read_Var                            (const char *keyword, char **value);                           ///< Scalar
  int Read_Var                            (const char *keyword, std::string *value, std::string vardef); ///< Scalar 

  // Bool Read Functions

  int Read_Var                            (const char *var, bool *value, bool vardef); ///< Scalar
  int Read_Var                            (std::string var, bool *value, bool vardef); ///< Scalar

  /** @} */

  /** \ingroup CXXinput
   *  \name Read vector values 
   * 
   * The following member functions are used to read vector valued
   * input values for common intrinsic datatypes given a desired
   * \e keyword. If successful, the resulting
   * data is stored in the array values.
   */

  /** \ingroup CXXinput
   * @{
   */

  template <typename T> int Read_Var_Vec  (std::string keyword, T *values, int nelems);            ///< Vec
  template <typename T> int Read_Var_Vec  (const char *keyword, T *values, int nelems);		   ///< Vec
  template <typename T> int Read_Var_Vec  (std::string keyword, T *values, int nelems, T vardef);  ///< Vec
  template <typename T> int Read_Var_Vec  (const char *keyword, T *values, int nelems, T vardef);  ///< Vec

  /** @} */

  /** \ingroup CXXinput
   *  \name Read ith vector value 
   * 
   * The following member functions are used to read the ith entry (\e elem) of 
   * vector valued input values for common intrinsic datatypes given a desired 
   * keyword. If successful, the resulting
   * data is stored in \e value.
   */

  /** \ingroup CXXinput
   * @{
   */

  template <typename T> int Read_Var_iVec (std::string keyword, T *value, int elem);               ///< iVec
  template <typename T> int Read_Var_iVec (const char *keyword, T *value, int elem);		   ///< iVec
  template <typename T> int Read_Var_iVec (std::string keyword, T *value, int elem,   T vardef);   ///< iVec
  template <typename T> int Read_Var_iVec (const char *keyword, T *value, int elem,   T vardef);   ///< iVec

  // Character String Read Functions

  int Read_Var_iVec                       (const char *keyword, char **value, int elem);           ///<iVec
  int Read_Var_iVec                       (const char *keyword, std::string *value, int elem);     ///<iVec

  /** @} */

  /** \ingroup CXXinput
   *  \name Default value registration:
   * 
   * The following member functions provide a mechanism to register a
   * default value with the input parsing mechanism. If a particular
   * \e keyword has a registered default value and is subsequently
   * queried with an input file which does not contain the keyword,
   * the registered default value will be returned instead. A
   * convenient use for these registration functions is to provide
   * sensible defaults to newly added input keywords which are not
   * present in older input file revisions.
   */

  /** \ingroup CXXinput
   * @{
   */

  void Register_Var  (const char *keyword, int     var);           ///< Register_Var
  void Register_Var  (const char *keyword, float   var);	   ///< Register_Var
  void Register_Var  (const char *keyword, double  var);	   ///< Register_Var
  void Register_Var  (const char *keyword, bool    var);	   ///< Register_Var
  void Register_Var  (const char *keyword, const char  *var);	   ///< Register_Var
  void Register_Var  (const char *keyword, std::string  var);      ///< Register_Var

  /** @} */

  /** 
   * \ingroup CXXinput 
   * \name Default registration query:
   *
   * The following member functions can be used to query the current
   * hashed values of any keyword variables which have been registered
   * previously.
   */

  /** \ingroup CXXinput
   * @{
   */

  int  Get_Var       (const char *keyword, int    *value);       ///< Get_Var
  int  Get_Var       (const char *keyword, float  *value);	 ///< Get_Var
  int  Get_Var       (const char *keyword, double *value);	 ///< Get_Var
  int  Get_Var       (const char *keyword, char  **value);	 ///< Get_Var
  int  Get_Var       (const char *keyword, std::string *value);  ///< Get_Var

  void PrintRegVars  (const char *prefix); ///< Print

  /** @} */

 private:
  class GRVY_Input_ClassImp       ;           // forward declaration to Input class implementation
  std::auto_ptr<GRVY_Input_ClassImp> m_pimpl; // pointer to implementation

};

  /* @} */  

//--------------------------
// Performance Timing Class
//--------------------------

  /** \defgroup CXXtimer Performance Timer Utilities 
   *  \ingroup CXXapi
   *
   * \brief This section presents the C++ class for measuring
   * runtime performance of specific code sections to aid in overall
   * performance/statistical analysis, and to maintain historical
   * performance records as application codes evolve or across
   * alternate compute platforms.  Individual code timers are defined
   * based on BeginTimer/EndTimer demarcation around the desired code snippet to
   * measure along with a unique user-provided id string. Note that
   * individual timers can be nested and the library will report
   * exclusive timing of the innermost timers. Various options are
   * provided to interrogate timer measurements, statistics, and
   * relative timer comparisons. A convenient use of these routines is
   * to define timers around various important work constructs within
   * your application and use the Summarize() function to
   * obtain a concise summary of the runtime performance, variability,
   * and relative wallclock comparisions. Example output using this
   * approach is shown below:
   *
   *  \code 
   * -----------------------------------------------------------------------------------------------
   * GRVY Example Timing - Performance Timings:              |      Mean      Variance       Count
   * --> foo                 : 3.00978e+00 secs ( 64.0889 %) | [3.00978e-01  2.70727e-08         10]
   * --> boo                 : 1.17648e+00 secs ( 25.0513 %) | [1.17648e-01  2.35981e-08         10]
   * --> bar                 : 5.09513e-01 secs ( 10.8493 %) | [5.09513e-02  5.02795e-08         10]
   * --> Main Program        : 4.48704e-04 secs (  0.0096 %) | [4.48704e-04  0.00000e+00          1]
   * --> GRVY_Unassigned     : 4.02927e-05 secs (  0.0009 %)
   * 
   *     Total Measured Time = 4.69626e+00 secs (100.0000 %)
   * -----------------------------------------------------------------------------------------------
   *  \endcode
   *
   * \b Namespace: All libGRVY C++ classes are contained with the GRVY namespace. 
   *
   * <b>Class Name:</b> GRVY::GRVY_Timer_Class
   *
   * <b> Code Example</b>: A specific C++ example using the performance timing
   * routines is available in \ref CXXtimerExample "cpp-timer.cpp".
   *
   * <hr>
   */

class GRVY_Timer_Class {

 public:
  GRVY_Timer_Class        (); 
 ~GRVY_Timer_Class        ();

  /**
   * \ingroup CXXtimer
   * \name Performance Timer - Initialization and Timer Demarcation:
   *
   * The following member functions provide support for defining one or more
   * wall-clock timers around specific code regions. Individual timers are
   * delineated by a unique \e id.  In addition to timing specific code
   * regions identified with begin/end calls, the library also
   * tracks the total application time from when the timing library
   * was first initialized.
   */

  /** \ingroup CXXtimer
   * @{
   */

  void   Init             (std::string name); ///<  intialize global timing process
  void   BeginTimer       (std::string id);   ///<  starts local timer
  void   EndTimer         (std::string id);   ///<  ends local timer
  void   Finalize         ();                 ///<  ends global timer

  /** @} */

  /**
   * \ingroup CXXtimer
   * \name Performance Timer - Query Tools:
   *
   * The following member functions allow for the querying of defined
   * performance timers.
   */

  /**
   * \ingroup CXXtimer
   * @{ */
  
  double ElapsedSeconds   (std::string id);   // return elapsed time for specifc timer id
  double ElapsedGlobal    ();		      // return elapsed time since Init()
  double RawTimer         ();		      // raw timer

  void   Reset            ();	              // reset all timers
  void   Summarize        ();	              // pretty-print timing information
  int    SetSummarizeWidth(const int width);  // set max output width for summarize stdout

  size_t StatsCount       (std::string id);   // # of calls to timer (id)
  double StatsMean        (std::string id);   // mean time for timer (id)
  double StatsVariance    (std::string id);   // variance for timer  (id)
  double StatsMin         (std::string id);   // min value for timer (id)
  double StatsMax         (std::string id);   // max value for timer (id)



  /** @} */

  /**
   * \ingroup CXXtimer
   * \name Performance Timing - Historical Logging:
   *
   * These member functions provide support to store measured runtime
   * performance into an HDF5 file for logging purposes (this
   * functionality requires HDF5 library linkage during the libGRVY
   * configuration phase). Results are stored on a per-machine basis
   * and are appended to the HDF5 file with timestamps to document
   * historical performance over time.  Stored results can be
   * retrieved using the API below or via standalone executables
   * installed with libGRVY.
   * 
   * There are two primary modes for saving historical performance
   * data:
   * 
   * <b>Mode 1</b>: you are using the GRVY_Timer_Class to define
   *         individual sections to monitor and want to save the
   *         global runtime measurement along with all individually
   *         defined subtimers.
   * 
   * <b>Mode 2</b>: you are using other means to profile the application code
   *         and want to save a single global timing value. Routines
   *         for this mode are distinguished by the presence of an
   *         extra "timing" argument in the calling sequence.
   * 
   * In both modes, standard and expanded (exp) calling sequences are supported
   * with the expanded version allowing additional optional runtime
   * documentation (e.g. flops, code revision) to be provided.
   * 
   */

  /** \ingroup CXXtimer
   * @{
   */

  // Mode 1: Saving internal GRVY timer values to historical repository

  int  SaveHistTiming      (std::string experiment, std::string comment, int num_procs, 
			    std::string filename);

  int  SaveHistTiming      (std::string experiment, std::string comment, int num_procs, 
			    int jobId, std::string code_revision, double flops, std::string filename);

  // Mode 2: Saving user-provided global timing to historical repository

  int  SaveHistTiming      (double timing, std::string machinename, std::string experiment, 
			    std::string comment, int num_procs, std::string filename);

  int  SaveHistTiming      (double timing, std::string machinename, std::string experiment, 
			    std::string comment, int num_procs, int jobId, std::string code_revision, 
			    double flops, std::string filename);

  // ---------------
  // Query Functions
  // ---------------

  void SummarizeHistTiming (std::string filename,   std::string delimiter, std::string outdir);

  /** @} */


  // Class options 

  int  SetOption           (std::string option, bool flag);

private:
  class GRVY_Timer_ClassImp;	              // forward declaration to Timer implementation
  std::auto_ptr<GRVY_Timer_ClassImp> m_pimpl; // pointer to implementation

};

  //--------------------------
  // MPI Out-of-Core Class
  //--------------------------

  /** \defgroup CXXocore MPI Out-of-Core Utilities 
   *  \ingroup CXXapi
   *
   * \brief This section presents the C++ class which provides support
   * to offload out-of-core read/write operations to a pool of
   * distributed shared-memory nodes using MPI for data transfer.  An
   * additional level of indirection can be enabled to offload
   * less-frequently accessed data to one or more disk-based files.
   */

  /** 
   * \ingroup CXXocore
   * @{
   */


class GRVY_MPI_Ocore_Class {

public:
  GRVY_MPI_Ocore_Class(); 
 ~GRVY_MPI_Ocore_Class();

  /** 
   * \ingroup CXXocore
   * \name Initialization and runtime queries:
   *
   * Member functions to initialize/finalize out-of-core suport
   * (requires MPI enabled libGRVY build) and runtime utilities.
   */

  /** \ingroup CXXocore 
   * @{ 
   */

  int    Initialize   (std::string inputfile);
  void   Finalize     ();
  size_t NumActive    ();	// number of currently active records
  bool   isMaster     ();	// is the calling task the ocore master?
  bool   isEnabled    ();	// is MPI Ocore enabled? (can be controlled via input file)
  int    Blocksize    ();       // Ocore blocksize

  /** @} */

  // Read/Write Functions

  /** @}
   *
   * \ingroup Cocore 
   * \name Read/Write:
   *
   * Member functions to read and write blocks of data to remote
   * memory pools for standard intrinsic datatypes. Supported template
   * \e data types include ints, floats, doubles, and long longs.
   *
   */

  /** \ingroup CXXocore
   * @{
   */

  template <typename T> int Write (size_t offset,T *data );
  template <typename T> int Read  (size_t offset,T *data );

  /** @} */

  // Record retrieval/removal

  /** @}
   * \ingroup CXXocore
   * \name Record retreival:
   * 
   * Member function to query the state of an existing remote out-of-core
   * memory pool and read the next available record.  These routines
   * are primarily used to save the state to disk.  Supported template
   * \e data types include ints, floats, doubles, and long longs.
   */

  /** \ingroup CXXocore
   * @{ */

  template <typename T> size_t PopRecord (T *data );

  /** @} */

private:
  class GRVY_MPI_Ocore_ClassImp;		  // forward declaration to Ocore implementation
  std::auto_ptr<GRVY_MPI_Ocore_ClassImp> m_pimpl; // pointer to implementation
};

//--------------------
// HDF5 Utility Class
//--------------------

 class GRVY_HDF5_Class //: private boost::noncopyable
 {
   friend class GRVY_Timer_Class;

 public:
   GRVY_HDF5_Class  ();
  ~GRVY_HDF5_Class  ();

   GRVY_HDF5_Class  (const GRVY_HDF5_Class &rhs);
   GRVY_HDF5_Class  &operator= (GRVY_HDF5_Class );

   // File-related functions
   
   int  Create  (std::string filename, bool overwrite_existing);
   int  Open    (std::string filename, bool read_only         );
   bool Exists  (std::string filename);
   int  Close   ();

   // Group-related functions
   
   int  GroupCreate (std::string groupname);
   int  GroupOpen   (std::string groupname);
   bool GroupExists (std::string groupname);

   std::vector<std::string> ListSubGroups(std::string groupname);

   // Dataset-related functions

   int  DatasetOpen  (std::string groupname, std::string datasetname);
   bool DatasetExists(std::string groupname, std::string datasetname);

   // Attribute-related functions

   int  AttributeOpen  (std::string groupname, std::string attribute);
   bool AttributeExists(std::string groupname, std::string attribute);

   int AttributeWrite(std::string groupname, std::string attribute,          short int  value);
   int AttributeWrite(std::string groupname, std::string attribute,                int  value);
   int AttributeWrite(std::string groupname, std::string attribute,               long  value);
   int AttributeWrite(std::string groupname, std::string attribute, unsigned short int  value);
   int AttributeWrite(std::string groupname, std::string attribute,       unsigned int  value);
   int AttributeWrite(std::string groupname, std::string attribute,      unsigned long  value);
   int AttributeWrite(std::string groupname, std::string attribute,              float  value);
   int AttributeWrite(std::string groupname, std::string attribute,             double  value);
   int AttributeWrite(std::string groupname, std::string attribute,        std::string  value);

   int AttributeRead (std::string groupname, std::string attribute,          short int &value);
   int AttributeRead (std::string groupname, std::string attribute,                int &value);
   int AttributeRead (std::string groupname, std::string attribute,               long &value);
   int AttributeRead (std::string groupname, std::string attribute, unsigned short int &value);
   int AttributeRead (std::string groupname, std::string attribute,       unsigned int &value);
   int AttributeRead (std::string groupname, std::string attribute,      unsigned long &value);
   int AttributeRead (std::string groupname, std::string attribute,              float &value);
   int AttributeRead (std::string groupname, std::string attribute,             double &value);
   int AttributeRead (std::string groupname, std::string attribute,        std::string &value);

   // Dataset-related functions

   // Packet Table related functions
   
 private:
   //boost::scoped_ptr<GRVY_HDF5_ClassImp> m_pimpl;
   class GRVY_HDF5_ClassImp;	               // forward declaration of HDF5 implementation
   std::auto_ptr<GRVY_HDF5_ClassImp> m_pimpl;  // pointer to implementation
 };
}

#endif

#endif
