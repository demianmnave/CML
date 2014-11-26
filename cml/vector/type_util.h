/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_type_util_h
#define	cml_vector_type_util_h

#include <cml/common/type_util.h>
#include <cml/vector/readable_vector.h>

namespace cml {

/** Defines typedef @c type as std::true_type if @c T is statically
 * polymorphic and derived from @c readable_vector, or std::false_type
 * otherwise.  The static bool @c value is set to true or false to match @c
 * type.
 */
template<class T> struct is_vector {
  private:

  /* Strip const, volatile, and reference from T to get the type to test: */
  typedef cml::unqualified_type_t<T>			naked_type;

  /* Deduce the derived type (fails if T is not statically polymorphic): */
  typedef actual_type_of_t<naked_type>			derived_type;


  public:

  /* std::true_type if T is derived from readable_vector<>, std::false_type
   * otherwise:
   */
  typedef std::is_base_of<
    readable_vector<derived_type>, naked_type>		type;

  /* True or false, depending upon 'type': */
  static const bool value = type::value;
};

/** Defines @c type to be the vector_traits of the actual type of @c Sub. */
template<class Sub> struct vector_traits_of {
  typedef vector_traits<actual_type_of_t<Sub>> type;
};

/** Convenience alias for vector_traits_of. */
template<class Sub> using vector_traits_of_t
  = typename vector_traits_of<Sub>::type;

/** Defines @c type to be the element type of the vector expression. */
template<class Sub> struct vector_element_type_of {
  typedef vector_traits_of_t<Sub> traits_type;
  typedef typename traits_type::value_type type;
};

/** Convenience alias for vector_element_type_of. */
template<class Sub> using vector_element_type_of_t
  = typename vector_element_type_of<Sub>::type;


/** Wrapper for enable_if to detect vector types (derived from
 * readable_vector).
 */
template<class Sub> struct enable_if_vector
: std::enable_if<cml::is_vector<Sub>::value> {};

/** Convenience alias for enable_if_vector. */
template<class Sub> using enable_if_vector_t
  = typename enable_if_vector<Sub>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
