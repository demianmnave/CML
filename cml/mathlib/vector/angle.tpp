/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#ifndef __CML_MATHLIB_VECTOR_ANGLE_TPP
#  error "mathlib/vector/angle.tpp not included correctly"
#endif

#include <cml/vector/dot.h>
#include <cml/vector/perp_dot.h>
#include <cml/vector/cross.h>

namespace cml {

template<class Sub1, class Sub2>
inline auto
signed_angle_2D(const readable_vector<Sub1>& v1,
  const readable_vector<Sub2>& v2) -> value_type_trait_promote_t<Sub1, Sub2>
{
  using value_type = value_type_trait_promote_t<Sub1, Sub2>;
  using value_traits = scalar_traits<value_type>;
  return value_traits::atan2(perp_dot(v1, v2), dot(v1, v2));
}

template<class Sub1, class Sub2>
inline auto
unsigned_angle_2D(const readable_vector<Sub1>& v1,
  const readable_vector<Sub2>& v2) -> value_type_trait_promote_t<Sub1, Sub2>
{
  using value_type = value_type_trait_promote_t<Sub1, Sub2>;
  using value_traits = scalar_traits<value_type>;
  return value_traits::fabs(signed_angle_2D(v1, v2));
}

template<class Sub1, class Sub2, class Sub3>
inline auto
signed_angle(const readable_vector<Sub1>& v1, const readable_vector<Sub2>& v2,
  const readable_vector<Sub3>& reference)
  -> value_type_trait_promote_t<Sub1, Sub2, Sub3>
{
  using value_type = value_type_trait_promote_t<Sub1, Sub2, Sub3>;
  using value_traits = scalar_traits<value_type>;

  auto c = cross(v1, v2);
  auto angle = value_traits::atan2(c.length(), dot(v1, v2));
  return (dot(c, reference) < value_type(0)) ? -angle : angle;
}

template<class Sub1, class Sub2>
inline auto
unsigned_angle(const readable_vector<Sub1>& v1, const readable_vector<Sub2>& v2)
  -> value_type_trait_promote_t<Sub1, Sub2>
{
  using value_type = value_type_trait_promote_t<Sub1, Sub2>;
  using value_traits = scalar_traits<value_type>;
  return value_traits::atan2(cross(v1, v2).length(), dot(v1, v2));
}

}  // namespace cml