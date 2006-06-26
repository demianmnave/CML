/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef interpolation_h
#define interpolation_h

#include <cml/mathlib/matrix_rotation.h>

/* Interpolation functions.
 *
 * This code is currently a huge mess, but we'll get it cleaned up as we go.
 * The complexity comes from overloading slerp() to work with vectors (of any
 * size), quaternions, and matrices (of size 3x3 or 2x2). I originally had
 * these as separate named functions - quaternion_slerp() and so on. This
 * seemed cumbersome for the user and contrary to convention though, so I
 * decided to give this a try instead.
 *
 * This definitely needs another look though, if nothing else to make sure
 * that all necessary dynamic resizing is take care of. Also, I'm wondering
 * if more than one temporary is generated due to the layers involved; can
 * this be addressed through inlining?
 *
 * Actually, not that I think about it this was probably the wrong way to go
 * about it. Since there are only two arguments to slerp() that can be CML
 * expressions, and three types, that would only be 12 function signatures.
 * So instead, we could have 12 overloaded versions of slerp() that passed off
 * to named helper functions. Matrix slerp would still have to be dispatched
 * by size, but otherwise I think things would be simpler.
 *
 * This is already in place though, so I'm just going to finish this up as is.
 * We'll come back and clean it up later.
 *
 * There are also a couple of things I'm not quite sure of and need to look
 * into. One is whether, by any stretch, it's appropriate to use the term
 * 'nlerp' with matrices. This implies, among other things, that to
 * 'normalize' a rotation matrix is to orthogonalize it. I think I've seen
 * normalize used in this way, but I'm not sure whether or not it's
 * technically correct. It would be nice if it were, since then we would have
 * a nice uniform interface.
 *
 * The other thing I'm not sure about is what the best method of linearly
 * interpolating rotation matrices is. Currently I'm lerping them and then
 * orthogonalizing, but I've heard it suggested that it's better to lerp two
 * of the basis vectors rather than the whole matrix. I'm not sure why this
 * would be though; I'll have to think about it.
*/

namespace cml {

struct function_expects_args_of_same_type_error;

namespace detail {

//////////////////////////////////////////////////////////////////////////////
// Helper struct to promote a vector, quaternion or matrix
//////////////////////////////////////////////////////////////////////////////

template< class T1, class T2, class ResultT > struct TypePromote;

template< class T1, class T2 >
struct TypePromote< T1,T2,et::vector_result_tag > {
    typedef typename CrossPromote<T1,T2>::promoted_vector temporary_type;
};

template< class T1, class T2 >
struct TypePromote< T1,T2,et::matrix_result_tag > {
    typedef typename et::MatrixPromote<T1,T2>::temporary_type temporary_type;
};

template< class T1, class T2 >
struct TypePromote< T1,T2,et::quaternion_result_tag > {
    typedef typename et::QuaternionPromote<T1,T2>::temporary_type
        temporary_type;
};

//////////////////////////////////////////////////////////////////////////////
// Helper functions to resize a vector, quaternion or matrix
//////////////////////////////////////////////////////////////////////////////

template< typename E, class A, class VecT > void
InterpResize(vector<E,A>&, const VecT&, fixed_size_tag) {
}

template< typename E, class A, class VecT > void
InterpResize(vector<E,A>& v, const VecT& target, dynamic_size_tag) {
    v.resize(target.size());
}

template< typename E, class A, class B, class L, class MatT > void
InterpResize(matrix<E,A,B,L>&, const MatT&, fixed_size_tag) {
}

template< typename E, class A, class B, class L, class MatT > void
InterpResize(matrix<E,A,B,L>& m, const MatT& target, dynamic_size_tag) {
    m.resize(target.rows(),target.cols());
}

template< typename E, class A, class O, class C, class QuatT > void
InterpResize(quaternion<E,A,O,C>&, const QuatT&, fixed_size_tag) {
}

template< typename E, class A, class O, class C, class QuatT > void
InterpResize(quaternion<E,A,O,C>&, const QuatT&, dynamic_size_tag) {}

//////////////////////////////////////////////////////////////////////////////
// Spherical linear interpolation of two vectors of any size
//////////////////////////////////////////////////////////////////////////////

template< class VecT_1, class VecT_2, typename Real, class SizeT >
typename detail::TypePromote<
    VecT_1,VecT_2,typename et::ExprTraits<VecT_1>::result_tag
>::temporary_type
slerp(
    const VecT_1& v1,
    const VecT_2& v2,
    Real t,
    Real tolerance = epsilon<Real>::placeholder(),
    et::vector_result_tag,
    SizeT)
{
    typedef et::ExprTraits<VecT_1> type_traits;
    typedef typename type_traits::result_tag result_type;
    typedef typename
        detail::TypePromote<VecT_1,VecT_2,result_type>::temporary_type
            temporary_type;
    typedef typename temporary_type::value_type value_type;
    typedef et::ExprTraits<temporary_type> result_traits;
    typedef typename result_traits::size_tag size_tag;
            
    temporary_type result;
    detail::InterpResize(result, v1, size_tag());

    value_type omega = acos_safe(dot(v1,v2));
    value_type s = std::sin(omega);
    if (s < tolerance) {
        result = nlerp(v1,v2,t);
    } else {
        result = (value_type(std::sin((value_type(1)-t)*omega))*v1 +
            value_type(std::sin(t*omega))*v2) / s;
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////////
// Spherical linear interpolation of two quaternions
//////////////////////////////////////////////////////////////////////////////

template< class QuatT_1, class QuatT_2, typename Real, class SizeT >
typename detail::TypePromote<
    QuatT_1,QuatT_2,typename et::ExprTraits<QuatT_1>::result_tag
>::temporary_type
slerp(
    const QuatT_1& q1,
    const QuatT_2& q2,
    Real t,
    Real tolerance = epsilon<Real>::placeholder(),
    et::quaternion_result_tag,
    SizeT)
{
    typedef et::ExprTraits<QuatT_1> type_traits;
    typedef typename type_traits::result_tag result_type;
    typedef typename
        detail::TypePromote<QuatT_1,QuatT_2,result_type>::temporary_type
            temporary_type;
    typedef typename temporary_type::value_type value_type;

    temporary_type q3 = q2;
    value_type c = dot(q1,q3);
    if (c < value_type(0)) {
        q3 = -q3;
        c = -c;
    }
    
    value_type omega = acos_safe(c);
    value_type s = std::sin(omega);
    
    /* @todo: Here we are working around the fact that the utility function
     * lerp() is not expression-aware. By wrapping both input expressions in
     * temporaries of the same type, we can match lerp()'s template
     * signature.
     */

    return (s < tolerance) ?
        //normalize(lerp(q1,q3,t)) :
        normalize(lerp(temporary_type(q1),temporary_type(q3),value_type(t))) :
        (value_type(std::sin((value_type(1) - t) * omega)) * q1+
            value_type(std::sin(t * omega)) * q3) / s;
}

//////////////////////////////////////////////////////////////////////////////
// Helper struct for spherical linear interpolation of 3x3 and 2x2 matrices
//////////////////////////////////////////////////////////////////////////////

template< class MatT_1, class MatT_2, size_t N > struct slerp_f;

template< class MatT_1, class MatT_2 > struct slerp_f<MatT_1,MatT_2,3>
{
    template< typename Real >
    typename detail::TypePromote<
        MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
    >::temporary_type
    operator()(
        const MatT_1& m1,
        const MatT_2& m2,
        Real t,
        Real tolerance = epsilon<Real>::placeholder())
    {
        typedef typename detail::TypePromote<
            MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
        >::temporary_type temporary_type;

        temporary_type m;
        et::detail::Resize(m,3,3);
        m = matrix_rotation_difference(m1,m2);
        matrix_scale_rotation_angle(m,t,tolerance);
        m = detail::matrix_concat_rotations(m1,m);
        return m;
    }
};

template< class MatT_1, class MatT_2 > struct slerp_f<MatT_1,MatT_2,2>
{
    template< typename Real >
    typename detail::TypePromote<
        MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
    >::temporary_type
    operator()(
        const MatT_1& m1,
        const MatT_2& m2,
        Real t,
        Real tolerance = epsilon<Real>::placeholder())
    {
        typedef typename detail::TypePromote<
            MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
        >::temporary_type temporary_type;

        temporary_type m;
        et::detail::Resize(m,2,2);
        m = matrix_rotation_difference_2D(m1,m2);
        matrix_scale_rotation_angle_2D(m,t,tolerance);
        m = detail::matrix_concat_rotations_2D(m1,m);
        return m;
    }
};

//////////////////////////////////////////////////////////////////////////////
// Spherical linear interpolation of two matrices of size 3x3 or 2x2
//////////////////////////////////////////////////////////////////////////////

template< class MatT_1, class MatT_2, typename Real >
typename detail::TypePromote<
    MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
>::temporary_type
slerp(
    const MatT_1& m1,
    const MatT_2& m2,
    Real t,
    Real tolerance = epsilon<Real>::placeholder(),
    et::matrix_result_tag,
    fixed_size_tag)
{
    return slerp_f<MatT_1,MatT_2,MatT_1::array_rows>()(m1,m2,t,tolerance);
}

template< class MatT_1, class MatT_2, typename Real >
typename detail::TypePromote<
    MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
>::temporary_type
slerp(
    const MatT_1& m1,
    const MatT_2& m2,
    Real t,
    Real tolerance = epsilon<Real>::placeholder(),
    et::matrix_result_tag,
    dynamic_size_tag)
{
    typedef typename detail::TypePromote<
        MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
    >::temporary_type temporary_type;

    temporary_type m;
    et::detail::Resize(m,m1.rows(),m1.cols());
    
    switch (m1.rows()) {
        case 3:
            m = slerp_f<MatT_1,MatT_2,3>()(m1,m2,t,tolerance);
            break;
        case 2:
            m = slerp_f<MatT_1,MatT_2,2>()(m1,m2,t,tolerance);
            break;
        default:
            throw std::invalid_argument(
                "matrix slerp() expects sizes 3x3 or 2x2");
            break;
    }
    return m;
}

//////////////////////////////////////////////////////////////////////////////
// Normalized linear interpolation of two vectors of any size
//////////////////////////////////////////////////////////////////////////////

template< class VecT_1, class VecT_2, typename Real, class SizeT >
typename detail::TypePromote<
    VecT_1,VecT_2,typename et::ExprTraits<VecT_1>::result_tag
>::temporary_type
nlerp(
    const VecT_1& v1,
    const VecT_2& v2,
    Real t,
    et::vector_result_tag,
    SizeT)
{
    typedef et::ExprTraits<VecT_1> type_traits;
    typedef typename type_traits::result_tag result_type;
    typedef typename
        detail::TypePromote<VecT_1,VecT_2,result_type>::temporary_type
            temporary_type;
    typedef typename temporary_type::value_type value_type;
    typedef et::ExprTraits<temporary_type> result_traits;
    typedef typename result_traits::size_tag size_tag;
            
    temporary_type result;
    detail::InterpResize(result, v1, size_tag());
    
    /* @todo: Fix lerp() issue, after which we can write:
     *
     * result = normalize(lerp(v1,v2,t));
     */
    
    //temporary_type temp1, temp2;
    //detail::InterpResize(temp1, v1, size_tag());
    //detail::InterpResize(temp2, v1, size_tag());
    //temp1 = v1;
    //temp2 = v2;
    //result = normalize(lerp(temp1,temp2,t));
    //result = normalize(lerp(v1,v2,t));
    
    /* Aha! lerp() doesn't work for dynamic vectors yet. So:
     * @todo.
     *
     * Furthermore, normalize() doesn't work with dynamic vectors either.
     */
     
    //result = normalize((value_type(1)-t)*v1+t*v2);
    result = (value_type(1)-t)*v1+t*v2;
    result.normalize();
    return result;
}

//////////////////////////////////////////////////////////////////////////////
// Normalized linear interpolation of two quaternions
//////////////////////////////////////////////////////////////////////////////

template< class QuatT_1, class QuatT_2, typename Real, class SizeT >
typename detail::TypePromote<
    QuatT_1,QuatT_2,typename et::ExprTraits<QuatT_1>::result_tag
>::temporary_type
nlerp(
    const QuatT_1& q1,
    const QuatT_2& q2,
    Real t,
    et::quaternion_result_tag,
    SizeT)
{
    typedef et::ExprTraits<QuatT_1> type_traits;
    typedef typename type_traits::result_tag result_type;
    typedef typename
        detail::TypePromote<QuatT_1,QuatT_2,result_type>::temporary_type
            temporary_type;
    typedef typename temporary_type::value_type value_type;
    
    /* @todo: Here we are working around the fact that the utility function
     * lerp() is not expression-aware. By wrapping both input expressions in
     * temporaries of the same type, we can match lerp()'s template
     * signature.
     */

    //return normalize(lerp(q1, (dot(q1,q2) < value_type(0)) ? -q2 : q2, t));
    
    return normalize(
        lerp(
            temporary_type(q1),
            temporary_type(dot(q1,q2) < value_type(0) ? -q2 : q2),
            value_type(t)
        )
    );
}

//////////////////////////////////////////////////////////////////////////////
// Helper struct for normalized linear interpolation of 3x3 and 2x2 matrices
//////////////////////////////////////////////////////////////////////////////

template< class MatT_1, class MatT_2, size_t N > struct nlerp_f;

template< class MatT_1, class MatT_2 > struct nlerp_f<MatT_1,MatT_2,3>
{
    template< typename Real >
    typename detail::TypePromote<
        MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
    >::temporary_type
    operator()(
        const MatT_1& m1,
        const MatT_2& m2,
        Real t)
    {
        typedef typename detail::TypePromote<
            MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
        >::temporary_type temporary_type;
        typedef typename temporary_type::value_type value_type;
        
        /* @todo: Use lerp() when fixed*/

        temporary_type m;
        et::detail::Resize(m,3,3);
        m = (value_type(1)-t)*m1+t*m2;
        matrix_orthogonalize_3x3(m);
        return m;
    }
};

template< class MatT_1, class MatT_2 > struct nlerp_f<MatT_1,MatT_2,2>
{
    template< typename Real >
    typename detail::TypePromote<
        MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
    >::temporary_type
    operator()(
        const MatT_1& m1,
        const MatT_2& m2,
        Real t)
    {
        typedef typename detail::TypePromote<
            MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
        >::temporary_type temporary_type;
        typedef typename temporary_type::value_type value_type;
        
        /* @todo: Use lerp() when fixed*/

        temporary_type m;
        et::detail::Resize(m,2,2);
        m = (value_type(1)-t)*m1+t*m2;
        matrix_orthogonalize_2x2(m);
        return m;
    }
};

//////////////////////////////////////////////////////////////////////////////
// Spherical linear interpolation of two matrices of size 3x3 or 2x2
//////////////////////////////////////////////////////////////////////////////

template< class MatT_1, class MatT_2, typename Real >
typename detail::TypePromote<
    MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
>::temporary_type
nlerp(
    const MatT_1& m1,
    const MatT_2& m2,
    Real t,
    et::matrix_result_tag,
    fixed_size_tag)
{
    return nlerp_f<MatT_1,MatT_2,MatT_1::array_rows>()(m1,m2,t);
}

template< class MatT_1, class MatT_2, typename Real >
typename detail::TypePromote<
    MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
>::temporary_type
nlerp(
    const MatT_1& m1,
    const MatT_2& m2,
    Real t,
    et::matrix_result_tag,
    dynamic_size_tag)
{
    typedef typename detail::TypePromote<
        MatT_1,MatT_2,typename et::ExprTraits<MatT_1>::result_tag
    >::temporary_type temporary_type;

    temporary_type m;
    et::detail::Resize(m,m1.rows(),m1.cols());
    
    switch (m1.rows()) {
        case 3:
            m = nlerp_f<MatT_1,MatT_2,3>()(m1,m2,t);
            break;
        case 2:
            m = nlerp_f<MatT_1,MatT_2,2>()(m1,m2,t);
            break;
        default:
            throw std::invalid_argument(
                "matrix nlerp() expects sizes 3x3 or 2x2");
            break;
    }
    return m;
}

} // namespace detail

//////////////////////////////////////////////////////////////////////////////
// Spherical linear interpolation of two vectors, quaternion or matrices
//////////////////////////////////////////////////////////////////////////////

template< class T1, class T2, typename Real >
typename detail::TypePromote<
    T1,T2,typename et::ExprTraits<T1>::result_tag
>::temporary_type
slerp(
    const T1& t1,
    const T2& t2,
    Real t,
    Real tolerance = epsilon<Real>::placeholder())
{
    typedef et::ExprTraits<T1> traits_1;
    typedef et::ExprTraits<T2> traits_2;
    typedef typename traits_1::result_tag result_type_1;
    typedef typename traits_2::result_tag result_type_2;
    
    /* Check that results are of the same type */
    CML_STATIC_REQUIRE_M(
        (same_type<result_type_1, result_type_2>::is_true),
        function_expects_args_of_same_type_error);
    
    typedef typename detail::TypePromote<T1,T2,result_type_1>::temporary_type
        temporary_type;
    typedef et::ExprTraits<temporary_type> result_traits;
    typedef typename result_traits::size_tag size_tag;

    temporary_type result;
    detail::InterpResize(result, t1, size_tag());
    
    result = detail::slerp(t1,t2,t,tolerance,result_type_1(),size_tag());
    return result;
}

//////////////////////////////////////////////////////////////////////////////
// Normalized linear interpolation of two vectors, quaternion or matrices
//////////////////////////////////////////////////////////////////////////////

template< class T1, class T2, typename Real >
typename detail::TypePromote<
    T1,T2,typename et::ExprTraits<T1>::result_tag
>::temporary_type
nlerp(const T1& t1, const T2& t2, Real t)
{
    typedef et::ExprTraits<T1> traits_1;
    typedef et::ExprTraits<T2> traits_2;
    typedef typename traits_1::result_tag result_type_1;
    typedef typename traits_2::result_tag result_type_2;
    
    /* Check that results are of the same type */
    CML_STATIC_REQUIRE_M(
        (same_type<result_type_1, result_type_2>::is_true),
        function_expects_args_of_same_type_error);
    
    typedef typename detail::TypePromote<T1,T2,result_type_1>::temporary_type
        temporary_type;
    typedef et::ExprTraits<temporary_type> result_traits;
    typedef typename result_traits::size_tag size_tag;

    temporary_type result;
    detail::InterpResize(result, t1, size_tag());

    result = detail::nlerp(t1,t2,t,result_type_1(),size_tag());
    return result;
}

} // namespace cml

#endif