/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

void mul(matrix_d44 res, const matrix_d44 A, const matrix_d44 B)
{
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
	    double sum = A[row][0]*B[0][col];
	    for(int k = 1; k < 4; ++k) {
		sum += A[row][k]*B[k][col];
	    }
	    res[row][col] = sum;
	}
    }
}

/* The args should *not* be references: */
void timed2(
        matrix_d44 m,
        const matrix_d44 m1,
        const matrix_d44 m2,
        const matrix_d44 m3,
        size_t n_iter
        )
{
    matrix_d44 tmp, tmp2; 
    for(int i = 0; i < n_iter; ++i) {
        /* m = m1*m2*m3 */
#if 1
        mul(tmp,m1,m2);
        mul(m,tmp,m3);
#endif
#if 0
        mul(m,m1,m2);
#endif
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
