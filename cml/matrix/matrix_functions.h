/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_functions_h
#define matrix_functions_h

namespace cml {

/** Set the given matrix to the identity matrix.
 *
 * This only makes sense for a square matrix, but no error will be
 * signaled if the matrix is not square.
 *
 * @todo This should return a MatrixXpr to allow loop unrolling, as should
 * the class method.
 */
template<typename E, class AT, typename L>
inline matrix<E,AT,L>&
identity(matrix<E,AT,L>& m)
{
    return m.identity();
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
