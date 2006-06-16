/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  @todo Return a VectorXpr adaptor from the imaginary() method of
 *  quaternion and the expression node types.
 *
 *  @todo swap multiplication order based upon template param
 *
 *  @todo change element order based upon template param
 */

#ifndef quaternion_h
#define quaternion_h

#include <cml/quaternion/quaternion_expr.h>
#include <cml/quaternion/quaternion_dot.h>

/* This is used below to create a more meaningful compile-time error when
 * the quaternion class is not created with a fixed-size 4-vector:
 */
struct quaternion_requires_fixed_size_array_type_error;

namespace cml {

/** Helper to specify v1^v2 multiplication order. */
struct positive_cross {
    enum { scale = 1 };
};

/** Helper to specify v2^v1 multiplication order. */
struct negative_cross {
    enum { scale = -1 };
};

/** Helper to specify scalar-first quaternion ordering. */
struct scalar_first {
    enum { W, X, Y, Z };
};

/** Helper to specify vector-first quaternion ordering. */
struct vector_first {
    enum { X, Y, Z, W };
};

/** A configurable quaternion type.
 *
 * @note Quaternions with two different orders cannot be used in the same
 * expression.
 *
 * @note The vector currently cannot have an external<> storage type.
 *
 * @internal The quaternion class would have to be specialized to allow an
 * external<> storage type.
 */
template<
    typename Element,
    class ArrayType = fixed<>,
    class Order = scalar_first,
    class Cross = positive_cross
>
class quaternion
{
    /* The ArrayType must be fixed<> or external<>: */
    CML_STATIC_REQUIRE_M(
            (same_type< ArrayType, fixed<> >::is_true
             || same_type< ArrayType, external<> >::is_true),
            quaternion_requires_fixed_size_array_type_error);

  public:

    /* Shorthand for the array type generator: */
    typedef ArrayType storage_type;
    typedef typename ArrayType::template rebind<4>::other generator_type;

    /* Vector representing the quaternion.  Use the rebinding template to
     * set the vector size:
     */
    typedef vector<Element, generator_type> vector_type;

    /* Vector temporary type: */
    typedef typename vector_type::temporary_type vector_temporary;

    /* Quaternion order: */
    typedef Order order_type;

    /* Quaternion multiplication order: */
    typedef Cross cross_type;

    /* Scalar type representing the scalar part: */
    typedef typename vector_type::value_type value_type;
    typedef typename vector_type::reference reference;
    typedef typename vector_type::const_reference const_reference;
    /* XXX Need to verify that this is a true scalar type. */

    /* The quaternion type: */
    typedef quaternion<Element,storage_type,order_type,cross_type>
        quaternion_type;

    /* For integration into the expression template code: */
    typedef quaternion_type expr_type;

    /* For integration into the expression template code: */
    typedef quaternion<
        Element, typename vector_temporary::storage_type,
        order_type, cross_type> temporary_type;

    /* For integration into the expression templates code: */
    typedef quaternion_type& expr_reference;
    typedef const quaternion_type& expr_const_reference;

    /* For matching by storage type: */
    typedef typename vector_type::memory_tag memory_tag;

    /* For matching by size type: */
    typedef typename vector_type::size_tag size_tag;

    /* Get the imaginary part type: */
    typedef typename vector_temporary::subvector_type imaginary_type;

    /* For matching by result-type: */
    typedef cml::et::quaternion_result_tag result_tag;

    /* For matching by assignability: */
    typedef cml::et::assignable_tag assignable_tag;


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

    /** Return the scalar part. */
    value_type real() const { return m_q[W]; }

    /** Return the imaginary vector. */
    imaginary_type imaginary() const {
        imaginary_type v;
        v[0] = m_q[X]; v[1] = m_q[Y]; v[2] = m_q[Z];
        return v;
    }

    /** Return the Cayley norm of the quaternion. */
    value_type norm() const {
        return length_squared();
    }

    /** Return square of the quaternion length. */
    value_type length_squared() const {
        return dot(*this,*this);
    }

    /** Return the quaternion length. */
    value_type length() const {
        return std::sqrt(length_squared());
    }

    /** Normalize this vector (divide by its length).
     *
     * @todo Make this return a QuaternionXpr.
     */
    quaternion_type& normalize() {
        return (*this /= length());
    }

    /** Set this quaternion to the multiplicative identity. */
    quaternion_type& identity() {
        (*this)[W] = value_type(1);
        (*this)[X] = value_type(0);
        (*this)[Y] = value_type(0);
        (*this)[Z] = value_type(0);
        return *this;
    }


    /** Const access to the quaternion as a vector. */
    const_reference operator[](size_t i) const { return m_q[i]; }

    /** Mutable access to the quaternion as a vector. */
    reference operator[](size_t i) { return m_q[i]; }

    /** Pairwise minimum of this quaternion with another. */
    template<typename E, class AT, class OT, class CT>
    void minimize(const quaternion<E,AT,OT,CT>& q) {
      /* XXX This should probably use ScalarPromote: */
      for (size_t i = 0; i < 4; ++i) {
        (*this)[i] = std::min((*this)[i],q[i]);
      }
    }

    /** Pairwise maximum of this quaternion with another. */
    template<typename E, class AT, class OT, class CT>
    void maximize(const quaternion<E,AT,OT,CT>& q) {
      /* XXX This should probably use ScalarPromote: */
      for (size_t i = 0; i < 4; ++i) {
        (*this)[i] = std::max((*this)[i],q[i]);
      }
    }

    /** Fill quaternion with random elements.
     *
     * @warning This does not generate uniformly random rotations.
     */
    void random(value_type min, value_type max) {
        for (size_t i = 0; i < 4; ++i) {
            (*this)[i] = random_real(min,max);
        }
    }


  public:

    /** Default initializer.
     *
     * The default constructor cannot be used with an external<> array
     * type.
     */
    quaternion() {}

    /** Initializer for an external<> vector type. */
    quaternion(Element* const array) : m_q(array) {}

    /** Copy construct from the same type of quaternion. */
    quaternion(const quaternion_type& q) : m_q(q.m_q) {}

    /** Construct from a quaternion having a different array type. */
    template<typename E, class AT> quaternion(
            const quaternion<E,AT,order_type,cross_type>& q) : m_q(q.m_q) {}

    /** Copy construct from a QuaternionXpr. */
    template<typename XprT> quaternion(QUATXPR_ARG_TYPE e) {
        typedef typename XprT::order_type arg_order;
        m_q[W] = e[arg_order::W];
        m_q[X] = e[arg_order::X];
        m_q[Y] = e[arg_order::Y];
        m_q[Z] = e[arg_order::Z];
    }



    /** Initialize from a 4-vector.
     *
     * If Order is scalar_first, then v[0] is the real part.  Otherwise,
     * v[3] is the real part.
     */
    quaternion(const vector_type& v) : m_q(v) {}

    /** Initialize from an array of scalars.
     *
     * If Order is scalar_first, then v[0] is the real part.  Otherwise,
     * v[3] is the real part.
     *
     * @note The target vector must have CML_VEC_COPY_FROM_ARRAY
     * implemented.
     */
    quaternion(const value_type v[4]) : m_q(v) {}

#if 0
    /* XXX This needs a function specialized on the order type to properly
     * interpret a as W or X and d as Z or W.
     */

    /** Initialize from 4 scalars.
     *
     * If then a is the real part, and (b,c,d) is the imaginary part.
     * Otherwise, (a,b,c) is the imaginary part, and d is the real part.
     */
    quaternion(
            const value_type& a, const value_type& b,
            const value_type& c, const value_type& d)
    {
        m_q[0] = a; m_q[1] = b; m_q[2] = c; m_q[3] = d;
    }
#endif



    /** Initialize both the real and imaginary parts.
     *
     * The imaginary part is given by an array of scalars.
     */
    quaternion(const value_type& s, const value_type v[3]) {
        m_q[W] = s; m_q[X] = v[0]; m_q[Y] = v[1]; m_q[Z] = v[2];
    }



    /** Initialize from a VectorXpr. */
    template<typename XprT>
        quaternion(VECXPR_ARG_TYPE e) : m_q(e) {}

    /** Initialize both the real and imaginary parts.
     *
     * The imaginary part is initialized with a VectorXpr.
     */
    template<typename XprT>
        quaternion(const value_type& s, VECXPR_ARG_TYPE e) {
            m_q[W] = s; m_q[X] = e[0]; m_q[Y] = e[1]; m_q[Z] = e[2];
        }



    /** In-place op from a quaternion.
     *
     * This assumes that _op_ is defined for both the quaternion's vector
     * type and its scalar type.
     */
#define CML_QUAT_ASSIGN_FROM_QUAT(_op_)                                 \
    template<typename E, class AT> const quaternion_type&               \
    operator _op_ (const quaternion<E,AT,order_type,cross_type>& q) {   \
        m_q[W] _op_ q[W];                                               \
        m_q[X] _op_ q[X];                                               \
        m_q[Y] _op_ q[Y];                                               \
        m_q[Z] _op_ q[Z];                                               \
        return *this;                                                   \
    }

    /** In-place op from a QuaternionXpr.
     *
     * This assumes that _op_ is defined for the quaternion's scalar type.
     */
#define CML_QUAT_ASSIGN_FROM_QUATXPR(_op_)                              \
    template<typename XprT> quaternion_type&                            \
    operator _op_ (QUATXPR_ARG_TYPE e) {                                \
        typedef typename XprT::order_type arg_order;                    \
        m_q[W] _op_ e[arg_order::W];                                    \
        m_q[X] _op_ e[arg_order::X];                                    \
        m_q[Y] _op_ e[arg_order::Y];                                    \
        m_q[Z] _op_ e[arg_order::Z];                                    \
        return *this;                                                   \
    }

    /** In-place op from a scalar type.
     *
     * This assumes that _op_ is defined for the quaternion's scalar type.
     */
#define CML_QUAT_ASSIGN_FROM_SCALAR(_op_,_op_name_)               \
    quaternion_type& operator _op_ (const value_type& s) {        \
        typedef _op_name_ <value_type,value_type> OpT;            \
        OpT().apply(m_q[W],s);                                    \
        OpT().apply(m_q[X],s);                                    \
        OpT().apply(m_q[Y],s);                                    \
        OpT().apply(m_q[Z],s);                                    \
        return *this;                                             \
    }

    CML_QUAT_ASSIGN_FROM_QUAT(=)
    CML_QUAT_ASSIGN_FROM_QUAT(+=)
    CML_QUAT_ASSIGN_FROM_QUAT(-=)

    CML_QUAT_ASSIGN_FROM_QUATXPR(=)
    CML_QUAT_ASSIGN_FROM_QUATXPR(+=)
    CML_QUAT_ASSIGN_FROM_QUATXPR(-=)

    CML_QUAT_ASSIGN_FROM_SCALAR(*=, cml::et::OpMulAssign)
    CML_QUAT_ASSIGN_FROM_SCALAR(/=, cml::et::OpDivAssign)

#undef CML_QUAT_ASSIGN_FROM_QUAT
#undef CML_QUAT_ASSIGN_FROM_QUATXPR


  protected:

    vector_type                 m_q;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
