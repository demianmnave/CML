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
        /* XXX Note: this is slow for external vectors (GCC4): */
        v = v+v1+v2+v3;

        /* XXX Note: this is fast for external vectors (GCC4): */
        //v += v1+v2+v3;
        //v += v1+v2;
        //v = v+v1+v2;
        //v = v+v1+v2+2.*v3;
        //v = v+v1;
        //v = v+v1+v2+v3+v4;
        //v += v1+v2+v3;
        //v += v3*dot(v2,(v1*dot(v1,v2)));
        //v = v+v1*dot(T(v2),v3);
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
