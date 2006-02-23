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
template<int Dim1 = -1, int Dim2 = -1, typename Layout = row_major>
struct fixed
{
    /* Record array size for type deduction: */
    enum { array_size = Dim1, array_rows = Dim1, array_cols = Dim2 };

    /* Record layout for type deduction: */
    typedef Layout layout;

    /* Record memory tag for type deduction: */
    typedef fixed_memory_tag memory_tag;

    /* Record size tag for type deduction: */
    typedef fixed_size_tag size_tag;

    template<typename Tag, typename Element> struct rebind;

    /* Rebind the element type; */
    template<typename Element> struct rebind<oned_tag,Element>
    {
        /* Need Dim1 > 0: */
        CML_STATIC_REQUIRE(Dim1 > 0);

        /* Rebind to a fixed-size 1D array: */
	typedef fixed_1D<Element,Dim1> other;
    };

    /* Rebind the element type; */
    template<typename Element> struct rebind<twod_tag,Element>
    {
        /* Need Dim1,Dim2 > 0: */
        CML_STATIC_REQUIRE(Dim1 > 0 && Dim2 > 0);

        /* Rebind to a fixed-size 2D array: */
	typedef fixed_2D<Element,Dim1,Dim2,Layout> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
