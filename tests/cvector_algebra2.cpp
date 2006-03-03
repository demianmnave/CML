/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#if 0
inline double dot(vector_d4 v1, vector_d4 v2)
{
  double sum = 0;
  for(int k = 0; k < 4; ++k) {
    sum += v1[k]*v2[k];
  }
  return sum;
}
#else
inline double dot(vector_d4 v1, vector_d4 v2)
{
  return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3];
}
#endif

/* The args should *not* be references---it slows down at least GCC 4.0: */
inline void timed2(
        vector_d4 v,
        vector_d4 v1,
        vector_d4 v2,
        vector_d4 v3,
        vector_d4 v4,
        size_t n_iter
        )
{
    for(int i = 0; i < n_iter; ++i) {
      double dp = dot(v2,v3);
#if defined(__ICC) && defined(__linux__) && (__ICC >= 900)
      /* Intel 9 Linux/x86 optimizes loops much better than blocks: */
      for(int k = 0; k < 4; ++k) {
        v[k] += v1[k]*dp;
      }
#else
#if 1
      v[0] += v1[0]*dp;
      v[1] += v1[1]*dp;
      v[2] += v1[2]*dp;
      v[3] += v1[3]*dp;
#else
      v[0] = v[0] + v1[0]*dp;
      v[1] = v[1] + v1[1]*dp;
      v[2] = v[2] + v1[2]*dp;
      v[3] = v[3] + v1[3]*dp;
#endif
#endif
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
