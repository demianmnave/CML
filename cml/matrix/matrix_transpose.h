/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  @todo Currently, the transpose() and T() functions copy the transposed
 *  result into a temporary, and return it to avoid aliasing problems, e.g.
 *  C = transpose(C).  By checking for C on the right-hand side, this can
 *  be avoided, but experimentation is needed to determine the impact on
 *  performance.  Another option is to use a function to explicitly specify
 *  when a temporary is needed; e.g. C = transpose(temp(C)).
 */

#ifndef matrix_transpose_h
#define matrix_transpose_h

#include <cml/et/size_checking.h>
#include <cml/matrix/matrix_promotions.h>
#include <cml/matrix/matrix_expr.h>

#define MATRIX_TRANSPOSE_RETURNS_TEMP

namespace cml {
namespace et {

/** "Transpose" the given matrix expression.
 *
 * This does nothing more than change the result type of the expression
 * into one with the opposite orientation (i.e. row->col, col->row).
 */
template<class ExprT>
class MatrixTransposeOp
{
  public:

    typedef MatrixTransposeOp<ExprT> expr_type;

    /* Record ary-ness of the expression: */
    typedef unary_expression expr_ary;

#if defined(CML_USE_MAT_XPR_REF)
    /* Use a reference to the compiler's MatrixTransposeOp<> temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_VEC_XPR_REF

    typedef typename ExprT::value_type value_type;
    typedef matrix_result_tag result_tag;
    typedef typename ExprT::size_tag size_tag;

    /* Store the expression traits: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Get the reference type: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Swap the orientation: */
    typedef typename expr_traits::result_type::transposed_type result_type;

    /* Get the temporary type: */
    typedef typename result_type::temporary_type temporary_type;


  public:

    /** Record result size as an enum. */
    enum {
        array_rows = result_type::array_rows,
        array_cols = result_type::array_cols
    };


  public:

    /** Return the expression size as a pair. */
    matrix_size size() const {
        return matrix_size(this->rows(),this->cols());
    }

    /** Return result rows.
     *
     * The tranpose has the same number of rows as the original has
     * columns.
     */
    size_t rows() const {
        return expr_traits().cols(m_expr);
    }

    /** Return result cols.
     *
     * The tranpose has the same number of columns as the original has
     * rows.
     */
    size_t cols() const {
        return expr_traits().rows(m_expr);
    }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result matrix.
     *
     * Element (i,j) of the transpose is element (j,i) of the original
     * expression.
     */
    value_type operator()(size_t i, size_t j) const {
        return expr_traits().get(m_expr,j,i);
    }


  public:

    /** Construct from the subexpression to store. */
    explicit MatrixTransposeOp(const ExprT& expr) : m_expr(expr) {}

    /** Copy constructor. */
    MatrixTransposeOp(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for VectorTransposeOp<>. */
template<class ExprT>
struct ExprTraits< MatrixTransposeOp<ExprT> >
{
    typedef MatrixTransposeOp<ExprT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& m, size_t i, size_t j) const {
        return m(i,j);
    }

    matrix_size size(const expr_type& e) const { return e.size(); }
    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};

} // namespace et


/* Define the transpose operators in the cml namespace: */
#if defined(MATRIX_TRANSPOSE_RETURNS_TEMP)

/** Matrix transpose operator taking a matrix operand. */
template<typename E, class AT, typename L>
typename et::MatrixTransposeOp<
    matrix<E,AT,L>
>::temporary_type
transpose(const matrix<E,AT,L>& expr)
{
    /* Record the matrix type: */
    typedef matrix<E,AT,L> matrix_type;

    /* Record the type of the transpose op: */
    typedef et::MatrixTransposeOp<matrix_type> Op;

    /* Determine the returned matrix type: */
    typedef typename et::MatrixTransposeOp<
        matrix_type
    >::temporary_type tmp_type;

    /* The expression to use to assign the temporary: */
    typedef et::MatrixXpr<Op> ExprT;

    /* Create the temporary and return it: */
    tmp_type tmp;
    cml::et::detail::Resize(tmp,expr.rows(),expr.cols(),
            typename tmp_type::size_tag());
    tmp = ExprT(Op(expr));
    return tmp;
}

/** Matrix transpose operator taking an et::MatrixXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the MatrixTransposeOp.
 */
template<class XprT>
typename et::MatrixTransposeOp<
    XprT
>::temporary_type
transpose(const et::MatrixXpr<XprT>& expr)
{
    /* Record the type of the transpose op: */
    typedef et::MatrixTransposeOp<XprT> Op;

    /* Determine the returned matrix type: */
    typedef typename et::MatrixTransposeOp<XprT>::temporary_type tmp_type;

    /* The expression to use to assign the temporary: */
    typedef et::MatrixXpr<Op> ExprT;

    /* Create the temporary and return it: */
    tmp_type tmp;
    cml::et::detail::Resize(tmp,expr.rows(),expr.cols(),
            typename tmp_type::size_tag());
    tmp = ExprT(Op(expr));
    return tmp;
}


/* For notational convenience: */

/** Matrix transpose operator taking a matrix operand. */
template<typename E, class AT, typename L>
typename et::MatrixTransposeOp<
    matrix<E,AT,L>
>::temporary_type
T(const matrix<E,AT,L>& expr)
{
    return transpose(expr);
}

/** Matrix transpose operator taking an et::MatrixXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the MatrixTransposeOp.
 */
template<class XprT>
typename et::MatrixTransposeOp<
    XprT
>::temporary_type
T(const et::MatrixXpr<XprT>& expr)
{
    return transpose(expr);
}

#else

/** Matrix transpose operator taking a matrix operand. */
template<typename E, class AT, typename L>
et::MatrixXpr< et::MatrixTransposeOp< matrix<E,AT,L> > >
transpose(const matrix<E,AT,L>& expr)
{
    typedef et::MatrixTransposeOp< matrix<E,AT,L> > ExprT;
    return et::MatrixXpr<ExprT>(ExprT(expr));
}

/** Matrix transpose operator taking an et::MatrixXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the MatrixTransposeOp.
 */
template<class XprT>
et::MatrixXpr< et::MatrixTransposeOp<XprT> >
transpose(const et::MatrixXpr<XprT>& expr)
{
    typedef et::MatrixTransposeOp<XprT> ExprT;
    return et::MatrixXpr<ExprT>(ExprT(expr.expression()));
}


/* For notational convenience: */

/** Matrix transpose operator taking a matrix operand. */
template<typename E, class AT, typename L>
et::MatrixXpr< et::MatrixTransposeOp< matrix<E,AT,L> > >
T(const matrix<E,AT,L>& expr)
{
    return transpose(expr);
}

/** Matrix transpose operator taking an et::MatrixXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the MatrixTransposeOp.
 */
template<class XprT>
et::MatrixXpr< et::MatrixTransposeOp<XprT> >
T(const et::MatrixXpr<XprT>& expr)
{
    return transpose(expr);
}

#endif

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
