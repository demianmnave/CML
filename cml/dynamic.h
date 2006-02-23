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

/** Generate a dynamically-sized and allocated array (1D or 2D).
 *
 * This uses the STL's default std::allocator<> if no allocator is
 * provided.
 *
 * @sa cml::vector
 * @sa cml::fixed for more information on the rebinding mechanism.
 *
 * @internal The std::allocator<void> default for Alloc is necessary to
 * allow dynamic<> to work properly, but it's not actually used since the
 * proper allocator is selected by rebinding from the derived class.
 */
template<typename T1 = void, typename T2 = void>
struct dynamic
{
  protected:

    /* This stuff below allows arguments to dynamic<> to be specified more
     * naturally.  If dynamic<> were defined like this
     *
     *    template<typename Layout = row_major,
     *                  typename Alloc = std::allocator<void> >
     *    struct dynamic;
     *
     * both Layout = row_major and Alloc = <something> would have to be
     * specified to set <something> as the allocator.  Using the scheme
     * below, a new allocator can be chosen without having to explicitly
     * specify a Layout as well. i.e.:
     *
     *    dynamic<row_major>
     *    dynamic<col_major>
     *      (Allocator defaults to std::allocator<void>)
     *
     *    dynamic< std::allocator<void> >
     *      (Layout defaults to row_major)
     *
     *    dynamic< row_major, std::allocator<void> >
     *      (Specify both the layout and the allocator)
     *
     * This is a bit tricky to implement, though, even with only a few
     * combos.  The select_switch<> below implements the following table:
     *
     *   T1       T2      Layout    Alloc
     * 1 void     void -> row_major default_alloc
     * 3 <layout> void -> <layout>  default_alloc
     * 2 <T1>     void -> row_major <T1>
     * 4 <layout> <T2> -> <layout>  <T2>
     *
     * Warning: these have to be ordered properly to pick up the void cases
     * before the T2-specific cases:
     */
    typedef std::allocator<void> default_alloc;
    typedef typename select_switch<
        type_pair<T1,T2>,

        /* Cases: */

        /*1*/ type_pair<void,void>,      type_pair<row_major,default_alloc>,

        /*2*/ type_pair<row_major,void>, type_pair<row_major,default_alloc>,
              type_pair<col_major,void>, type_pair<col_major,default_alloc>,

        /*3*/ type_pair<T1,void>,        type_pair<row_major,T1>,

        /*4*/ type_pair<row_major,T2>,   type_pair<row_major,T2>,
              type_pair<col_major,T2>,   type_pair<col_major,T2>,

        /* Default is an error (void): */
        meta::Default,                   void
    >::result decoded_args;

    /* Unpack the resulting type: */
    typedef typename decoded_args::first Layout;
    typedef typename decoded_args::second Alloc;


  public:

    /* Record array size for type deduction (for 1D and 2D dynamic-sized
     * arrays, all sizes are -1):
     */
    enum { array_size = -1, array_rows = -1, array_cols = -1 };

    /* Record layout for type deduction: */
    typedef Layout layout;

    /* Record allocator for type deduction: */
    typedef Alloc allocator_type;

    /* Record memory tag for type deduction: */
    typedef dynamic_memory_tag memory_tag;

    /* Record size tag for type deduction: */
    typedef dynamic_size_tag size_tag;

    /* Forward declare the rebinder class to be specialized: */
    template<typename Tag, typename Element> struct rebind;

    /** Select a dynamic 1D array of Element's. */
    template<typename Element> struct rebind<oned_tag,Element> {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_1D<Element,allocator> other;
    };

    /** Select a dynamic 2D array of Element's with layout Layout. */
    template<typename Element> struct rebind<twod_tag,Element> {

        /* Have to rebind the allocator to the right element type: */
        typedef typename Alloc::template rebind<Element>::other allocator;
	typedef dynamic_2D<Element,Layout,allocator> other;
    };
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
