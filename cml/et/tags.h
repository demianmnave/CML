/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef tags_h
#define tags_h

namespace cml {
namespace et {

/** Tag an expression as returning a scalar. */
struct scalar_result_tag {};

/** Tag an expression as returning a vector. */
struct vector_result_tag {};

/** Tag an expression as returning a matrix. */
struct matrix_result_tag {};

/** Marker for unary expression ops. */
struct unary_expression {};

/** Marker for biary expression ops. */
struct binary_expression {};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
