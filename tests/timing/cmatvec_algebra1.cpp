/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

inline void add(vector_d4 res, const vector_d4 a, const vector_d4 b)
{
    for(int i = 0; i < 4; ++ i) {
        res[i] = a[i]+b[i];
    }
}

inline void mul(vector_d4 res, const matrix_d44 A, const vector_d4 x)
{
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
	    double sum = A[row][0]*x[0];
	    for(int k = 1; k < 4; ++k) {
		sum += A[row][k]*x[k];
	    }
	    res[row] = sum;
	}
    }
}

inline void mul(vector_d4 res, const vector_d4 x, const matrix_d44 A)
{
    for(int row = 0; row < 4; ++row) {
	for(int col = 0; col < 4; ++col) {
	    double sum = x[0]*A[0][col];
	    for(int k = 1; k < 4; ++k) {
		sum += x[k]*A[k][col];
	    }
	    res[col] = sum;
	}
    }
}

/* The args should *not* be references: */
inline void timed1(
        matrix_d44 m,
        const matrix_d44 m1,
        const matrix_d44 m2,
        const matrix_d44 m3,
        vector_d4 v,
        vector_d4 v1,
        vector_d4 v2,
        vector_d4 v3,
        vector_d4 v4,
        size_t n_iter
        )
{
    vector_d4 t1;
    for(int i = 0; i < n_iter; ++i) {
        add(t1, v, v2);
        mul(v, m1, t1);
    }
}

// -------------------------------------------------------------------------
// vim:ft=cpp
