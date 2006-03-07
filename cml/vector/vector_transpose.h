/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef vector_transpose_h
#define vector_transpose_h

#include <cml/vector/vector_expr.h>

#define VECTOR_TRANSPOSE_RETURNS_TEMP

namespace cml {
namespace et {

/** "Transpose" the given vector expression.
 *
 * This does nothing more than change the result type of the expression
 * into one with the opposite orientation (i.e. row->col, col->row).
 */
template<class ArgT>
class VectorTransposeOp
{
  public:

    typedef VectorTransposeOp<ArgT> expr_type;

    /* Record ary-ness of the expression: */
    typedef unary_expression expr_ary;

#if defined(CML_USE_VEC_XPR_REF)
    /* Use a reference to the compiler's VectorTransposeOp<> temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_VEC_XPR_REF

    typedef typename ArgT::value_type value_type;
    typedef vector_result_tag result_tag;
    typedef typename ArgT::size_tag size_tag;

    /* Store the expression traits: */
    typedef ExprTraits<ArgT> expr_traits;

    /* Get the reference type: */
    typedef typename expr_traits::const_reference arg_reference;

    /* Swap the orientation tag for the result type: */
    typedef typename expr_traits::result_type::transposed_type result_type;

    /* Get the temporary type: */
    typedef typename result_type::temporary_type temporary_type;


  public:

    /** Record result size as an enum. */
    enum { array_size = ArgT::array_size };


  public:

    /** Return size of this expression (same as subexpression's size). */
    size_t size() const {
        return expr_traits().size(m_expr);
    }

    /** Return reference to contained expression. */
    arg_reference expression() const { return m_expr; }

    /** Compute value at index i of the result vector. */
    value_type operator[](size_t i) const {
        return expr_traits().get(m_expr,i);
    }


  public:

    /** Construct from the subexpression to store. */
    explicit VectorTransposeOp(arg_reference expr) : m_expr(expr) {}

    /** Copy constructor. */
    VectorTransposeOp(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    arg_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for VectorTransposeOp<>. */
template<class ExprT>
struct ExprTraits< VectorTransposeOp<ExprT> >
{
    typedef VectorTransposeOp<ExprT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};

} // namespace et


/* Define the transpose operators in the cml namespace: */
#if defined(VECTOR_TRANSPOSE_RETURNS_TEMP)

/** Vector transpose operator taking a vector operand. */
template<typename E, class AT, class O>
typename et::VectorTransposeOp<
    vector<E,AT,O>
>::temporary_type
transpose(const vector<E,AT,O>& expr)
{
    /* Record the vector type: */
    typedef vector<E,AT,O> vector_type;

    /* Record the type of the transpose op: */
    typedef et::VectorTransposeOp<vector_type> Op;

    /* Determine the returned vector type: */
    typedef typename et::VectorTransposeOp<
        vector_type
    >::temporary_type tmp_type;

    /* The expression to use to assign the temporary: */
    typedef et::VectorXpr<Op> ExprT;

    /* Create the temporary and return it: */
    tmp_type tmp;
    cml::et::detail::Resize(tmp, expr.size(),
            typename tmp_type::size_tag());
    tmp = ExprT(Op(expr));
    return tmp;
}

/** Vector transpose operator taking an et::VectorXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpression of the VectorTransposeOp.
 */
template<class XprT>
typename et::VectorTransposeOp<
    XprT
>::temporary_type
transpose(const et::VectorXpr<XprT>& expr)
{
    /* Record the type of the transpose op: */
    typedef et::VectorTransposeOp<XprT> Op;

    /* Determine the returned vector type: */
    typedef typename et::VectorTransposeOp<XprT>::temporary_type tmp_type;

    /* The expression to use to assign the temporary: */
    typedef et::VectorXpr<Op> ExprT;

    /* Create the temporary and return it: */
    tmp_type tmp;
    cml::et::detail::Resize(tmp, expr.size(),
            typename tmp_type::size_tag());
    tmp = ExprT(Op(expr.expression()));
    return tmp;
}


/* For notational convenience: */

/** Vector transpose operator taking a vector operand. */
template<typename E, class AT, class O>
typename et::VectorTransposeOp<
    vector<E,AT,O>
>::temporary_type
T(const vector<E,AT,O>& expr)
{
    return transpose(expr);
}

/** Vector transpose operator taking an et::VectorXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpression of the VectorTransposeOp.
 */
template<class XprT>
typename et::VectorTransposeOp<
    XprT
>::temporary_type
T(const et::VectorXpr<XprT>& expr)
{
    return transpose(expr);
}

#else

/** Vector transpose operator taking a vector operand. */
template<typename E, class AT, class O>
et::VectorXpr< et::VectorTransposeOp< vector<E,AT,O> > >
transpose(const vector<E,AT,O>& expr)
{
    typedef et::VectorTransposeOp< vector<E,AT,O> > ExprT;
    return et::VectorXpr<ExprT>(ExprT(expr));
}

/** Vector transpose operator taking an et::VectorXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpression of the VectorTransposeOp.
 */
template<class XprT>
et::VectorXpr< et::VectorTransposeOp<XprT> >
transpose(const et::VectorXpr<XprT>& expr)
{
    typedef et::VectorTransposeOp<XprT> ExprT;
    return et::VectorXpr<ExprT>(ExprT(expr.expression()));
}


/* For notational convenience: */

/** Vector transpose operator taking a vector operand. */
template<typename E, class AT, class O>
et::VectorXpr< et::VectorTransposeOp< vector<E,AT,O> > >
T(const vector<E,AT,O>& expr)
{
    return transpose(expr);
}

/** Vector transpose operator taking an et::VectorXpr operand.
 *
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpression of the VectorTransposeOp.
 */
template<class XprT>
et::VectorXpr< et::VectorTransposeOp<XprT> >
T(const et::VectorXpr<XprT>& expr)
{
    return transpose(expr);
}

#endif

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
