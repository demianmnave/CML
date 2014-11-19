/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_promotion_h
#define	cml_common_scalar_promotion_h

#include <type_traits>

namespace cml {

/** Use C++ type deduction via std::common_type to determine the result of
 * combining N scalars.
 */
template<class... Scalars> using
  scalar_promote = std::common_type<Scalars...>;

/** Use C++ type deduction via std::common_type to determine the result of
 * combining N scalars.
 */
template<class... Scalars> using scalar_promote_t
  = typename scalar_promote<Scalars...>::type;

/** Alias to simplify scalar promotion from objects that implement a
 * value_type typedef.
 */
template<class... Subs> using value_type_promote
  = scalar_promote<typename Subs::value_type...>;

/** Convenience alias for value_type_promote<>::type. */
template<class... Subs> using value_type_promote_t
  = scalar_promote_t<typename Subs::value_type...>;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
