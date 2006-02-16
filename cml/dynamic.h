/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_h
#define dynamic_h

#include <memory>               // for std::allocator
#include <cml/common.h>
#include <cml/core/dynamic_1D.h>
#include <cml/core/dynamic_2D.h>

namespace cml {

/** Generate a dynamically-sized and allocated array (1D or 2D).
 *
 * This uses the STL's default std::allocator<> if no allocator is
 * provided.
 *
 * @sa cml::vector
 * @sa cml::fixed for more information on the rebinding mechanism.
 *
 * @internal The std::allocator<void*> default for Alloc is necessary to
 * allow dynamic<> to work properly, but it's not actually used since the
 * proper allocator is selected by rebinding from the derived class.
 */
template<class Alloc = std::allocator<void*> > struct dynamic
{
    /* Record array size for type deduction (for 1D and 2D dynamic-sized
     * arrays, all sizes are -1):
     */
    enum { array_size = -1, array_rows = -1, array_cols = -1 };

    /* Record size tag for type deduction: */
    typedef dynamic_size_tag size_tag;

    /* Record allocator type for type deduction: */
    typedef Alloc allocator_type;


    /* Forward declare the rebinder class to be specialized: */
    template<typename Element, typename Orient = void> struct rebind;

    /** Select a dynamic 1D array of Element's. */
    template<typename Element> struct rebind<Element,void> {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_1D<Element,allocator> other;
    };

    /** Select a dynamic 2D array of Element's with orientation Orient. */
    template<typename Element, typename Orient> struct rebind {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_2D<Element,Orient,allocator> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
