/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATHLIB_MATRIX_TRANSLATION_TPP
#error "mathlib/matrix/translation.tpp not included correctly"
#endif

#include <cml/common/mpl/are_convertible.h>
#include <cml/vector/size_checking.h>
#include <cml/mathlib/matrix/size_checking.h>

namespace cml {
namespace detail {

/* Base case, set a single basis element (I,J): */
template<int I, int J, class Sub, class E> inline void
matrix_set_basis(writable_matrix<Sub>& m, const E& e)
{
  m.set_basis_element(I, J, e);
}

/* Recursive case: set basis element (I,J) to e, then recursively set
 * (I,J+1):
 */
template<int I, int J, class Sub, class E, class... Es> inline void
matrix_set_basis(writable_matrix<Sub>& m, const E& e, const Es&... es)
{
  m.set_basis_element(I, J, e);
  matrix_set_basis<I,J+1>(m, es...);
}

/* Entry case: set basis vector I from the items in Es: */
template<int I, class Sub, class... Es> inline void
matrix_set_basis(writable_matrix<Sub>& m, const Es&... es)
{
  static_assert(
    cml::are_convertible<value_type_trait_of_t<Sub>, Es...>::value,
    "incompatible scalar types");

  /* Recursively set basis vector I, starting at element 0: */
  matrix_set_basis<I,0>(m, es...);
}

} // namespace detail


template<class Sub, class E0, class E1> inline void
matrix_set_translation_2D(
  writable_matrix<Sub>& m, const E0& e0, const E1& e1
  )
{
  cml::check_affine_2D(m);
  detail::matrix_set_basis<2>(m, e0, e1);
}

template<class Sub1, class Sub2> inline void
matrix_set_translation_2D(
  writable_matrix<Sub1>& m, const readable_vector<Sub2>& v
  )
{
  cml::check_size(v, cml::int_c<2>());
  cml::check_affine_2D(m);
  detail::matrix_set_basis<2>(m, v[0], v[1]);
}


template<class Sub, class E0, class E1> inline void
matrix_get_translation_2D(
  writable_matrix<Sub>& m, E0& e0, E1& e1
  )
{
  static_assert(
    cml::are_convertible<value_type_trait_of_t<Sub>, E0, E1>::value,
    "incompatible scalar types");

  cml::check_affine_2D(m);
  e0 = m.basis_element(2,0);
  e1 = m.basis_element(2,1);
}

template<class Sub> auto
matrix_get_translation_2D(const readable_matrix<Sub>& m)
-> n_basis_vector_of_t<Sub,2>
{
  cml::check_affine_2D(m);
  return { m.basis_element(2,0), m.basis_element(2,1) };
}


template<class Sub, class E0, class E1, class E2> inline void
matrix_set_translation(
  writable_matrix<Sub>& m, const E0& e0, const E1& e1, const E2& e2
  )
{
  cml::check_affine_3D(m);
  detail::matrix_set_basis<3>(m, e0, e1, e2);
}

template<class Sub1, class Sub2> inline void
matrix_set_translation(
  writable_matrix<Sub1>& m, const readable_vector<Sub2>& v
  )
{
  cml::check_size(v, cml::int_c<3>());
  cml::check_affine_3D(m);
  detail::matrix_set_basis<3>(m, v[0], v[1], v[2]);
}


template<class Sub, class E0, class E1, class E2> inline void
matrix_get_translation(
  writable_matrix<Sub>& m, E0& e0, E1& e1, E2& e2
  )
{
  static_assert(
    cml::are_convertible<value_type_trait_of_t<Sub>, E0, E1, E2>::value,
    "incompatible scalar types");

  cml::check_affine_3D(m);
  e0 = m.basis_element(3,0);
  e1 = m.basis_element(3,1);
  e2 = m.basis_element(3,2);
}

template<class Sub> auto
matrix_get_translation(const readable_matrix<Sub>& m)
-> n_basis_vector_of_t<Sub,3>
{
  cml::check_affine_3D(m);
  return { m.basis_element(3,0), m.basis_element(3,1), m.basis_element(3,2) };
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
