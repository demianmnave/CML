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
#ifdef _MSC_VER
// At least VC++ 2013 can't grok the better solution below, so fake it for
// now:
template<class S0, class S1, class S2 = void, class = void>
  struct scalar_promote;

template<class S0, class S1> struct scalar_promote<S0,S1,void> {
  typedef typename std::common_type<S0,S1>::type type;
};

template<class S0, class S1, class S2> struct scalar_promote<S0,S1,S2,void> {
  typedef typename std::common_type<S0,S1,S2>::type type;
};
#else
// The real C++11 solution for N scalar arguments:
template<class... Scalars> struct scalar_promote {
  typedef typename std::common_type<Scalars...>::type type;
};
#endif

/** Use C++ type deduction via std::common_type to determine the result of
 * combining N scalars.
 */
template<class... Scalars> using scalar_promote_t
  = typename scalar_promote<Scalars...>::type;

/** Alias to simplify pairwise promotion of the value_type from two
 * objects that implement a value_type typedef.
 */
template<class Sub1, class Sub2> using value_type_promote
  = scalar_promote<typename Sub1::value_type, typename Sub2::value_type>;

/** Alias to simplify pairwise promotion of the value_type from two
 * objects that implement a value_type typedef.
 */
template<class Sub1, class Sub2> using value_type_promote_t
  = scalar_promote_t<typename Sub1::value_type, typename Sub2::value_type>;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
