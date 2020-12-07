/****************************************************************************
 ** File: pm_std.h
 ** Abstract:
 **     Physical modeling standard header.
 ** 
 ** Copyright 2009-2014 The MathWorks, Inc.
 ****************************************************************************/

#ifndef __pm_std_h__
#define __pm_std_h__

#include "pm_system.h"

#ifdef MATLAB_MEX_FILE
#include "tmwtypes.h"
#else
#include "rtwtypes.h"
#endif

#include "pm_types.h"

#ifdef _MSC_VER
#define PMF_DEPLOY_STATIC static __inline
#else
#define PMF_DEPLOY_STATIC static
#endif

#define pmf_printf         printf
#define pmf_vprintf        vprintf 
#define pmf_strcpy         strcpy
#define pmf_calloc         calloc
#define pmf_free           free
#define pmf_malloc         malloc
#define pmf_get_message(x) x

real_T pmf_get_eps(void);

real_T pmf_get_real_max(void);

real_T pmf_get_real_min(void);

real_T pmf_get_pi(void);

real_T pmf_get_inf(void);

void pmf_warning( const char *w, ...);

void pmf_preformatted_warning(const char *id,
                              const char *msg);

int pmf_vsnprintf_message(char       *buffer,
                          size_t      l,
                          const char *format,
                          va_list     arg);

int pmf_snprintf_message(char       *buffer,
                         size_t      length,
                         const char *format,
                         ...);

boolean_T pmf_is_interrupt_pending(void);

#ifndef TRUE
#define TRUE                          (1U)
#endif

#ifndef FALSE
#define FALSE                         (0U)
#endif

typedef const char    *PmfMessageId;

#endif /* __pm_std_h__ */
/* [EOF] pm_std.h */
