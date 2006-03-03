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
        size_t n_iter
        )
{
    //matrix_d44 tmp, tmp2;
    for(size_t i = 0; i < n_iter; ++i) {
        /* m = m1*m2*m3 -> tmp = m1*m2, m = tmp*m3 */
        //mult(m1,m2,tmp); mult(tmp,m3,m);

        /* m = m1*m2*m3*m3 -> tmp = m1*m2, tmp2 = m3*m3, m = tmp*tmp2 */
        //mult(m1,m2,tmp); mult(m3,m3,tmp2); mult(tmp,tmp2,m);

        /* XXX Slower with unroller using ICC 9 and GCC 4 on x86 */
        //m = m + m1 + m2 + m3 + m2;

        /* XXX Slower without unroller using ICC 9 and GCC 4 on x86 */
        m += m1 + m2 + m3 + m2;

        //m += m1;
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
