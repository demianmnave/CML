/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */


#if 0
inline void cmul(matrix_d44& res, const matrix_d44& A, const matrix_d44& B)
{
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
	    double sum = A(row,0)*B(0,col);
	    for(int k = 1; k < 4; ++k) {
		sum += A(row,k)*B(k,col);
	    }
	    res(row,col) = sum;
	}
    }
}
#endif

#if 1
inline matrix_d44
cmul(const matrix_d44& A, const matrix_d44& B)
{
    matrix_d44 res;
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
	    double sum = A(row,0)*B(0,col);
	    for(int k = 1; k < 4; ++k) {
		sum += A(row,k)*B(k,col);
	    }
            res(row,col) = sum;
	}
    }
    return res;
}
#endif

#if 0
matrix_d44
cmul(const matrix_d44& A, const matrix_d44& B)
{
    matrix_d44 res;

    res(0,0)  = A(0,0)*B(0,0);
    res(0,0) += A(0,1)*B(1,0);
    res(0,0) += A(0,2)*B(2,0);
    res(0,0) += A(0,3)*B(3,0);

    res(0,1)  = A(0,0)*B(0,1);
    res(0,1) += A(0,1)*B(1,1);
    res(0,1) += A(0,2)*B(2,1);
    res(0,1) += A(0,3)*B(3,1);

    res(0,2)  = A(0,0)*B(0,2);
    res(0,2) += A(0,1)*B(1,2);
    res(0,2) += A(0,2)*B(2,2);
    res(0,2) += A(0,3)*B(3,2);

    res(0,3)  = A(0,0)*B(0,3);
    res(0,3) += A(0,1)*B(1,3);
    res(0,3) += A(0,2)*B(2,3);
    res(0,3) += A(0,3)*B(3,3);

    res(1,0)  = A(1,0)*B(0,0);
    res(1,0) += A(1,1)*B(1,0);
    res(1,0) += A(1,2)*B(2,0);
    res(1,0) += A(1,3)*B(3,0);

    res(1,1)  = A(1,0)*B(0,1);
    res(1,1) += A(1,1)*B(1,1);
    res(1,1) += A(1,2)*B(2,1);
    res(1,1) += A(1,3)*B(3,1);

    res(1,2)  = A(1,0)*B(0,2);
    res(1,2) += A(1,1)*B(1,2);
    res(1,2) += A(1,2)*B(2,2);
    res(1,2) += A(1,3)*B(3,2);

    res(1,3)  = A(1,0)*B(0,3);
    res(1,3) += A(1,1)*B(1,3);
    res(1,3) += A(1,2)*B(2,3);
    res(1,3) += A(1,3)*B(3,3);

    res(2,0)  = A(2,0)*B(0,0);
    res(2,0) += A(2,1)*B(1,0);
    res(2,0) += A(2,2)*B(2,0);
    res(2,0) += A(2,3)*B(3,0);

    res(2,1)  = A(2,0)*B(0,1);
    res(2,1) += A(2,1)*B(1,1);
    res(2,1) += A(2,2)*B(2,1);
    res(2,1) += A(2,3)*B(3,1);

    res(2,2)  = A(2,0)*B(0,2);
    res(2,2) += A(2,1)*B(1,2);
    res(2,2) += A(2,2)*B(2,2);
    res(2,2) += A(2,3)*B(3,2);

    res(2,3)  = A(2,0)*B(0,3);
    res(2,3) += A(2,1)*B(1,3);
    res(2,3) += A(2,2)*B(2,3);
    res(2,3) += A(2,3)*B(3,3);

    res(3,0)  = A(3,0)*B(0,0);
    res(3,0) += A(3,1)*B(1,0);
    res(3,0) += A(3,2)*B(2,0);
    res(3,0) += A(3,3)*B(3,0);

    res(3,1)  = A(3,0)*B(0,1);
    res(3,1) += A(3,1)*B(1,1);
    res(3,1) += A(3,2)*B(2,1);
    res(3,1) += A(3,3)*B(3,1);

    res(3,2)  = A(3,0)*B(0,2);
    res(3,2) += A(3,1)*B(1,2);
    res(3,2) += A(3,2)*B(2,2);
    res(3,2) += A(3,3)*B(3,2);

    res(3,3)  = A(3,0)*B(0,3);
    res(3,3) += A(3,1)*B(1,3);
    res(3,3) += A(3,2)*B(2,3);
    res(3,3) += A(3,3)*B(3,3);

    return res;
}
#endif

/* Note: this *must* be inlined for ICC9/Linux to vectorize the loops! */
void timed2(
        matrix_d44& m,
        const matrix_d44& m1,
        const matrix_d44& m2,
        const matrix_d44& m3,
        size_t n_iter
        )
{
    matrix_d44 tmp; 
    m[0][0] = 1.; m[0][1] = 0.; m[0][2] = 0.; m[0][3] = 0.;
    m[1][0] = 0.; m[1][1] = 1.; m[1][2] = 0.; m[1][3] = 0.;
    m[2][0] = 0.; m[2][1] = 0.; m[2][2] = 1.; m[2][3] = 0.;
    m[3][0] = 0.; m[3][1] = 0.; m[3][2] = 0.; m[3][3] = 1.;
    for(size_t i = 0; i < n_iter; ++i) {
        /* m = m1*m2*m3 */
        //m = m*m1*m2;

        /* m = m*m1*m2 */
        //mul(tmp,m,m1);
        //mul(m,tmp,m2);
        //tmp = m*m1;
        //m = tmp*m2;
        m = m*m1*m2;
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
