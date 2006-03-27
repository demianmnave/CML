/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Compute the inverse of a matrix by LU factorization.
 *
 * @internal This can probably be sped up a lot by using a dedicated function,
 * rather than lu_solve(), to compute the inverse.
 *
 * @internal inverse() should be specialized for small matrices.
 */

#ifndef inverse_h
#define inverse_h

#include <cml/et/size_checking.h>
#include <cml/matrix/matrix_expr.h>

namespace cml {
namespace detail {

/* Compute inverse of an LU-factored matrix: */
template<typename MatT> inline
typename MatT::temporary_type
lu_inverse(const MatT& LU)
{
    /* Shorthand. */
    typedef typename MatT::value_type value_type;

    /* Get size of the matrix: */
    size_t N = LU.rows();

    typename MatT::temporary_type Inv;
    cml::et::detail::Resize(Inv,N,N);

    typename MatT::col_vector_type v, x;
    cml::et::detail::Resize(v,N);
    for(size_t i = 0; i < N; ++i)
        v[i] = value_type(0);
    /* XXX Need a fill() function here. */

    /* Use lu_solve to solve M*x = v for x, where v = [0 ... 1 ... 0]^T: */
    for(size_t i = 0; i < N; ++i) {
        v[i] = 1.;
        x = lu_solve(LU,v);
        v[i] = 0.;

        /* x is column i of the inverse of LU: */
        for(size_t k = 0; k < N; ++ k) {
            Inv(k,i) = x[k];
        }
    }

    return Inv;
}

} // namespace detail

/** Inverse of a square matrix. */
template<typename E, class AT, class L> inline
typename matrix<E,AT,L>::temporary_type
inverse(const matrix<E,AT,L>& A)
{
    /* Compute the LU factorization (lu verifies that A is square): */
    typename matrix<E,AT,L>::temporary_type M = lu(A);
    return detail::lu_inverse(M);
}

/** Inverse of a square matrix expression. */
template<typename XprT> inline
typename et::MatrixXpr<XprT>::temporary_type
inverse(const et::MatrixXpr<XprT>& e)
{
    /* Compute the LU factorization (lu verifies that A is square): */
    typename et::MatrixXpr<XprT>::temporary_type M = lu(e);
    return detail::lu_inverse(M);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
