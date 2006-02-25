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
template<int Dim1 = -1, int Dim2 = -1>
struct fixed
{
    /* Forward declare rebinder for specialization: */
    template<typename DTag, typename Element,
        typename Layout = CML_DEFAULT_ARRAY_LAYOUT> struct rebind;

    /* Specialization for 1D arrays: */
    template<typename E> struct rebind<oned_tag,E,CML_DEFAULT_ARRAY_LAYOUT>
    {
        /* Require Dim1 > 0, Dim2 = -1: */
        CML_STATIC_REQUIRE((Dim1 > 0) && (Dim2 == -1));
        typedef fixed_1D<E,Dim1> other;
    };

    /* Specialization for row_major 2D arrays: */
    template<typename E> struct rebind<twod_tag,E,row_major>
    {
        /* Require Dim1,Dim2 > 0: */
        CML_STATIC_REQUIRE((Dim1 > 0) && (Dim2 > 0));
        typedef fixed_2D<E,Dim1,Dim2,row_major> other;
    };

    /* Specialization for col_major 2D arrays: */
    template<typename E> struct rebind<twod_tag,E,col_major>
    {
        /* Require Dim1,Dim2 > 0: */
        CML_STATIC_REQUIRE((Dim1 > 0) && (Dim2 > 0));
        typedef fixed_2D<E,Dim1,Dim2,col_major> other;
    };

    /* All other combinations are undefined, and will produce compile-time
     * errors.
     */
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
