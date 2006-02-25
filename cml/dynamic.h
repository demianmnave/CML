/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_h
#define dynamic_h

#include <memory>               // for std::allocator
#include <cml/core/cml_assert.h>
#include <cml/core/dynamic_1D.h>
#include <cml/core/dynamic_2D.h>

namespace cml {

template< typename Alloc = std::allocator<void> >
struct dynamic
{
    /* Forward declare rebinder for specialization: */
    template<typename DTag, typename Element,
        typename Layout = CML_DEFAULT_ARRAY_LAYOUT> struct rebind;

    /* Specialization for 1D arrays: */
    template<typename E> struct rebind<oned_tag,E,CML_DEFAULT_ARRAY_LAYOUT>
    {
        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<E>::other allocator;
        typedef dynamic_1D<E,allocator> other;
    };

    /* Specialization for row_major 2D arrays: */
    template<typename E> struct rebind<twod_tag,E,row_major>
    {
        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<E>::other allocator;
        typedef dynamic_2D<E,row_major,allocator> other;
    };

    /* Specialization for col_major 2D arrays: */
    template<typename E> struct rebind<twod_tag,E,col_major>
    {
        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<E>::other allocator;
        typedef dynamic_2D<E,col_major,allocator> other;
    };

    /* All other combinations are undefined, and will produce compile-time
     * errors.
     */
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
