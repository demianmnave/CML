/* -*- C++ -*- ------------------------------------------------------------
   @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

inline double dot(vector_d4 v1, vector_d4 v2)
#if 0
{
    double sum = 0;
    for(int k = 0; k < 4; ++k) {
        sum += v1[k]*v2[k];
    }
    return sum;
}
#else
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3];
}
#endif

inline void add(vector_d4 res, vector_d4 v1, vector_d4 v2)
#if 0
{
    for(int k = 0; k < 4; ++k) {
        res[k] = v1[k] + v2[k];
    }
}
#else
{
    res[0] = v1[0]+v2[0];
    res[1] = v1[1]+v2[1];
    res[2] = v1[2]+v2[2];
    res[3] = v1[3]+v2[3];
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
  vector_d4 VECINIT(tmp1), VECINIT(tmp2);
    for(size_t i = 0; i < n_iter; ++i) {
        add(tmp1,v3,v4);
        add(tmp2,tmp1,v2);
        double dp = dot(v2,tmp2);
#if 1
#if defined(__ICC) && defined(__linux__) && (__ICC >= 900)
        /* Intel 9 Linux/x86 optimizes loops much better than blocks: */
        for(int k = 0; k < 4; ++k) {
            v[k] *= dp*dp;
        }
#else
#if 1
        v[0] *= dp*dp;
        v[1] *= dp*dp;
        v[2] *= dp*dp;
        v[3] *= dp*dp;
#else
        v[0] = v[0] * dp*dp;
        v[1] = v[1] * dp*dp;
        v[2] = v[2] * dp*dp;
        v[3] = v[3] * dp*dp;
#endif
#endif
#else
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
#endif
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
