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

/** Use C++ type deduction via std::common_type. */
template<class Scalar1, class Scalar2> struct scalar_promote {
  typedef typename std::common_type<Scalar1,Scalar2>::type scalar_type;
};

/** Alias to simplify pairwise promotion of the value_type from two
 * objects that implement a value_type typedef.
 */
template<class Sub1, class Sub2> using value_type_promote
  = scalar_promote<typename Sub1::value_type, typename Sub2::value_type>;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
