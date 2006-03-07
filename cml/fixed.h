/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef fixed_h
#define fixed_h

namespace cml {


/** This is a selector for fixed 1D and 2D arrays.
 *
 * The fixed<> struct has no implementation; it is used only to select a
 * 1D or 2D array as the base class of a vector or matrix.
 *
 * @sa dynamic
 * @sa external
 */
template<int Dim1 = -1, int Dim2 = -1> struct fixed;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
