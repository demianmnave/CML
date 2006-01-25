/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Defines promotions between array types.
 *
 * @todo Not all type combinations are represented here.
 */

#ifndef array_promotions_h
#define array_promotions_h

#include <cml/fixed.h>
#include <cml/dynamic.h>

namespace cml {
namespace et {

/** Class to promote array types. */
template<class AT1, class AT2>
struct ArrayPromote
{
    template<typename SizeT1, typename SizeT2, typename U=void> struct deduce;

    /* Record array sizes for later: */
    enum { L1 = AT1::array_size, L2 = AT2::array_size };

    /* Record size tags for later: */
    typedef typename AT1::size_tag left_tag;
    typedef typename AT2::size_tag right_tag;


    /** Promote fixed-size/fixed-size to fixed<>. */
    template<typename U> struct deduce<fixed_size_tag,fixed_size_tag,U> {
        typedef cml::fixed< ((L1>L2)?L1:L2) > type;
    };

    /** Promote fixed-size/any to fixed<>. */
    template<typename ST, typename U> struct deduce<ST,fixed_size_tag,U> {
        typedef cml::fixed< ((L1>L2)?L1:L2) > type;
    };

    /** Promote any/fixed-size to fixed<>. */
    template<typename ST, typename U> struct deduce<fixed_size_tag,ST,U> {
        typedef cml::fixed< ((L1>L2)?L1:L2) > type;
    };

    /** Promote dynamic-size/dynamic-size to dynamic<>.
     *
     * @bug This always uses the allocator of the left-hand type.
     */
    template<typename U> struct deduce<dynamic_size_tag,dynamic_size_tag,U> {
        typedef cml::dynamic<typename AT1::allocator_type> type;
    };

    /** Compute the type promotion. */
    typedef typename deduce<left_tag, right_tag>::type type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
