/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef fixed_h
#define fixed_h

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
template<int Dim1 = -1, int Dim2 = -1,
    typename Layout = CML_DEFAULT_ARRAY_LAYOUT> struct fixed;

/** Specialization for vectors. */
template<int Size>
struct fixed<Size,-1,CML_DEFAULT_ARRAY_LAYOUT>
{
    /* Need Size > 0: */
    CML_STATIC_REQUIRE(Size > 0);

    /* Record array size for type deduction: */
    enum { array_size = Size };

    /* Record memory tag for type deduction: */
    typedef fixed_memory_tag memory_tag;

    /* Record size tag for type deduction: */
    typedef fixed_size_tag size_tag;

    /* Forward declare for specialization: */
    template<typename Tag, typename Element> struct rebind;

    /* Rebind the element type to a fixed 1D array; */
    template<typename Element> struct rebind<oned_tag,Element> {
	typedef fixed_1D<Element,Size> other;
    };
};

/** Specializations for matrices. */
template<int Rows, int Cols, typename Layout>
struct fixed
{
    /* Need Rows,Cols > 0: */
    CML_STATIC_REQUIRE(Rows > 0 && Cols > 0);

    /* Record array size for type deduction: */
    enum { array_rows = Rows, array_cols = Cols };

    /* Record layout for type deduction: */
    typedef Layout layout;

    /* Record memory tag for type deduction: */
    typedef fixed_memory_tag memory_tag;

    /* Record size tag for type deduction: */
    typedef fixed_size_tag size_tag;

    /* To simplify the matrix transpose operator: */
    typedef fixed<Cols,Rows,Layout> transposed_type;

    /* Forward declare for specialization: */
    template<typename Tag, typename Element> struct rebind;

    /* Rebind the element type to a fixed 2D array; */
    template<typename Element> struct rebind<twod_tag,Element> {
	typedef fixed_2D<Element,Rows,Cols,Layout> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
