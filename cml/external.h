/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef external_h
#define external_h

namespace cml {

/** This is a selector for external 1D and 2D arrays.
 *
 * The external<> struct has no implementation; it is used only to select a
 * 1D or 2D array as the base class of a vector or matrix.
 *
 * @sa fixed
 * @sa dynamic
 */
template<int Dim1 = -1, int Dim2 = -1> struct external;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
