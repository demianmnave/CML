/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Vector linear expression classes.
 */

#ifndef vector_expr_h
#define vector_expr_h

#include <cml/core/common.h>
#include <cml/core/cml_meta.h>
#include <cml/et/vector_traits.h>
#include <cml/et/vector_promotions.h>
#include <cml/et/size_checking.h>

namespace cml {
namespace et {

/** A placeholder for a vector expression in an expression tree. */
template<class ExprT>
class VectorXpr
{
  public:

    typedef VectorXpr<ExprT> expr_type;

    /* Record ary-ness of the expression: */
    typedef typename ExprT::expr_ary expr_ary;

#if defined(CML_USE_VEC_XPR_REF)
    /* Use a reference to the compiler's VectorXpr<> temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_VEC_XPR_REF

    typedef typename ExprT::value_type value_type;
    typedef vector_result_tag result_tag;
    typedef typename ExprT::size_tag size_tag;

    /* Store the expression traits: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Get the reference type: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Get the result type: */
    typedef typename expr_traits::result_type result_type;


  public:

    /** Record result size as an enum. */
    enum { array_size = ExprT::array_size };


  public:

    /** Return size of this expression (same as subexpression's size). */
    size_t size() const {
        return expr_traits().size(m_expr);
    }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result vector. */
    value_type operator[](size_t i) const {
        return expr_traits().get(m_expr,i);
    }


  public:

    /** Construct from the subexpression to store. */
    explicit VectorXpr(const ExprT& expr) : m_expr(expr) {}

    /** Copy constructor. */
    VectorXpr(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for VectorXpr<>. */
template<class ExprT>
struct ExprTraits< VectorXpr<ExprT> >
{
    typedef VectorXpr<ExprT> expr_type;
    typedef ExprT arg_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A unary vector expression.
 *
 * The operator's operator() method must take exactly one argument.
 */
template<class ExprT, class OpT>
class UnaryVectorOp
{
  public:

    typedef UnaryVectorOp<ExprT,OpT> expr_type;

    /* Record ary-ness of the expression: */
    typedef unary_expression expr_ary;

#if defined(CML_USE_VEC_UNIOP_REF)
    /* Use a reference to the compiler's UnaryVectorOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_VEC_UNIOP_REF

    typedef typename OpT::value_type value_type;
    typedef vector_result_tag result_tag;
    typedef typename ExprT::size_tag size_tag;

    /* Store the expression traits for the subexpression: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Reference type for the subexpression: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Get the result type (same as for subexpression): */
    typedef typename expr_traits::result_type result_type;


  public:

    /** Record result size as an enum. */
    enum { array_size = ExprT::array_size };


  public:

    /** Return size of this expression (same as exprument's size). */
    size_t size() const {
        return expr_traits().size(m_expr);
    }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result vector. */
    value_type operator[](size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the subexpression:
         */
        return OpT().apply(expr_traits().get(m_expr,i));
    }


  public:

    /** Construct from the subexpression. */
    explicit UnaryVectorOp(expr_reference expr) : m_expr(expr) {}

    /** Copy constructor. */
    UnaryVectorOp(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for UnaryVectorOp<>. */
template<class ExprT, class OpT>
struct ExprTraits< UnaryVectorOp<ExprT,OpT> >
{
    typedef UnaryVectorOp<ExprT,OpT> expr_type;
    typedef ExprT arg_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A binary vector expression.
 *
 * The operator's operator() method must take exactly two arguments.
 */
template<class LeftT, class RightT, class OpT>
class BinaryVectorOp
{
  public:

    typedef BinaryVectorOp<LeftT,RightT,OpT> expr_type;

    /* Record ary-ness of the expression: */
    typedef binary_expression expr_ary;

#if defined(CML_USE_VEC_BINOP_REF)
    /* Use a reference to the compiler's BinaryVectorOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_VEC_BINOP_REF

    typedef typename OpT::value_type value_type;
    typedef vector_result_tag result_tag;

    /* Store the expression traits types for the two subexpressions: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Reference types for the two subexpressions: */
    typedef typename left_traits::const_reference left_reference;
    typedef typename right_traits::const_reference right_reference;

    /* Figure out the expression's resulting (vector) type: */
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename VectorPromote<left_result,right_result>::type result_type;
    typedef typename result_type::size_tag size_tag;

    /* Define a size checker: */
    typedef GetCheckedSize<LeftT,RightT,result_tag> checked_size;


  public:

    /** Record result size as an enum (if applicable). */
    enum { array_size = result_type::array_size };


  public:

    /** Return the size of the vector result.
     *
     * @throws std::invalid_argument if the expressions do not have the same
     * size.
     */
    size_t size() const {
#if defined(CML_CHECK_VECTOR_EXPR_SIZES)
        return checked_size()(m_left,m_right);
#else
        return left_traits().size(m_left);
#endif
    }

    /** Return reference to left expression. */
    left_reference left_expression() const { return m_left; }

    /** Return reference to right expression. */
    right_reference right_expression() const { return m_right; }

    /** Compute value at index i of the result vector. */
    value_type operator[](size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the two subexpressions:
         */
        return OpT().apply(
                left_traits().get(m_left,i),
                right_traits().get(m_right,i));
    }


  public:

    /** Construct from the two subexpressions.
     *
     * @throws std::invalid_argument if the subexpression sizes don't
     * match.
     *
     * @bug The constructor ensures that left and right have the same size
     * through CheckLinearExprSizes.  For dynamically-allocated arrays this
     * could become very costly, since the check happens at each call to
     * the BinaryVectorOp constructor.
     */
    explicit BinaryVectorOp(left_reference left, right_reference right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    BinaryVectorOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* This ensures that a compile-time size check is executed: */
    typename checked_size::compile_time_check _dummy;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for BinaryVectorOp<>. */
template<class LeftT, class RightT, class OpT>
struct ExprTraits< BinaryVectorOp<LeftT,RightT,OpT> >
{
    typedef BinaryVectorOp<LeftT,RightT,OpT> expr_type;
    typedef LeftT left_type;
    typedef RightT right_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};

/* Helper struct to verify that both arguments are vector expressions: */
template<typename LeftTraits, typename RightTraits>
struct VectorExpressions
{
    /* Require that both arguments are vector expressions: */
    typedef typename LeftTraits::result_tag left_result;
    typedef typename RightTraits::result_tag right_result;
    enum { is_true = (same_type<left_result,et::vector_result_tag>::is_true
            && same_type<right_result,et::vector_result_tag>::is_true) };
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
