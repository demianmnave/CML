/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include "timing.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define NOCRYPT
#define NOGDI
#define NOSERVICE
#define NOMCX
#define NOIME
#include <windows.h>
#include <cstdlib>
#include <cstdio>

usec_t usec_time()
{
    LARGE_INTEGER liC, liF;

    /* Get counts per second: */
    QueryPerformanceFrequency(&liF);

    /* Get current count: */
    QueryPerformanceCounter(&liC);

    LONGLONG freq = liF.QuadPart;
    LONGLONG val = liC.QuadPart;

    /* Return total number of microseconds: */
    return (val*1000000ULL)/freq;
}
#else

#include <sys/time.h>

usec_t usec_time()
{
  timeval tv;
  gettimeofday(&tv,0);
  return tv.tv_sec*1000000ULL + tv.tv_usec;
}

#endif


// -------------------------------------------------------------------------
// vim:ft=cpp
