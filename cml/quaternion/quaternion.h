/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef quaternion_h
#define quaternion_h

#include <cml/quaternion/quaternion_expr.h>

/* This is used below to create a more meaningful compile-time error when
 * the quaternion class is not created with a fixed-size 3-vector:
 */
struct quaternion_requires_fixed_size_3_vector_error;

namespace cml {

/** A configurable quaternion type.
 *
 * @note The vector currently cannot have an external<> storage type.
 *
 * @internal The quaternion class would have to be specialized to allow an
 * external<> storage type.
 */
template<typename VecT>
class quaternion
{
    /* The argument must be a fixed-size 3-vector without external<>
     * storage:
     */
    CML_STATIC_REQUIRE_M(
            ((VecT::array_size == 3)
            && same_type<typename VecT::size_tag, fixed_size_tag>::is_true),
            quaternion_requires_fixed_size_3_vector_error);

  public:

    /* Vector representing the imaginary part: */
    typedef VecT vector_type;

    /* Scalar type representing the scalar part: */
    typedef typename vector_type::value_type value_type;
    typedef typename vector_type::reference reference;
    typedef typename vector_type::const_reference const_reference;
    /* XXX Need to verify that this is a true scalar type. */

    /* The quaternion type: */
    typedef quaternion<vector_type> quaternion_type;

    /* For integration into the expression template code: */
    typedef quaternion_type expr_type;

    /* For integration into the expression template code: */
    typedef quaternion<typename vector_type::temporary_type> temporary_type;

    /* For integration into the expression templates code: */
    typedef quaternion_type& expr_reference;
    typedef const quaternion_type& expr_const_reference;

    /* For matching by storage type: */
    typedef typename vector_type::memory_tag memory_tag;

    /* For matching by size type: */
    typedef typename vector_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::quaternion_result_tag result_tag;

    /* For matching by assignability: */
    typedef cml::et::assignable_tag assignable_tag;


  public:

    /** Record result size as an enum. */
    enum { array_size = 4 };


  public:

    /** Default initializer. */
    quaternion() {}

    /** Copy construct from the same type of quaternion. */
    quaternion(const quaternion_type& q)
        : m_imag(q.imaginary()), m_real(q.real()) {}

    /** Construct from a quaternion having a different vector type. */
    template<typename V> quaternion(const quaternion<V>& q)
        : m_imag(q.imaginary()), m_real(q.real()) {}

    /** Copy construct from a QuaternionXpr. */
    template<typename XprT> quaternion(QUATXPR_ARG_TYPE e) {
        quaternion_type& q = *this;
        q[0] = e[0]; q[1] = e[1]; q[2] = e[2]; q[3] = e[3];
    }



    /** Initialize from 4 scalars.
     *
     * If CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST is defined, then a is
     * the real part, and (b,c,d) is the imaginary part.  Otherwise,
     * (a,b,c) is the imaginary part, and d is the real part.
     */
    quaternion(
            const value_type& a, const value_type& b,
            const value_type& c, const value_type& d)
    {
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        m_real = a; m_imag[0] = b; m_imag[1] = c; m_imag[2] = d;
#else
        m_imag[0] = a; m_imag[1] = b; m_imag[2] = c; m_real = d;
#endif
    }



    /** Initialize the imaginary part from an array of scalars.
     *
     * The imaginary part is given by an array of scalars.  The real part
     * is set to 0.
     *
     * @internal This requires that the vector type implements
     * CML_VEC_COPY_FROM_FIXED_ARRAY
     */
    quaternion(const value_type v[3]) : m_imag(v), m_real(0) {}

    /** Initialize both the real and imaginary parts.
     *
     * The imaginary part is given by an array of scalars.
     *
     * @internal This requires that the vector type implements
     * CML_VEC_COPY_FROM_FIXED_ARRAY
     */
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
    quaternion(const value_type v[3], const value_type& s)
        : m_imag(v), m_real(s) {}
#else
    quaternion(const value_type v[3], const value_type& s)
        : m_imag(v), m_real(s) {}
#endif



    /** Initialize the imaginary part.
     *
     * The real part is set to 0.
     */
    quaternion(const vector_type& v)
        : m_imag(v), m_real(0) {}

    /** Initialize both the real and imaginary parts.
     *
     * The imaginary part is initialized with a vector having the same type
     * as the quaternion's vector type.
     */
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
    quaternion(const value_type& s, const vector_type& v)
        : m_imag(v), m_real(s) {}
#else
    quaternion(const vector_type& v, const value_type& s)
        : m_imag(v), m_real(s) {}
#endif



    /** Initialize the imaginary part from a VectorXpr.
     *
     * The real part is set to 0.
     */
    template<typename XprT>
        quaternion(VECXPR_ARG_TYPE e) : m_imag(e), m_real(0) {}

    /** Initialize both the real and imaginary parts.
     *
     * The imaginary part is initialized with a VectorXpr.
     */
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
    template<typename XprT>
        quaternion(const value_type& s, VECXPR_ARG_TYPE e)
            : m_imag(e), m_real(s) {}
#else
    template<typename XprT>
        quaternion(VECXPR_ARG_TYPE e, const value_type& s)
            : m_imag(e), m_real(s) {}
#endif



    /** In-place op from a quaternion.
     *
     * This assumes that _op_ is defined for both the quaternion's vector
     * type and its scalar type.
     */
#define CML_QUAT_ASSIGN_FROM_QUAT(_op_)                           \
    template<typename V> const quaternion_type&                   \
    operator _op_ (const quaternion<V>& q) {                      \
        m_imag _op_ q.imaginary(); m_real _op_ q.real();          \
        return *this;                                             \
    }

    /** In-place op from a QuaternionXpr.
     *
     * This assumes that _op_ is defined for the quaternion's scalar type.
     */
#define CML_QUAT_ASSIGN_FROM_QUATXPR(_op_)                        \
    template<typename XprT> const quaternion_type&                \
    operator _op_ (QUATXPR_ARG_TYPE e) {                          \
        quaternion_type& q = *this;                               \
        q[0] _op_ e[0]; q[1] _op_ e[1];                           \
        q[2] _op_ e[2]; q[3] _op_ e[3];                           \
        return *this;                                             \
    }

    /** In-place op from a scalar type.
     *
     * This assumes that _op_ is defined for the quaternion's scalar type.
     */
#define CML_QUAT_ASSIGN_FROM_SCALAR(_op_,_op_name_)               \
    const quaternion_type& operator _op_ (const value_type& s) {  \
        typedef _op_name_ <value_type,value_type> OpT;            \
        quaternion_type& q = *this;                               \
        OpT().apply(q[0],s); OpT().apply(q[1],s);                 \
        OpT().apply(q[2],s); OpT().apply(q[3],s);                 \
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

  public:

    /** Return the imaginary vector. */
    const vector_type& imaginary() const { return m_imag; }

    /** Return the scalar part. */
    value_type real() const { return m_real; }

    /** Access the quaternion like a vector. */
    const_reference operator[](size_t i) const {
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        return (i==0)?m_real:m_imag[i-1];
#else
        return (i==3)?m_real:m_imag[i];
#endif
    }


  protected:

    /** Access the quaternion like a vector. */
    reference operator[](size_t i) {
#if defined(CML_ASSUME_QUATERNION_REAL_PART_IS_FIRST)
        return (i==0)?m_real:m_imag[i-1];
#else
        return (i==3)?m_real:m_imag[i];
#endif
    }


  protected:

    vector_type                 m_imag;
    value_type                  m_real;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
