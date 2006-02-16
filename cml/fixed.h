/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef fixed_h
#define fixed_h

#include <cstddef>              // for size_t
#include <cml/core/cml_assert.h>
#include <cml/core/fixed_1D.h>
#include <cml/core/fixed_2D.h>

namespace cml {

/* Forward declare the fixed<> array class; it's specialized below: */
template<int Dim1, int Dim2 = 0> struct fixed;

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
 */
template<int Size> struct fixed<Size,0>
{
    /* Need Size > 0: */
    CML_STATIC_REQUIRE( (Size > 0) );

    /* Record array size for type deduction: */
    enum { array_size = Size };

    /* Record size tag for type deduction: */
    typedef fixed_size_tag size_tag;

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
 */
template<int Rows, int Cols> struct fixed
{
    /* Need Rows,Cols > 0: */
    CML_STATIC_REQUIRE(((Rows > 0) && (Cols > 0)));

    /* Record array size for type deduction: */
    enum { array_rows = Rows, array_cols = Cols };

    /* Record size tag for type deduction: */
    typedef fixed_size_tag size_tag;

    /** Select a static 2D array of Element's. */
    template<typename Element, typename Orient> struct rebind {
	typedef fixed_2D<Element,Rows,Cols,Orient> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
