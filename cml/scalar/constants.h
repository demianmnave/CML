/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cmath>

#if !defined(M_PI)
#  define M_PI 3.14159265358979323846
#endif

#if !defined(M_SQRT2)
#  define M_SQRT2 1.41421356237309504880
#endif

#if !defined(M_E)
#  define M_E 2.71828182845904523536
#endif

namespace cml {
/** Templated constants struct.
 *
 * Either float or double can be used.
 */
template<typename Float> struct constants
{
  static constexpr Float pi() { return Float(M_PI); }

  static constexpr Float two_pi() { return Float(2. * M_PI); }

  static constexpr Float inv_pi() { return Float(1. / M_PI); }

  static constexpr Float inv_two_pi() { return Float(1. / (2. * M_PI)); }

  static constexpr Float pi_over_2() { return Float(M_PI / 2.); }

  static constexpr Float pi_over_4() { return Float(M_PI / 4.); }

  static constexpr Float e() { return Float(M_E); }

  static constexpr Float deg_per_rad() { return Float(180. / M_PI); }

  static constexpr Float rad_per_deg() { return Float(M_PI / 180.); }

  static constexpr Float sqrt_2() { return Float(M_SQRT2); }

  static constexpr Float sqrt_3() { return Float(1.73205080756887729353); }

  static constexpr Float sqrt_5() { return Float(2.23606797749978969641); }

  static constexpr Float sqrt_6() { return Float(2.44948974278317809820); }
};
} // namespace cml
