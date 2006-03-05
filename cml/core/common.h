/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef core_common_h
#define core_common_h

#include <cstddef>              // for size_t
#include <utility>              // for std::pair<>
#include <cml/defaults.h>

namespace cml {

/** 1D tag (to select array shape). */
struct oned_tag {};

/** 2D tag (to select array shape). */
struct twod_tag {};

/** Statically-allocated memory tag. */
struct fixed_memory_tag {};

/** Dynamically-allocated memory tag. */
struct dynamic_memory_tag {};

/** Externally-allocated memory tag. */
struct external_memory_tag {};

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

/** Error tag (undefined struct) for bad layout. */
struct invalid_layout;

/** Column vector tag. */
struct col_vector {};

#if defined(CML_IGNORE_VECTOR_ORIENTATION)
/* Assume col_vector always: */
typedef col_vector row_vector;
#else
/** Row vector tag. */
struct row_vector {};
#endif

/* This is the pair returned from the matrix size() method, as well as from
 * the matrix expression size checking code:
 */
typedef std::pair<size_t,size_t> matrix_size;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
