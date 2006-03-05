/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Forward declarations, useful to avoid including lots of headers.
 *
 * @sa cml/et/array_promotions.h
 */

#ifndef fwd_h
#define fwd_h

namespace cml {

/* cml/core/fixed_1D.h */
template<typename E, int S> class fixed_1D;

/* cml/core/fixed_2D.h */
template<typename E, int R, int C, typename L> class fixed_2D;

/* cml/core/dynamic_1D.h */
template<typename E, class A> class dynamic_1D;

/* cml/core/dynamic_2D.h */
template<typename E, typename L, class A> class dynamic_2D;

}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
