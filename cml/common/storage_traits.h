/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_storage_traits_h
#define	cml_common_storage_traits_h

#include <cml/common/size_tags.h>

namespace cml {

template<class Storage> struct storage_traits;

/** Tag for an arbitrary/unspecified storage type. */
struct any_storage {};

/** Traits for any_storage. */
template<> struct storage_traits<any_storage> {
  typedef any_storage					storage_type;
  typedef void						solid_type;
  typedef any_size_tag					size_tag;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
