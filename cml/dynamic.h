/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_h
#define dynamic_h

#include <memory>               // for std::allocator
#include <cml/core/common.h>

namespace cml {

template< typename Alloc = std::allocator<void> > struct dynamic;

} // namespace cml

#include <cml/core/dynamic_1D.h>
#include <cml/core/dynamic_2D.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
