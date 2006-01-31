/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Vector expression classes.
 */

#ifndef vector_expr_h
#define vector_expr_h

#include <cml/common.h>
#include <cml/et/vector_traits.h>
#include <cml/et/vector_promotions.h>
#include <cml/et/size_checking.h>

namespace cml {

/* Forward declare for the vector expressions below: */
template<typename Element, class ArrayType> class vector;

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
    typedef typename ExprT::size_tag size_tag;  // Just inherit size type.

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
    VectorXpr(const ExprT& expr) : m_expr(expr) {}

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
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A unary vector expression.
 *
 * The operator must take exactly one argument.
 */
template<class ArgT, class OpT>
class UnaryVectorOp
{
  public:

    typedef UnaryVectorOp<ArgT,OpT> expr_type;

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
    typedef typename ArgT::size_tag size_tag;  // Just inherit size type.

    /* Store the expression traits for the subexpression: */
    typedef ExprTraits<ArgT> arg_traits;

    /* Reference type for the subexpression: */
    typedef typename arg_traits::const_reference arg_reference;

    /* Get the result type (same as for subexpression): */
    typedef typename arg_traits::result_type result_type;


  public:

    /** Record result size as an enum. */
    enum { array_size = ArgT::array_size };


  public:

    /** Return size of this expression (same as argument's size). */
    size_t size() const {
        return arg_traits().size(m_arg);
    }

    /** Compute value at index i of the result vector. */
    value_type operator[](size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the subexpression:
         */
        return OpT().apply(arg_traits().get(m_arg,i));
    }


  public:

    /** Construct from the subexpression. */
    UnaryVectorOp(const ArgT& arg)
        : m_arg(arg) {}

    /** Copy constructor. */
    UnaryVectorOp(const expr_type& e)
        : m_arg(e.m_arg) {}


  protected:

    arg_reference m_arg;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for UnaryVectorOp<>. */
template<class ArgT, class OpT>
struct ExprTraits< UnaryVectorOp<ArgT,OpT> >
{
    typedef UnaryVectorOp<ArgT,OpT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A binary vector expression. */
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

    /* A checker to verify the argument sizes at compile- or run-time. This
     * automatically checks fixed-size vectors at compile time:
     */
    typedef CheckVectorSizes<LeftT,RightT> check_size;

    /* Figure out the result size and type based on the subexpressions: */
    typedef DeduceVectorExprSize<LeftT,RightT> deduce_size;
    typedef typename deduce_size::tag size_tag;

    /* Figure out the expression's resulting (vector) type: */
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename VectorPromote<left_result,right_result>::type result_type;


  public:

    /** Record result size as an enum (if applicable). */
    enum { array_size = result_type::array_size };


  public:

    /** Return the size of the vector result. */
    size_t size() const {
        return deduce_size()(m_left,m_right);
    }

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

    /** Construct from the two subexpressions. */
    BinaryVectorOp(const LeftT& left, const RightT& right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    BinaryVectorOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for BinaryVectorOp<>. */
template<class LeftT, class RightT, class OpT>
struct ExprTraits< BinaryVectorOp<LeftT,RightT,OpT> >
{
    typedef BinaryVectorOp<LeftT,RightT,OpT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A binary vector reduction expression.
 *
 * Both operators must take two arguments, and the resulting type of
 * the reduction operator must be 0-assignable.
 *
 * @internal The result of a reduction operation should be stored as a
 * temporary in the expression tree, otherwise it will be recomputed on
 * each call.
 */
template<class LeftT, class RightT, class OpT, class ReduceT>
class BinaryVectorReductionOp
{
  public:

    typedef BinaryVectorReductionOp<LeftT,RightT,OpT,ReduceT> expr_type;

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

    typedef typename ReduceT::value_type value_type;
    typedef scalar_result_tag result_tag;

    /* Store the expression traits types for the two subexpressions: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Reference types for the two subexpressions: */
    typedef typename left_traits::const_reference left_reference;
    typedef typename right_traits::const_reference right_reference;

    /* A checker to verify the argument sizes at compile- or run-time. This
     * automatically checks fixed-size vectors at compile time:
     */
    typedef CheckVectorSizes<LeftT,RightT> check_size;

    /* Figure out the number of elements to reduce: */
    typedef DeduceVectorExprSize<LeftT,RightT> deduce_size;

    /* Always unit size: */
    typedef unit_size_tag size_tag;

    /* The expression's resulting (vector) type: */
    typedef typename ReduceT::value_type result_type;


  public:

    /** Record result size. */
    enum { array_size = 1 };


  public:

    /** Return the size of the vector result. */
    size_t size() const {
        return 1;
    }

    /** Compute value of the reduction operator.
     *
     * @internal Should the loop be unrolled automatically?
     */
    value_type operator()() const {

        /* Figure out the result size and type based on the subexpressions.
         * This automatically verifies at run-time that dynamic-size
         * vectors have the same length:
         */
        size_t sz = deduce_size()(m_left,m_right);

        /* Loop through and compute the reduction: */
        value_type result(0);
        for(size_t i = 0; i < sz; ++i) {
            result = ReduceT().apply(
                    result,
                    OpT().apply(
                        left_traits().get(m_left,i),
                        right_traits().get(m_right,i))
                    );
        }

        return result;
    }


  public:

    /** Construct from the two subexpressions. */
    BinaryVectorReductionOp(const LeftT& left, const RightT& right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    BinaryVectorReductionOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for BinaryVectorOp<>. */
template<class LeftT, class RightT, class OpT, class ReduceT>
struct ExprTraits< BinaryVectorReductionOp<LeftT,RightT,OpT,ReduceT> >
{
    typedef BinaryVectorReductionOp<LeftT,RightT,OpT,ReduceT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

    value_type get(const expr_type& v, size_t) const { return v(); }
    size_t size(const expr_type& e) const { return e.size(); }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
