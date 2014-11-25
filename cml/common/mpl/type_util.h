/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_mpl_type_util_h
#define	cml_common_mpl_type_util_h

#include <utility>
#include <cml/common/compiler.h>
#include <cml/common/mpl/if_t.h>

namespace cml {

/** Remove const-volatile and reference types from @c T, but leave array and
 * function pointer types alone.
 */
template<class T> struct unqualified_type {
  typedef typename std::remove_cv<
    typename std::remove_reference<T>::type>::type type;
};

/** Convenience alias for unqualified_type. */
template<class T> using unqualified_type_t
  = typename cml::unqualified_type<T>::type;

/** Defines typedef @c type as std::true_type if @c T has a member function
 * actual() that returns a reference type, or std::false_type otherwise.
 * The static bool @c value is set to true or false to match @c type.
 */
template<class T> struct is_statically_polymorphic {

  private:

  /* SFINAE overload to deduce the return type of T::actual, if it exists. */
  template<class U> static auto get_type_of_actual(int)
    -> decltype(std::declval<U>().actual());

  /* The default overload deduces a void return type. */
  template<class U> static auto get_type_of_actual(...)
    -> void;

  /* Strip const, volatile, and reference from T to detect actual(): */
  typedef cml::unqualified_type_t<T> naked_type;


  public:

  /* std::true_type if T::actual is a member function returning a
   * reference type, std::false_type otherwise.
   */
  typedef cml::if_t<
    std::is_reference<decltype(get_type_of_actual<naked_type>(0))>::value,
    std::true_type, std::false_type> type;

  /* True or false, depending upon 'type': */
  static const bool value = type::value;
};

/** Deduce the derived type of a statically polymorphic type @c T.  @c T
 * must implement a method, actual(), having a reference return type based
 * on @c T (e.g. T&, const T&).
 */
template<class T> struct actual_type_of {
  private:
  static_assert(is_statically_polymorphic<T>::value,
    "T does not implement actual() returning a reference type");

  /* Strip const, volatile, and reference from T to get the return type
   * of T::actual:
   */
  typedef cml::unqualified_type_t<T>			naked_type;


  public:

  /* Deduce the return type of T::actual: */
  typedef cml::unqualified_type_t<
    decltype(std::declval<naked_type>().actual())>	type;
};

/** Convenience alias for actual_type_of<>. */
template<class T> using actual_type_of_t = typename actual_type_of<T>::type;

/** Defines @c type as a reference to the derived type of a
 * statically polymorphic type @c T.  For example, if @c T is
 * readable_matrix<S>&, then @c type is S&.  The const-ness of @c T is
 * maintained for lvalue references.
 */
template<class T> struct actual_operand_type_of {
  private:

  /* Possibly const, non-reference type: */
  typedef typename std::remove_reference<T>::type	base_type;

  /* Derived type of T: */
  typedef actual_type_of_t<base_type>			actual_type;


  public:

  /* Build the reference type: */
  typedef cml::if_t<
    std::is_rvalue_reference<T>::value, actual_type&&,
      cml::if_t<std::is_const<base_type>::value,
      const actual_type&, actual_type&>>		type;
};

/** Convenience alias for actual_operand_type_of<>. */
template<class T> using actual_operand_type_of_t
  = typename actual_operand_type_of<T>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
