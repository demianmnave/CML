/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

/* The args should *not* be references: */
inline void timed1(
        matrix_d44 m,
        const matrix_d44 m1,
        const matrix_d44 m2,
        const matrix_d44 m3,
        size_t n_iter
        )
{
    matrix_d44 tmp, tmp2; 
    for(size_t i = 0; i < n_iter; ++i) {
        for(size_t row = 0; row < 4; ++row) {
            for(int col = 0; col < 4; ++col) {
#if 0
                m[row][col] = m[row][col] + m1[row][col] + m2[row][col]
                    + m3[row][col] + m2[row][col];
#endif
#if 1
                m[row][col] += m1[row][col] + m2[row][col]
                    + m3[row][col] + m2[row][col];
#endif
            }
        }
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
