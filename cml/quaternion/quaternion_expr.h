/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef quaternion_expr_h
#define quaternion_expr_h

#include <cml/et/size_checking.h>
#include <cml/quaternion/quaternion_traits.h>
#include <cml/quaternion/quaternion_promotions.h>

#define QUATXPR_ARG_TYPE  const et::QuaternionXpr<XprT>&
#define QUATXPR_ARG_TYPE_N(_N_)  const et::QuaternionXpr<XprT##_N_>&

namespace cml {
namespace et {

/** A placeholder for a quaternion expression in an expression tree. */
template<class ExprT>
class QuaternionXpr
{
  public:

    typedef QuaternionXpr<ExprT> expr_type;

    /* Record ary-ness of the expression: */
    typedef typename ExprT::expr_ary expr_ary;

    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;

    typedef typename ExprT::value_type value_type;
    typedef quaternion_result_tag result_tag;
    typedef typename ExprT::size_tag size_tag;

    /* Store the expression traits: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Get the reference type: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Get the result type: */
    typedef typename expr_traits::result_type result_type;

    /* For matching by assignability: */
    typedef cml::et::not_assignable_tag assignable_tag;

    /* Get the temporary type: */
    typedef typename result_type::temporary_type temporary_type;


  public:

    /** Record result size as an enum. */
    enum { array_size = ExprT::array_size };


  public:

    /** Return size of this expression (same as subexpression's size). */
    size_t size() const {
        return m_expr.size();
    }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result quaternion. */
    value_type operator[](size_t i) const {
        return m_expr[i];
    }

    /** Return the real part of the expression. */
    value_type real() const {
        return m_expr.real();
    }

    /** Return the vector part of the expression. */
    result_type imaginary() const {
        return m_expr.imaginary();
    }


  public:

    /** Construct from the subexpression to store. */
    explicit QuaternionXpr(expr_reference expr) : m_expr(expr) {}

    /** Copy constructor. */
    QuaternionXpr(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for QuaternionXpr<>. */
template<class ExprT>
struct ExprTraits< QuaternionXpr<ExprT> >
{
    typedef QuaternionXpr<ExprT> expr_type;
    typedef ExprT arg_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef typename expr_type::assignable_tag assignable_tag;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A unary quaternion expression.
 *
 * The operator's operator() method must take exactly one argument.
 */
template<class ExprT, class OpT>
class UnaryQuaternionOp
{
  public:

    typedef UnaryQuaternionOp<ExprT,OpT> expr_type;

    /* Record ary-ness of the expression: */
    typedef unary_expression expr_ary;

    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;

    typedef typename OpT::value_type value_type;
    typedef quaternion_result_tag result_tag;
    typedef typename ExprT::size_tag size_tag;

    /* Store the expression traits for the subexpression: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Reference type for the subexpression: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Get the result type (same as for subexpression): */
    typedef typename expr_traits::result_type result_type;

    /* For matching by assignability: */
    typedef cml::et::not_assignable_tag assignable_tag;

    /* Get the temporary type: */
    typedef typename result_type::temporary_type temporary_type;


  public:

    /** Record result size as an enum. */
    enum { array_size = ExprT::array_size };


  public:

    /** Return size of this expression (same as argument's size). */
    size_t size() const {
        return m_expr.size();
    }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result quaternion. */
    value_type operator[](size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the subexpression:
         */
        return OpT().apply(expr_traits().get(m_expr,i));
    }

    /** Return the real part of the expression. */
    value_type real() const {
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        return (*this)[0];
#else
        return (*this)[3];
#endif
    }

    /** Return the vector part of the expression. */
    result_type imaginary() const {
        result_type v;
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        v[0] = (*this)[1]; v[1] = (*this)[2]; v[2] = (*this)[3];
#else
        v[0] = (*this)[0]; v[1] = (*this)[1]; v[2] = (*this)[2];
#endif
        return v;
    }


  public:

    /** Construct from the subexpression. */
    explicit UnaryQuaternionOp(expr_reference expr) : m_expr(expr) {}

    /** Copy constructor. */
    UnaryQuaternionOp(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for UnaryQuaternionOp<>. */
template<class ExprT, class OpT>
struct ExprTraits< UnaryQuaternionOp<ExprT,OpT> >
{
    typedef UnaryQuaternionOp<ExprT,OpT> expr_type;
    typedef ExprT arg_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef typename expr_type::assignable_tag assignable_tag;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};


/** A binary quaternion expression.
 *
 * The operator's operator() method must take exactly two arguments.
 */
template<class LeftT, class RightT, class OpT>
class BinaryQuaternionOp
{
  public:

    typedef BinaryQuaternionOp<LeftT,RightT,OpT> expr_type;

    /* Record ary-ness of the expression: */
    typedef binary_expression expr_ary;

    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;

    typedef typename OpT::value_type value_type;
    typedef quaternion_result_tag result_tag;

    /* Store the expression traits types for the two subexpressions: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Reference types for the two subexpressions: */
    typedef typename left_traits::const_reference left_reference;
    typedef typename right_traits::const_reference right_reference;

    /* Figure out the expression's resulting (quaternion) type: */
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename QuaternionPromote<left_result,right_result>::type
        result_type;
    typedef typename result_type::size_tag size_tag;

    /* For matching by assignability: */
    typedef cml::et::not_assignable_tag assignable_tag;

    /* Get the temporary type: */
    typedef typename result_type::temporary_type temporary_type;

    /* Define a size checker: */
    typedef GetCheckedSize<LeftT,RightT,size_tag> checked_size;


  public:

    /** Record result size as an enum. */
    enum { array_size = 4 };


  public:

    /** Return the size of the quaternion result.
     *
     * @throws std::invalid_argument if the expressions do not have the same
     * size.
     */
    size_t size() const {
        /* Note: This actually does a check only if
         * CML_CHECK_VECTOR_EXPR_SIZES is set:
         */
        CheckedSize(m_left,m_right,size_tag());

        /* The size is always 4: */
        return 4;
    }

    /** Return reference to left expression. */
    left_reference left_expression() const { return m_left; }

    /** Return reference to right expression. */
    right_reference right_expression() const { return m_right; }

    /** Compute value at index i of the result quaternion. */
    value_type operator[](size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the two subexpressions:
         */
        return OpT().apply(
                left_traits().get(m_left,i),
                right_traits().get(m_right,i));
    }

    /** Return the real part of the expression. */
    value_type real() const {
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        return (*this)[0];
#else
        return (*this)[3];
#endif
    }

    /** Return the vector part of the expression. */
    result_type imaginary() const {
        result_type v;
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        v[0] = (*this)[1]; v[1] = (*this)[2]; v[2] = (*this)[3];
#else
        v[0] = (*this)[0]; v[1] = (*this)[1]; v[2] = (*this)[2];
#endif
        return v;
    }


  public:

    /** Construct from the two subexpressions. */
    explicit BinaryQuaternionOp(left_reference left, right_reference right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    BinaryQuaternionOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* This ensures that a compile-time size check is executed: */
    typename checked_size::check_type _dummy;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits class for BinaryQuaternionOp<>. */
template<class LeftT, class RightT, class OpT>
struct ExprTraits< BinaryQuaternionOp<LeftT,RightT,OpT> >
{
    typedef BinaryQuaternionOp<LeftT,RightT,OpT> expr_type;
    typedef LeftT left_type;
    typedef RightT right_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef typename expr_type::assignable_tag assignable_tag;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& v, size_t i) const { return v[i]; }
    size_t size(const expr_type& e) const { return e.size(); }
};

/* Helper struct to verify that both arguments are quaternion expressions: */
template<typename LeftTraits, typename RightTraits>
struct QuaternionExpressions
{
    /* Require that both arguments are quaternion expressions: */
    typedef typename LeftTraits::result_tag left_result;
    typedef typename RightTraits::result_tag right_result;
    enum { is_true = (same_type<left_result,et::quaternion_result_tag>::is_true
            && same_type<right_result,et::quaternion_result_tag>::is_true) };
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
