/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Compute the determinant of a square matrix using LU factorization.
 *
 *  @todo This should be specialized on the matrix size for small matrices.
 */

#ifndef determinant_h
#define determinant_h

namespace cml {

/** Determinant of a matrix. */
template<typename E, class AT, class L> inline E
determinant(const matrix<E,AT,L>& m)
{
    /* Compute the LU factorization: */
    typename matrix<E,AT,L>::temporary_type M = lu(m);

    /* The product of the diagonal entries is the determinant: */
    double det = M(0,0);
    for(size_t i = 1; i < M.rows(); ++ i)
        det *= M(i,i);
    return det;
}

/** Determinant of a matrix expression. */
template<typename XprT> inline typename XprT::value_type
determinant(const et::MatrixXpr<XprT>& e)
{
    /* Compute the LU factorization: */
    typename et::MatrixXpr<XprT>::temporary_type M = lu(e);

    /* The product of the diagonal entries is the determinant: */
    double det = M(0,0);
    for(size_t i = 1; i < M.rows(); ++ i)
        det *= M(i,i);
    return det;
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
