/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATHLIB_VECTOR_TRANSFORM_TPP
#error "mathlib/vector/transform.tpp not included correctly"
#endif

#include <cml/common/mpl/are_convertible.h>
#include <cml/vector/size_checking.h>
#include <cml/mathlib/matrix/size_checking.h>

namespace cml {

/* 3D transformations: */

template<class Sub1, class Sub2> inline auto
transform_vector(
  const readable_matrix<Sub1>& m, const readable_vector<Sub2>& v
  ) -> temporary_of_t<Sub2>
{
  typedef temporary_of_t<Sub2> result_type;
  return result_type(
    m.basis_element(0,0)*v[0] +
    m.basis_element(1,0)*v[1] +
    m.basis_element(2,0)*v[2],

    m.basis_element(0,1)*v[0] +
    m.basis_element(1,1)*v[1] +
    m.basis_element(2,1)*v[2],

    m.basis_element(0,2)*v[0] +
    m.basis_element(1,2)*v[1] +
    m.basis_element(2,2)*v[2]
    );
}

} // namespace cml

#if 0
// XXX INCOMPLETE XXX

/* Functions for transforming a vector, representing a geometric point or
 * or vector, by an affine transfom.
 *
 * Note: This functionality may be provisional, depending on what architecture
 * we settle on for the higher-level math functions. If we do keep these
 * functions, then this code may ending up being a placeholder for expression
 * template code.
 */

namespace cml {

/** A fixed-size temporary 4D vector */
#define TEMP_VEC4 vector<          \
    typename et::ScalarPromote<    \
        typename MatT::value_type, \
        typename VecT::value_type  \
    >::type,                       \
    fixed<4>                       \
>

/** A fixed-size temporary 3D vector */
#define TEMP_VEC3 vector<          \
    typename et::ScalarPromote<    \
        typename MatT::value_type, \
        typename VecT::value_type  \
    >::type,                       \
    fixed<3>                       \
>

/** A fixed-size temporary 2D vector */
#define TEMP_VEC2 vector<          \
    typename et::ScalarPromote<    \
        typename MatT::value_type, \
        typename VecT::value_type  \
    >::type,                       \
    fixed<2>                       \
>

namespace detail {

template < class MatT, class VecT > TEMP_VEC4
transform_vector_4D(const MatT& m, const VecT& v, row_basis) {
    return v*m;
}

template < class MatT, class VecT > TEMP_VEC4
transform_vector_4D(const MatT& m, const VecT& v, col_basis) {
    return m*v;
}

} // namespace detail

/** Apply a 4x4 homogeneous transform matrix to a 4D vector */
template < class MatT, class VecT > TEMP_VEC4
transform_vector_4D(const MatT& m, const VecT& v) {
    return detail::transform_vector_4D(m,v,typename MatT::basis_orient());
}

/** Apply a homogeneous (e.g. perspective) transform to a 3D point. */
template < class MatT, class VecT > TEMP_VEC3
transform_point_4D(const MatT& m, const VecT& v)
{
    typedef TEMP_VEC3 vector_type;
    typedef typename TEMP_VEC3::coordinate_type coordinate_type;

    /* Checking */
    detail::CheckMatHomogeneous3D(m);
    detail::CheckVec3(v);

    /* Compute the 4D point: */
    TEMP_VEC4 v4 = transform_vector_4D(
      m, TEMP_VEC4(v[0], v[1], v[2], coordinate_type(1)));

    /* Return the projected point: */
    coordinate_type w = v4[3];
    return vector_type(v4[0]/w, v4[1]/w, v4[2]/w);
}

/** Apply a 3D affine transform to a 3D point */
template < class MatT, class VecT > TEMP_VEC3
transform_point(const MatT& m, const VecT& v)
{
    typedef TEMP_VEC3 vector_type;

    /* Checking */
    detail::CheckMatAffine3D(m);
    detail::CheckVec3(v);

    return vector_type(
        m.basis_element(0,0)*v[0]+m.basis_element(1,0)*v[1]+
            m.basis_element(2,0)*v[2]+m.basis_element(3,0),
        m.basis_element(0,1)*v[0]+m.basis_element(1,1)*v[1]+
            m.basis_element(2,1)*v[2]+m.basis_element(3,1),
        m.basis_element(0,2)*v[0]+m.basis_element(1,2)*v[1]+
            m.basis_element(2,2)*v[2]+m.basis_element(3,2)
    );
}

/** Apply a 3D affine transform to a 3D vector */
template < class MatT, class VecT > TEMP_VEC3
transform_vector(const MatT& m, const VecT& v)
{
    typedef TEMP_VEC3 vector_type;

    /* Checking */
    detail::CheckMatLinear3D(m);
    detail::CheckVec3(v);

    return vector_type(
        m.basis_element(0,0)*v[0]+m.basis_element(1,0)*v[1]+
            m.basis_element(2,0)*v[2],
        m.basis_element(0,1)*v[0]+m.basis_element(1,1)*v[1]+
            m.basis_element(2,1)*v[2],
        m.basis_element(0,2)*v[0]+m.basis_element(1,2)*v[1]+
            m.basis_element(2,2)*v[2]
    );
}

/** Apply a 2D affine transform to a 2D point */
template < class MatT, class VecT > TEMP_VEC2
transform_point_2D(const MatT& m, const VecT& v)
{
    typedef TEMP_VEC2 vector_type;

    /* Checking */
    detail::CheckMatAffine2D(m);
    detail::CheckVec2(v);

    return vector_type(
        m.basis_element(0,0)*v[0]+m.basis_element(1,0)*v[1]+
            m.basis_element(2,0),
        m.basis_element(0,1)*v[0]+m.basis_element(1,1)*v[1]+
            m.basis_element(2,1)
    );
}

/** Apply a 2D affine transform to a 2D vector */
template < class MatT, class VecT > TEMP_VEC2
transform_vector_2D(const MatT& m, const VecT& v)
{
    typedef TEMP_VEC2 vector_type;

    /* Checking */
    detail::CheckMatLinear2D(m);
    detail::CheckVec2(v);

    return vector_type(
        m.basis_element(0,0)*v[0] + m.basis_element(1,0)*v[1],
        m.basis_element(0,1)*v[0] + m.basis_element(1,1)*v[1]
    );
}

#undef TEMP_VEC4
#undef TEMP_VEC3
#undef TEMP_VEC2

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
