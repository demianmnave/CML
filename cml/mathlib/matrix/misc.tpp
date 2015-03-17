/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATHLIB_MATRIX_MISC_TPP
#error "mathlib/matrix/misc.tpp not included correctly"
#endif

#include <cml/vector/readable_vector.h>
#include <cml/matrix/writable_matrix.h>

namespace cml {

template<class Sub> inline auto
trace_2x2(const readable_matrix<Sub>& m) -> value_type_trait_of_t<Sub>
{
  cml::check_minimum_size(m, cml::int_c<2>(), cml::int_c<2>());
  return m(0,0) + m(1,1);
}

template<class Sub> inline auto
trace_3x3(const readable_matrix<Sub>& m) -> value_type_trait_of_t<Sub>
{
  cml::check_minimum_size(m, cml::int_c<3>(), cml::int_c<3>());
  return m(0,0) + m(1,1) + m(2,2);
}


template<class Sub1, class Sub2> inline void
matrix_skew_symmetric(
  writable_matrix<Sub1>& m, const readable_vector<Sub2>& v
  )
{
  cml::check_minimum_size(m, cml::int_c<3>(), cml::int_c<3>());
  cml::check_size(v, cml::int_c<3>());

  m.zero();

  m.set_basis_element(1,2,  v[0]);
  m.set_basis_element(2,1, -v[0]);
  m.set_basis_element(2,0,  v[1]);
  m.set_basis_element(0,2, -v[1]);
  m.set_basis_element(0,1,  v[2]);
  m.set_basis_element(1,0, -v[2]);
}

template<class Sub1, class Scalar> inline void
matrix_skew_symmetric_2D(
  writable_matrix<Sub1>& m, const Scalar& s
  )
{
  cml::check_minimum_size(m, cml::int_c<2>(), cml::int_c<2>());

  m.zero();
  m.set_basis_element(0,1,  s);
  m.set_basis_element(1,0, -s);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
