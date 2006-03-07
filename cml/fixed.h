/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef fixed_h
#define fixed_h

#include <cml/core/cml_assert.h>

namespace cml {

/** Select a statically-allocated array.
 *
 * cml::fixed<> is a wrapper for the implementation class, which is
 * accessed via a "rebind"-like mechanism to select the actual array type
 * to use.  This allows the cml::vector<> and cml::matrix<> classes to have
 * template signatures independent of the array type being used.
 *
 * This method is used by cml::dynamic<> also, making compile-time
 * selection of fixed or dynamic storage relatively straightforward.
 *
 * @sa cml::vector
 * @sa cml::matrix
 */
template<int Dim1 = -1, int Dim2 = -1> struct fixed;

} // namespace cml

/* Include these here to pick up definition of fixed<>: */
#include <cml/core/fixed_1D.h>
#include <cml/core/fixed_2D.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
