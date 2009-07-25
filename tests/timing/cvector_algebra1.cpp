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
      for(int k = 0; k < 4; ++k) {
        v[k] = v[k]+v1[k]+v2[k]+v3[k];
      }
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
