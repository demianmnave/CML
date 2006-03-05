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

#if 0
const matrix_d44
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
#if 0
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
            double sum = A(row,0)*B(0,col);
            for(int k = 1; k < 4; ++ k) {
                sum += A(row,k)*B(k,col);
            }
            res(row,col) = sum;
	}
    }
#endif

#if 0
    for(int row = 0; row < 4; ++row) {
        res(row,0)  = A(row,0)*B(0,0);
        res(row,0) += A(row,1)*B(1,0);
        res(row,0) += A(row,2)*B(2,0);
        res(row,0) += A(row,3)*B(3,0);

        res(row,1)  = A(row,0)*B(0,1);
        res(row,1) += A(row,1)*B(1,1);
        res(row,1) += A(row,2)*B(2,1);
        res(row,1) += A(row,3)*B(3,1);

        res(row,2)  = A(row,0)*B(0,2);
        res(row,2) += A(row,1)*B(1,2);
        res(row,2) += A(row,2)*B(2,2);
        res(row,2) += A(row,3)*B(3,2);

        res(row,3)  = A(row,0)*B(0,3);
        res(row,3) += A(row,1)*B(1,3);
        res(row,3) += A(row,2)*B(2,3);
        res(row,3) += A(row,3)*B(3,3);
    }
#endif
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

#if 0
inline matrix_d44
operator^(const matrix_d44& A, const matrix_d44& B)
{
    matrix_d44 res;
#if 0
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
            (*const_cast<matrix_d44*>(&res))(row,col) += B(row,col);
	}
    }
#endif

#if 0
    res += B;
#endif

#if 0
    res *= 2.;
#endif

#if 0
    for(int row = 0; row < 4; ++row) {
#if 1
	for(int col = 0; col < 4; ++col) {
#if 1
            double sum = A(row,0)*B(0,col);
	    for(int k = 1; k < 4; ++k) {
                sum += A(row,k)*B(k,col);
	    }
            res(row,col) = sum;
#else
            res(row,col) = A(row,0)*B(0,col);
            res(row,col) += A(row,1)*B(1,col);
            res(row,col) += A(row,2)*B(2,col);
            res(row,col) += A(row,3)*B(3,col);
#endif
	}
#endif

#if 0
        res(row,0)  = A(row,0)*B(0,0);
        res(row,0) += A(row,1)*B(1,0);
        res(row,0) += A(row,2)*B(2,0);
        res(row,0) += A(row,3)*B(3,0);

        res(row,1)  = A(row,0)*B(0,1);
        res(row,1) += A(row,1)*B(1,1);
        res(row,1) += A(row,2)*B(2,1);
        res(row,1) += A(row,3)*B(3,1);

        res(row,2)  = A(row,0)*B(0,2);
        res(row,2) += A(row,1)*B(1,2);
        res(row,2) += A(row,2)*B(2,2);
        res(row,2) += A(row,3)*B(3,2);

        res(row,3)  = A(row,0)*B(0,3);
        res(row,3) += A(row,1)*B(1,3);
        res(row,3) += A(row,2)*B(2,3);
        res(row,3) += A(row,3)*B(3,3);
#endif

#if 0
	for(int col = 0; col < 4; ++col) {
	    res(row,col) = dot(cml::row(A,row),cml::col(B,col));
	    res(row,col) = dot(cml::row(A,row),cml::col(B,col));
	    res(row,col) = dot(cml::row(A,row),cml::col(B,col));
	    res(row,col) = dot(cml::row(A,row),cml::col(B,col));
	}
#endif

#if 0
        res(row,0) = dot(cml::row(A,row),cml::col(B,0));
        res(row,1) = dot(cml::row(A,row),cml::col(B,1));
        res(row,2) = dot(cml::row(A,row),cml::col(B,2));
        res(row,3) = dot(cml::row(A,row),cml::col(B,3));
#endif
    }
#endif

#if 0
    (*const_cast<matrix_d44*>(&res))(0,0) = dot(cml::row(A,0),cml::col(B,0));
    (*const_cast<matrix_d44*>(&res))(0,1) = dot(cml::row(A,0),cml::col(B,1));
    (*const_cast<matrix_d44*>(&res))(0,2) = dot(cml::row(A,0),cml::col(B,2));
    (*const_cast<matrix_d44*>(&res))(0,3) = dot(cml::row(A,0),cml::col(B,3));

    (*const_cast<matrix_d44*>(&res))(1,0) = dot(cml::row(A,1),cml::col(B,0));
    (*const_cast<matrix_d44*>(&res))(1,1) = dot(cml::row(A,1),cml::col(B,1));
    (*const_cast<matrix_d44*>(&res))(1,2) = dot(cml::row(A,1),cml::col(B,2));
    (*const_cast<matrix_d44*>(&res))(1,3) = dot(cml::row(A,1),cml::col(B,3));

    (*const_cast<matrix_d44*>(&res))(2,0) = dot(cml::row(A,2),cml::col(B,0));
    (*const_cast<matrix_d44*>(&res))(2,1) = dot(cml::row(A,2),cml::col(B,1));
    (*const_cast<matrix_d44*>(&res))(2,2) = dot(cml::row(A,2),cml::col(B,2));
    (*const_cast<matrix_d44*>(&res))(2,3) = dot(cml::row(A,2),cml::col(B,3));

    (*const_cast<matrix_d44*>(&res))(3,0) = dot(cml::row(A,3),cml::col(B,0));
    (*const_cast<matrix_d44*>(&res))(3,1) = dot(cml::row(A,3),cml::col(B,1));
    (*const_cast<matrix_d44*>(&res))(3,2) = dot(cml::row(A,3),cml::col(B,2));
    (*const_cast<matrix_d44*>(&res))(3,3) = dot(cml::row(A,3),cml::col(B,3));
#endif

#if 1
    res(0,0) = dot(cml::row(A,0),cml::col(B,0));
    res(0,1) = dot(cml::row(A,0),cml::col(B,1));
    res(0,2) = dot(cml::row(A,0),cml::col(B,2));
    res(0,3) = dot(cml::row(A,0),cml::col(B,3));

    res(1,0) = dot(cml::row(A,1),cml::col(B,0));
    res(1,1) = dot(cml::row(A,1),cml::col(B,1));
    res(1,2) = dot(cml::row(A,1),cml::col(B,2));
    res(1,3) = dot(cml::row(A,1),cml::col(B,3));

    res(2,0) = dot(cml::row(A,2),cml::col(B,0));
    res(2,1) = dot(cml::row(A,2),cml::col(B,1));
    res(2,2) = dot(cml::row(A,2),cml::col(B,2));
    res(2,3) = dot(cml::row(A,2),cml::col(B,3));

    res(3,0) = dot(cml::row(A,3),cml::col(B,0));
    res(3,1) = dot(cml::row(A,3),cml::col(B,1));
    res(3,2) = dot(cml::row(A,3),cml::col(B,2));
    res(3,3) = dot(cml::row(A,3),cml::col(B,3));
#endif

    return res;
}
#endif


#if 0
inline matrix_d44
operator^(const matrix_d44& A, const matrix_d44& B)
{
    matrix_d44 res(A);
    res *= B;
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
    for(size_t i = 0; i < n_iter; ++i) {
        /* m = m1*m2*m3 */
        m = m1*m2;
#if 0
        m = m1*m2*m3;
#endif
#if 0
        tmp = mul(m1,m2);
        m = mul(tmp,m3);
#endif
#if 0
        m = mul(m1,m2);
#endif
#if 0
        m = mul(mul(m1,m2),T(m3));
        //mul(m,m1,m2);
        //cmul(m,m1,m2);
        //m = m1^m2;
        //m = cmul(m1,m2);
#endif
#if 0
        m = cmul(m1,m2);
        //cmul(m,m1,m2);
#endif
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
