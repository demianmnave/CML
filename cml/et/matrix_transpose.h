/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_transpose_h
#define matrix_transpose_h

#include <cml/et/matrix_expr.h>

namespace cml {
namespace et {

/** "Transpose" the given matrix expression.
 *
 * This does nothing more than change the result type of the expression
 * into one with the opposite orientation (i.e. row->col, col->row).
 */
template<class ArgT>
class MatrixTransposeOp
{
  public:

    typedef MatrixTransposeOp<ArgT> expr_type;

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

    typedef typename ArgT::value_type value_type;
    typedef matrix_result_tag result_tag;
    typedef typename ArgT::size_tag size_tag;

    /* Store the expression traits: */
    typedef ExprTraits<ArgT> expr_traits;

    /* Get the reference type: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Swap the orientation tag: */
    typedef typename expr_traits::result_type::transposed_type result_type;


  public:

    /** Record result size as an enum. */
    enum {
        array_rows = ArgT::array_rows,
        array_cols = ArgT::array_cols
    };


  public:

    /** Return result rows. */
    size_t rows() const {
        return expr_traits().rows(m_expr);
    }

    /** Return result cols. */
    size_t cols() const {
        return expr_traits().cols(m_expr);
    }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result matrix. */
    value_type operator()(size_t i, size_t j) const {
        return expr_traits().get(m_expr,i,j);
    }


  public:

    /** Construct from the subexpression to store. */
    explicit MatrixTransposeOp(const ArgT& expr) : m_expr(expr) {}

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

    value_type get(const expr_type& m, size_t i, size_t j) const {
        return m(i,j);
    }

    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};

} // namespace et


/* Define the transpose operators in the cml namespace: */

/** Matrix transpose operator taking a matrix operand. */
template<typename E, class AT, class O>
inline et::MatrixXpr< et::MatrixTransposeOp< matrix<E,AT,O> > >
transpose(const matrix<E,AT,O>& arg)
{
    typedef et::MatrixTransposeOp< matrix<E,AT,O> > ExprT;
    return et::MatrixXpr<ExprT>(ExprT(arg));
}

/** Matrix transpose operator taking an et::MatrixXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the MatrixTransposeOp.
 */
template<class XprT>
inline et::MatrixXpr< et::MatrixTransposeOp<XprT> >
transpose(const et::MatrixXpr<XprT>& arg)
{
    typedef et::MatrixTransposeOp<XprT> ExprT;
    return et::MatrixXpr<ExprT>(ExprT(arg.expression()));
}


/* For notational convenience: */

/** Matrix transpose operator taking a matrix operand. */
template<typename E, class AT, class O>
inline et::MatrixXpr< et::MatrixTransposeOp< matrix<E,AT,O> > >
T(const matrix<E,AT,O>& arg)
{
    return transpose(arg);
}

/** Matrix transpose operator taking an et::MatrixXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the MatrixTransposeOp.
 */
template<class XprT>
inline et::MatrixXpr< et::MatrixTransposeOp<XprT> >
T(const et::MatrixXpr<XprT>& arg)
{
    return transpose(arg);
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
