/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_dynamic_selector_h
#define	cml_common_dynamic_selector_h

#include <memory>
#include <cml/common/storage_traits.h>

namespace cml {

/** Specializable type for 1D or 2D storage via a dynamically-allocated
 * array.
 *
 * @tparam Allocator Optional allocator type compatible with std::allocator.
 * The default is std::allocator<void>.
 *
 * @note A stateful allocator will increase the size of the dynamic<>
 * object beyond that required to store a pointer and array length.
 *
 * @note Dynamic 1D arrays must define a constant, array_size, set to -1.
 *
 * @note Dynamic 2D arrays must define two constants, array_rows and
 * array_cols, both set to -1.
 */
template<class Allocator = std::allocator<void>> struct dynamic;

/** storage_traits for dynamic<>. */
template<class Allocator>
struct storage_traits<dynamic<Allocator>>
{
  typedef dynamic<Allocator>				storage_type;
  typedef dynamic<Allocator>				solid_type;
  typedef dynamic_size_tag				size_tag;
};

/** traits_of for dynamic<>. */
template<class Allocator> struct traits_of<dynamic<Allocator>, void> {
  typedef storage_traits<dynamic<Allocator>>		type;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
