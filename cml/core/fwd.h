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

#ifndef core_fwd_h
#define core_fwd_h

namespace cml {

/* cml/core/fixed_1D.h */
template<typename E, int S> class fixed_1D;

/* cml/core/fixed_2D.h */
template<typename E, int R, int C, typename L> class fixed_2D;

/* cml/core/dynamic_1D.h */
template<typename E, class A> class dynamic_1D;

/* cml/core/dynamic_2D.h */
template<typename E, typename L, class A> class dynamic_2D;

/* cml/core/external_1D.h */
template<typename E, int S> class external_1D;

/* cml/core/external_2D.h */
template<typename E, int R, int C, typename L> class external_2D;

/* cml/fixed.h */
template<int Dim1, int Dim2> struct fixed;

/* cml/dynamic.h */
template<typename Alloc> struct dynamic;

/* cml/external.h */
template<int Dim1, int Dim2> struct external;

/* cml/vector.h */
template<typename E, class AT> class vector;

/* cml/matrix.h */
template<typename E, class AT, typename L> class matrix;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
