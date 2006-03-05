/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

/* The args should *not* be references---it slows down at least GCC 4.0: */
inline void timed1(
        vector_d4 v,
        vector_d4 v1,
        vector_d4 v2,
        vector_d4 v3,
        vector_d4 v4,
        size_t n_iter
        )
{
    for(size_t i = 0; i < n_iter; ++i) {
#if defined(__ICC) && defined(__linux__) && (__ICC >= 900)
      /* Intel 9 Linux/x86 optimizes loops much better than blocks: */
      for(int k = 0; k < 4; ++k) {
        v[k] = v[k]+v1[k]+v2[k]+v3[k];
      }
#else
#if 0
      v[0] += v1[0]+v2[0]+v3[0];
      v[1] += v1[1]+v2[1]+v3[1];
      v[2] += v1[2]+v2[2]+v3[2];
      v[3] += v1[3]+v2[3]+v3[3];
#else
      v[0] = v[0] + v1[0]+v2[0]+v3[0];
      v[1] = v[1] + v1[1]+v2[1]+v3[1];
      v[2] = v[2] + v1[2]+v2[2]+v3[2];
      v[3] = v[3] + v1[3]+v2[3]+v3[3];
#endif
#endif
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
