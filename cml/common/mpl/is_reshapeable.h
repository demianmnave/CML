/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

namespace cml {

/** Helper that defines @c type as std::true_type and @c value as true if
 * @c T implements resize(m,n), where m and n are convertible from int.
 */
template<class T> struct is_reshapeable
{
  /* Overload resolution trickery to determine if T implements resize(): */

  private:
  template<class X>
  static inline auto has_resize(X&&)
    -> decltype(std::declval<X>().actual().resize(0, 0), std::true_type());

  template<class... X> static inline auto has_resize(X...) -> std::false_type;

  public:
  /** std::true_type if @c T has a compatible resize() method,
   * std::false_type otherwise.
   */
  using type = decltype(has_resize(std::declval<T>()));

  /** true if @c T has a compatible resize() method, false otherwise. */
  static const int value = type::value;
};

}  // namespace cml
