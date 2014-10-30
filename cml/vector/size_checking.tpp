/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_SIZE_CHECKING_TPP
#error "vector/size_checking.tpp not included correctly"
#endif

#include <cml/common/mpl/array_size_of.h>

namespace cml {
namespace detail {

/** Run-time size checking between a vector and another object implementing
 * a size() method or a fixed-length array, when enabled.
 */
template<class SizeTag1, class SizeTag2> struct checked_size
{
  /** Check against array_size_of(right). */
  template<class Sub1, class Sub2> static void
    check(const readable_vector<Sub1>& left, const Sub2& right)
  {
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
    cml_require(left.actual().size() == cml::array_size_of(right),
      incompatible_vector_sizes, /**/);
#endif
  }
};

/** Compile-time size checking of fixed-size vector expressions. */
template<> struct checked_size<fixed_size_tag, fixed_size_tag>
{
  /** Check for a fixed-length vector or array. */
  template<class Sub1, class Sub2> static void
    check(const readable_vector<Sub1>&, const Sub2&)
  {
    static_assert(Sub1::array_size == cml::array_size_of_c<Sub2>::value,
      "incompatible vector expression sizes");
  }
};

} // namespace detail

template<class Sub1, class Sub2> void
check_same_size(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  typedef cml::size_tag_of<Sub1> tag1;
  typedef cml::size_tag_of<Sub2> tag2;
  detail::checked_size<tag1,tag2>::check(left.actual(), right.actual());
}

template<class Sub1, class Sub2> void
check_same_size(
  const readable_vector<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>*
  )
{
  typedef cml::size_tag_of<Sub1> tag1;
  typedef tag1 tag2;			// dynamic/dynamic or fixed/fixed.
  detail::checked_size<tag1,tag2>::check(left.actual(), right);
}

template<class Sub1, class Sub2> auto
check_same_size(const readable_vector<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void())
{
  typedef cml::size_tag_of<Sub1> tag1;
  typedef dynamic_size_tag tag2;	// dynamic/dynamic or fixed/dynamic.
  detail::checked_size<tag1,tag2>::check(left.actual(), right);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
