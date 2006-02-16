/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef common_h
#define common_h

namespace cml {

/** Statically-allocated memory tag. */
struct fixed_memory_tag {};

/** Dynamically-allocated memory tag. */
struct dynamic_memory_tag {};

/** Statically-sized tag. */
struct fixed_size_tag {};

/** Dynamically-sized tag. */
struct dynamic_size_tag {};

/** Unit-sized tag. */
struct unit_size_tag {};

/** Row-major storage tag. */
struct row_major {};

/** Col-major storage tag. */
struct col_major {};

/** Column vector tag. */
struct col_vector {};

#if !defined(CML_IGNORE_VECTOR_ORIENTATION)
/** Row vector tag. */
struct row_vector {};
#else
/* Assume col_vector's always: */
typedef col_vector row_vector;
#endif

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
