/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_h
#define dynamic_h

#include <cstddef>              // for size_t
#include <memory>               // for std::allocator
#include <cml/common.h>
#include <cml/core/dynamic_1D.h>
#include <cml/core/dynamic_2D.h>

namespace cml {

/* Forward declare dynamic<> template.  This is partially specialized below to
 * generate fixed- or dynamic-sized arrays:
 */
template<int Dim1 = 0, int Dim2 = 0, class Alloc = std::allocator<void*> >
    class dynamic;

/** Generate a dynamically-sized and allocated array (1D or 2D).
 *
 * This uses the STL's std::allocator<> if no allocator is provided.
 *
 * @sa cml::vector
 * @sa cml::matrix
 * @sa cml::fixed for more information on the rebinding mechanism.
 */
template<class Alloc> struct dynamic<0,0,Alloc> {

    /* Forward declare the rebinder class to be specialized: */
    template<typename Element, typename Orient = void> struct rebind;

    /** Select a dynamic 1D array of Element's. */
    template<typename Element> struct rebind<Element,void> {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_1D<Element,0,allocator> other;
    };

    /** Select a dynamic 2D array of Element's with orientation Orient. */
    template<typename Element, typename Orient> struct rebind {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_2D<Element,0,0,Orient,allocator> other;
    };
};

/** Generate a dynamically-allocated, fixed-size 1D array.
 *
 * This uses the STL's std::allocator<> if no allocator is provided.
 *
 * @sa cml::vector
 * @sa cml::matrix
 * @sa cml::fixed for more information on the rebinding mechanism.
 */
template<int Size, class Alloc> struct dynamic<Size,0,Alloc> {

    /** Select a dynamic 1D array of Element's. */
    template<typename Element> struct rebind {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_1D<Element,Size,allocator> other;
    };
};

/** Generate a dynamically-allocated, fixed-size 2D array.
 *
 * This uses the STL's std::allocator<> if no allocator is provided.
 *
 * @sa cml::vector
 * @sa cml::matrix
 * @sa cml::fixed for more information on the rebinding mechanism.
 */
template<int Rows, int Cols, class Alloc>
class dynamic
{
  public:

    /* Forward declare the rebinder class to be specialized: */
    template<typename Element, typename Orient> struct rebind;

    /** Select a 2D array of Element's with orientation Orient. */
    template<typename Element, typename Orient> struct rebind {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_2D<Element,Rows,Cols,Orient,allocator> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
