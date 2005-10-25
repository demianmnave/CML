/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef common_h
#define common_h

namespace cml {

/** Empty base class used before rebinding has happened. */
struct empty_base_class {};

/** Empty class to demarcate statically-allocated memory. */
struct fixed_memory_tag {};

/** Empty class to demarcate dynamically-allocated memory. */
struct dynamic_memory_tag {};

/** Empty class to demarcate statically-sized arrays. */
struct fixed_size_tag {};

/** Empty class to demarcate dynamically-sized arrays. */
struct dynamic_size_tag {};

/** Empty class to demarcate constants. */
struct unit_size_tag {};

/** Empty class to demarcate a matrix having row-major storage. */
struct row_major {};

/** Empty class to demarcate a matrix having col-major storage. */
struct col_major {};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
