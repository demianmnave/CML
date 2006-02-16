/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief A few simple metaprogramming tools.
 */

#ifndef cml_meta_h
#define cml_meta_h

/** Type of a true statement. */
struct true_type {};

/** Type of a false statement. */
struct false_type {};

/** Determine if two types are the same.
 *
 * Defaults to false.
 */
template<typename T, typename U> struct same_type {
    typedef false_type result;
    enum { is_true = false };
};

/** Match the same type for both of same_type's template arguments. */
template<typename T> struct same_type<T,T> {
    typedef true_type result;
    enum { is_true = true };
};

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
