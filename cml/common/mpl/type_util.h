/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_type_util_h
#define	cml_common_mpl_type_util_h

#include <type_traits>
#include <cml/common/compiler.h>

namespace cml {

/** Remove const-volatile and reference types from @c T. */
template<class T> struct unqualified_type {
  typedef typename std::remove_cv<
    typename std::remove_reference<T>::type>::type type;
};

/** Remove const-volatile and reference types from @c T. */
template<class T> using unqualified_type_t
  = typename cml::unqualified_type<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
