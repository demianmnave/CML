/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef fixed_h
#define fixed_h

#include <cstddef>              // for size_t
#include <cml/common.h>
#include <cml/core/fixed_1D.h>
#include <cml/core/fixed_2D.h>

namespace cml {

/* Forward declare the fixed<> array class; it's specialized below: */
template<int Dim1, int Dim2 = 0> class fixed;

/** Select a statically-allocated 1D array.
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
template<int Size> struct fixed<Size,0> {

    /** Select a static 1D array of Element's. */
    template<typename Element> struct rebind {
	typedef fixed_1D<Element,Size> other;
    };
};

/** Select a statically-allocated 2D array.
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
template<int Rows, int Cols> struct fixed {

    /** Select a static 2D array of Element's. */
    template<typename Element, typename Orient> struct rebind {
	typedef fixed_2D<Element,Rows,Cols,Orient> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
