/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_dynamic_selector_h
#define	cml_common_dynamic_selector_h

#include <memory>
#include <cml/common/size_tags.h>

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

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
