/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

/* Algebraic test #2: */
inline void timed2(
        vector_d4& v,
        const vector_d4& v1,
        const vector_d4& v2,
        const vector_d4& v3,
        const vector_d4& v4,
        size_t n_iter
        )
{
    for(size_t i = 0; i < n_iter; ++i) {
        //v += v1*dot(v2,v3);
        //v += v1*dot(v2,v3+v4+v2);
        v *= dot(v2,v3+v4+v2)*dot(v2,v3+v4+v2);
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
