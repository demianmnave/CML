/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  Define a matrix multiplication expression tree node.
 *
 * @todo Allow multiplication of matrices with different element types.
 */

#if !defined(cml_matrix_h)
#error "This should only be included from cml/matrix.h"
#else

#ifndef matrix_mult_h
#define matrix_mult_h

#include <cml/et/traits.h>
#include <cml/et/size_checking.h>

/** A class that computes the product of two matrices.
 *
 * This uses the naive, O(n^3) matrix multiplication algorithm, and each
 * element is recomputed (not stored) when requested.
 *
 * @todo A blocked version of this class can be used when computing
 * directly into a matrix<> instance (e.g. a temporary or user-instantiated
 * matrix<>).
 *
 * XXX Need to verify the number of rows and cols of the arguments!
 */
template<class LeftT, class RightT>
class MatrixProductOp
{
    typedef MatrixProductOp<LeftT,RightT> expr_type;

#if defined(CML_USE_MAT_BINOP_REF)
    /* Use a reference to the compiler's MatrixProductOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the MatrixProductOp expression by value into parent expression
     * tree nodes:
     */
    typedef expr_type expr_const_reference;
#endif // CML_USE_MAT_BINOP_REF

    /* XXX This should be deduced by type promotion! */
    typedef typename LeftT::value_type value_type;

    typedef matrix_result_tag result_tag;

    /* Record the expression traits for the two subexpressions: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Reference types for the two subexpressions: */
    typedef typename left_traits::const_reference left_reference;
    typedef typename right_traits::const_reference right_reference;


  public:

    /** Record result size as an enum (if applicable). */
    enum { array_rows = LeftT::array_rows, array_cols = RightT::array_cols };


  public:

    /** Return number of rows in the result. */
    size_t rows() const {
        return left_traits().rows(m_left);
    }

    /** Return number of cols in the result. */
    size_t cols() const {
        return right_traits().cols(m_right);
    }

    /** Return value at index i of the result matrix. */
    value_type operator()(size_t i) const {
    }

    /** Compute value at index i,j of the result vector. */
    value_type operator()(size_t i, size_t j) const {
    }


  public:

    /** Construct from the two subexpressions. */
    MatrixProductOp(const LeftT& left, const RightT& right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    MatrixProductOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Create a matrix multiplication node between two matrices.
 *
 * This function is more complex than other expression node generators,
 * since it has to support matrices with different array storage types.
 */
inline template<typename E, class AT1, typename O1, class AT2, typename O2>
cml::et::MatrixXpr<
   cml::et::MatrixProductOp<
       cml::matrix<E,AT1,O1>,
       cml::matrix<E,AT2,O2>
   >
operator*(const cml::matrix<E,AT1,O1>& left,
          const cml::matrix<E,AT2,O2>& right)
{
    typedef cml::et::MatrixProductOp<
            cml::matrix<E,AT1,O1>,
            cml::matrix<E,AT2,O2>
        > ExprT;
    return cml::et::MaxtrixXpr<ExprT>(ExprT(left,right));
}

#endif

#endif // !defined(cml_vector_h)

// -------------------------------------------------------------------------
// vim:ft=cpp
