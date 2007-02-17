/* -*- C++ -*- ------------------------------------------------------------
 
Copyright (c) 2007 Jesse Anders and Demian Nave http://cmldev.net/

The Configurable Math Library (CML) is distributed under the terms of the
Boost Software License, v1.0 (see cml/LICENSE for details).

 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Multiplication of two quaternions, p*q.
 *
 * This uses the expression tree, since the result is closed-form and can be
 * computed by index.
 */

#ifndef quaternion_mul_h
#define quaternion_mul_h

#include <cml/quaternion/quaternion_promotions.h>

namespace cml {
namespace et {

/** A binary expression tree node for multiplication. */
template<class LeftT, class RightT>
class QuaternionMulOp
{
  public:

    typedef QuaternionMulOp<LeftT,RightT> expr_type;

    /* Record ary-ness of the expression: */
    typedef binary_expression expr_ary;

    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;

    typedef typename ScalarPromote<
        typename LeftT::value_type,
        typename RightT::value_type
    >::type value_type;

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

    /* Get the vector type: */
    typedef typename result_type::vector_type vector_type;

    /* Get the imaginary part type: */
    typedef typename vector_type::subvector_type imaginary_type;

    /* Record the order type: */
    typedef typename result_type::order_type order_type;
    typedef typename result_type::cross_type cross_type;

    /* Define a size checker: */
    typedef GetCheckedSize<LeftT,RightT,size_tag> checked_size;


  public:

    /** Record result size as an enum. */
    enum { array_size = 4 };

    /** Localize the ordering as an enum. */
    enum {
        W = order_type::W,
        X = order_type::X,
        Y = order_type::Y,
        Z = order_type::Z
    };


  public:

    /** Return the real part of the expression. */
    value_type real() const {
        return (*this)[W];
    }

    /** Return the vector part of the expression. */
    imaginary_type imaginary() const {
        imaginary_type v;
        v[0] = (*this)[X]; v[1] = (*this)[Y]; v[2] = (*this)[Z];
        return v;
    }

    /** Return the Cayley norm of the expression. */
    value_type norm() const {
        return length_squared();
    }

    /** Return square of the quaternion length. */
    value_type length_squared() const {
        return dot(
                QuaternionXpr<expr_type>(*this),
                QuaternionXpr<expr_type>(*this));
    }

    /** Return the quaternion length. */
    value_type length() const {
        return std::sqrt(length_squared());
    }

    /** Return the result as a normalized quaternion. */
    temporary_type normalize() const {
        temporary_type q(QuaternionXpr<expr_type>(*this));
        return q.normalize();
    }

    /** Compute value of the product at index i.
     *
     * @bug This is dumb.  The result of the multiplication should be stored
     * in a temporary, and the coefficients of the temporary should be
     * returned.
     */
    value_type operator[](size_t i) const {

        /* Get scale for cross-product from the order (changes from v1^v2
         * to v2^v1):
         */
        enum { scale = cross_type::scale };

        /* Both expressions must be quaternions, so it's okay to use
         * operator[]:
         */
        switch(i) {

            /* s1*s2-dot(v1,v2): */
            case W: {
	      return m_left[W]*m_right[W] - m_left[X]*m_right[X]
		- m_left[Y]*m_right[Y] - m_left[Z]*m_right[Z];
	    } break;

            case X: {
	      /* (s1*v2 + s2*v1 + v1^v2) i: */
	      return m_left[W]*m_right[X] + m_right[W]*m_left[X]
		+ scale*(m_left[Y]*m_right[Z] - m_left[Z]*m_right[Y]);
	    } break;

            case Y: {
	      /* (s1*v2 + s2*v1 + v1^v2) j: */
	      return m_left[W]*m_right[Y] + m_right[W]*m_left[Y]
		+ scale*(m_left[Z]*m_right[X] - m_left[X]*m_right[Z]);
	    } break;

            case Z: {
	      /* (s1*v2 + s2*v1 + v1^v2) k: */
	      return m_left[W]*m_right[Z] + m_right[W]*m_left[Z]
		+ scale*(m_left[X]*m_right[Y] - m_left[Y]*m_right[X]);
	    } break;
        }
        throw std::runtime_error(
                "invalid index in QuaternionMulOp::operator[]");
        return 0.;
    }


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


  public:

    /** Construct from the two subexpressions. */
    explicit QuaternionMulOp(left_reference left, right_reference right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    QuaternionMulOp(const expr_type& e)
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
template<class LeftT, class RightT>
struct ExprTraits< QuaternionMulOp<LeftT,RightT> >
{
    typedef QuaternionMulOp<LeftT,RightT> expr_type;
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

} // namespace et

/** Declare mul taking two quaternion operands. */
template<typename E1, class AT1, typename E2, class AT2, class OT, class CT>
inline typename et::QuaternionPromote<
    quaternion<E1,AT1,OT,CT>, quaternion<E2,AT2,OT,CT>
>::temporary_type
operator* (
        const quaternion<E1,AT1,OT,CT>& left,
        const quaternion<E2,AT2,OT,CT>& right)
{
    typedef et::QuaternionMulOp<
            quaternion<E1,AT1,OT,CT>,
            quaternion<E2,AT2,OT,CT>
        > ExprT;
    return et::QuaternionXpr<ExprT>(ExprT(left,right));
}


/** Declare mul taking a quaternion and a et::QuaternionXpr. */
template<typename E, class AT, class OT, class CT, class XprT>
inline typename et::QuaternionPromote<
    quaternion<E,AT,OT,CT>, typename XprT::result_type
>::temporary_type
operator*(
        const quaternion<E,AT,OT,CT>& left,
        QUATXPR_ARG_TYPE right)
{
    typedef et::QuaternionMulOp<quaternion<E,AT,OT,CT>, XprT> ExprT;
    return et::QuaternionXpr<ExprT>(ExprT(left,right.expression()));
}


/** Declare mul taking an et::QuaternionXpr and a quaternion. */
template<class XprT, typename E, class AT, class OT, class CT>
inline typename et::QuaternionPromote<
    typename XprT::result_type, quaternion<E,AT,OT,CT>
>::temporary_type
operator* (
        QUATXPR_ARG_TYPE left,
        const quaternion<E,AT,OT,CT>& right)
{
    typedef et::QuaternionMulOp< XprT, quaternion<E,AT,OT,CT> > ExprT;
    return et::QuaternionXpr<ExprT>(ExprT(left.expression(),right));
}


/** Declare mul taking two et::QuaternionXpr operands. */
template<class XprT1, class XprT2>
inline typename et::QuaternionPromote<
    typename XprT1::result_type, typename XprT2::result_type
>::temporary_type
operator* (
        QUATXPR_ARG_TYPE_N(1) left,
        QUATXPR_ARG_TYPE_N(2) right)
{
    typedef et::QuaternionMulOp<XprT1, XprT2> ExprT;
    return et::QuaternionXpr<ExprT>(
            ExprT(left.expression(),right.expression()));
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
