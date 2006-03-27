/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

/* Note: this *must* be inlined for ICC9/Linux to vectorize the loops! */
inline void timed1(
        matrix_d44& m,
        const matrix_d44& m1,
        const matrix_d44& m2,
        const matrix_d44& m3,
        vector_d4& v,
        const vector_d4& v1,
        const vector_d4& v2,
        const vector_d4& v3,
        const vector_d4& v4,
        size_t n_iter
        )
{
    vector_d4 t1;
    for(size_t i = 0; i < n_iter; ++i) {
        v = m1*(v+v2);
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
