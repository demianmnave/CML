/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <utility>
#include <cml/common/mpl/is_statically_polymorphic.h>

namespace cml {
/** Remove const-volatile and reference types from @c T, but leave array and
 * function pointer types alone.
 */
template<class T> struct unqualified_type
{
  using type = typename std::remove_cv<typename std::remove_reference<
    T>::type>::type;
};

/** Convenience alias for unqualified_type. */
template<class T>
using unqualified_type_t = typename cml::unqualified_type<T>::type;

/** Deduce the derived type of a statically polymorphic type @c T from the
 * reference return type of @c T::actual, if defined.  If @c T does not
 * implement @c T::actual having a reference return type, then @c type is
 * defined as the unqualified base type of @c T.
 */
template<class T> struct actual_type_of
{
  private:
  /* Strip const, volatile, and reference from T to get the return type
   * of T::actual:
   */
  using naked_type = cml::unqualified_type_t<T>;

  /* SFINAE overload to deduce the return type of T::actual, if it exists. */
  template<class U>
  static auto get_naked_type_of_actual(int)
    -> cml::unqualified_type_t<decltype(std::declval<U>().actual())>;

  /* The default overload deduces a void return type. */
  template<class U> static auto get_naked_type_of_actual(...) -> void;

  public:
  /* Deduce the return type of T::actual: */
  using type = cml::if_t<is_statically_polymorphic<naked_type>::value,
    decltype(get_naked_type_of_actual<naked_type>(0)), naked_type>;
};

/** Convenience alias for actual_type_of<>. */
template<class T> using actual_type_of_t = typename actual_type_of<T>::type;

/** If @c T is a reference type, @c type is defined as a reference to the
 * derived type of a statically polymorphic type @c T, or as @c T for other
 * types.  For example, if @c T is readable_matrix<S>&, then @c type is S&.
 * The const-ness of @c T is maintained for lvalue references.
 */
template<class T> struct actual_operand_type_of
{
  private:
  static_assert(std::is_reference<T>::value, "T is not a reference type");

  /* Possibly const, non-reference type: */
  using base_type = typename std::remove_reference<T>::type;

  /* Derived type of T: */
  using actual_type = actual_type_of_t<base_type>;

  public:
  /* Build the reference type: */
  using type = cml::if_t<std::is_rvalue_reference<T>::value, actual_type&&,
    cml::if_t<std::is_const<base_type>::value, const actual_type&,
      actual_type&>>;
};

/** Convenience alias for actual_operand_type_of<>. */
template<class T>
using actual_operand_type_of_t = typename actual_operand_type_of<T>::type;
} // namespace cml
