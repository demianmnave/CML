/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_type_util_h
#define	cml_matrix_type_util_h

#include <cml/common/type_util.h>
#include <cml/matrix/readable_matrix.h>

namespace cml {

/** Defines typedef @c type as std::true_type if @c T is statically
 * polymorphic and derived from @c readable_matrix, or std::false_type
 * otherwise.  The static bool @c value is set to true or false to match @c
 * type.
 */
template<class T> struct is_matrix {
  private:

  /* Strip const, volatile, and reference from T to get the type to test: */
  typedef cml::unqualified_type_t<T>			naked_type;

  /* Deduce the derived type (fails if T is not statically polymorphic): */
  typedef actual_type_of_t<naked_type>			derived_type;


  public:

  /* std::true_type if T is derived from readable_matrix<>, std::false_type
   * otherwise:
   */
  typedef std::is_base_of<
    readable_matrix<derived_type>, naked_type>		type;

  /* True or false, depending upon 'type': */
  static const bool value = type::value;
};

/** Defines @c type to be the matrix_traits of the actual type of @c Sub. */
template<class Sub> struct matrix_traits_of {
  typedef matrix_traits<actual_type_of_t<Sub>> type;
};

/** Convenience alias for matrix_traits_of. */
template<class Sub> using matrix_traits_of_t
  = typename matrix_traits_of<Sub>::type;

/** Defines @c type to be the element type of the matrix expression. */
template<class Sub> struct matrix_element_type_of {
  typedef matrix_traits_of_t<Sub> traits_type;
  typedef typename traits_type::value_type type;
};

/** Convenience alias for matrix_element_type_of. */
template<class Sub> using matrix_element_type_of_t
  = typename matrix_element_type_of<Sub>::type;


/** Wrapper for enable_if to detect matrix types (derived from
 * readable_matrix).
 */
template<class Sub> struct enable_if_matrix
: std::enable_if<cml::is_matrix<Sub>::value> {};

/** Convenience alias for enable_if_matrix. */
template<class Sub> using enable_if_matrix_t
  = typename enable_if_matrix<Sub>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
