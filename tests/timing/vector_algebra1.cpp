/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

/* Algebraic test #1: */
inline void timed1(
        vector_d4& v,
        const vector_d4& v1,
        const vector_d4& v2,
        const vector_d4& v3,
        const vector_d4& v4,
        size_t n_iter
        )
{
    for(size_t i = 0; i < n_iter; ++i) {
        v = v+v1+v2+v3;
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
