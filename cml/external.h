/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef external_h
#define external_h

#include <cml/core/cml_assert.h>

namespace cml {

/** Wrapper for externally-created arrays.
 *
 * cml::external<> is a wrapper for the implementation classes, which are
 * accessed via a "rebind"-like mechanism to select the actual array type
 * to use.  This allows the cml::vector<> and cml::matrix<> classes to have
 * template signatures independent of the array type being used.
 *
 * This method is used by cml::fixed<> and cml::dynamic<> also, making
 * compile-time selection of array sizes and storage relatively
 * straightforward.
 *
 * @sa cml::vector
 * @sa cml::matrix
 */
template<int Dim1 = -1, int Dim2 = -1> struct external;

} // namespace cml

/* Include these here to pick up definition of external<>: */
#include <cml/core/external_1D.h>
#include <cml/core/external_2D.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
