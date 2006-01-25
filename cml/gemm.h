/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Multiply two matrices.
 */

#ifndef	gemm_h
#define	gemm_h

#if 0
#include <cml/detail/gemm_return_type.h>
#include <cml/matrix.h>

namespace cml
{

/** General matrix multiplication.
 *
 * Compute C = A x B, where A and B have the same type.
 *
 * This function implements the O(n^3) matrix multiplication algorithm without
 * blocking, and will therefore be slow for large matrices.
 *
 * @param C result matrix.
 * @param A first matrix.
 * @param B second matrix.
 *
 * @note No checking is done to ensure the proper dimensions.  This is left to
 * the caller (or compiler for fixed-memory matrices).
 *
 * @todo Blocking might speed up 2Nx2M matrix multiplication by taking better
 * advantage of the CPU cache, particularly for N=M=2.
 *
 * @internal GEMM is the Lapack name for general matrix product.  We're using
 * it here, even though there is no scaling parameter for our function (yet).
 */
template<class MatC, class MatA, class MatB> inline void
gemm(MatC& C, const MatA& A, const MatB& B)
{
    typedef typename MatC::value_type value_type;
    for(size_t row = 0; row < A.rows(); ++row) {
        for(size_t col = 0; col < B.cols(); ++col) {
            value_type sum(A(row,0)*B(0,col));
            for(size_t k = 1; k < B.rows(); ++k) {
                sum = sum + (A(row,k)*B(k,col));
            }
            C(row,col) = sum;
        }
    }
}

/** Dispatch to GEMM for a fixed-memory return type. */
template<class MatA, class MatB> inline
typename detail::gemm_return_type<MatA,MatB>::return_type
gemm_dispatch(const MatA& A, const MatB& B, core::fixed_memory_tag)
{
    typedef typename detail::gemm_return_type<MatA,MatB>::return_type Mat3;
    Mat3 C;
    gemm(C,A,B);
    return C;
}

/** Dispatch to GEMM for a dynamic-memory return type. */
template<class MatA, class MatB> inline
typename detail::gemm_return_type<MatA,MatB>::return_type
gemm_dispatch(const MatA& A, const MatB& B, core::dynamic_memory_tag)
{
    typedef typename detail::gemm_return_type<MatA,MatB>::return_type Mat3;
    Mat3 C(A.rows(),B.cols());
    gemm(C,A,B);
    return C;
}

/** Compute the product of two matrices of arbitrary type.
 *
 * The return type is automatically deduced based upon the parameter types.
 * This is mostly useful when using matrix expressions.  This actually calls
 * gemm_dispatch to multiply the matrices and return the proper type.
 *
 * @param A the first matrix.
 * @param B the second matrix.
 * @returns the product of A and B.
 *
 * @sa cml::gemm<class MatC, class MatA, class MatB>
 */
template<class MatA, class MatB> inline
typename detail::gemm_return_type<MatA,MatB>::return_type
gemm(const MatA& A, const MatB& B)
{
    typename detail::gemm_return_type<MatA,MatB>::memory_type memory_tag;
    return gemm_dispatch(A,B,memory_tag);
}

/** Matrix multiplication with algebraic notation.
 *
 * Compute the matrix product C = A x B using algebraic notation.
 *
 * @param A first matrix.
 * @param B second matrix.
 * @returns the matrix product.
 *
 * @sa cml::gemm<class MatA, class MatB>
 * @sa cml::gemm<class MatC, class MatA, class MatB>
 *
 * @bug This should verify dimensions for dynamic matrices.
 *
 * @internal Do not move this inside the matrix class, and do not use
 * operator*=().  Making operator*=() work correctly is not easy to do, and
 * would likely slow things down.
 *
 * @internal This <em>must</em> be inlined to ensure that NRVO works corre
 */
template<class MatA, class MatB>
typename detail::gemm_return_type<MatA,MatB>::return_type
operator*(const MatA& A, const MatB& B)
{
    typedef typename detail::gemm_return_type<MatA,MatB>::return_type MatC;
    typedef typename MatA::value_type value_type;

    /* Call gemm to compute the product: */
    //gemm(C,A,B);

    //std::cerr << "in*!" << std::endl;
    //MatC C(A);
    MatC C;
    for(size_t row = 0; row < A.rows(); ++row) {
        for(size_t col = 0; col < B.cols(); ++col) {
            value_type sum(A(row,0)*B(0,col));
            for(size_t k = 1; k < B.rows(); ++k) {
                sum = sum + (A(row,k)*B(k,col));
            }
            C(row,col) = sum;
        }
    }
    return C;
}

} // namespace cml
#endif

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
