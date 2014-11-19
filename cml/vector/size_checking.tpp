/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_SIZE_CHECKING_TPP
#error "vector/size_checking.tpp not included correctly"
#endif

#include <cml/common/mpl/array_size_of.h>
#include <cml/vector/readable_vector.h>
#include <cml/vector/promotion.h>

namespace cml {
namespace detail {

/* Compile-time binary vector expression size checking: */
template<class Sub1, class Sub2> inline void check_same_size(
  const readable_vector<Sub1>&, const Sub2&, fixed_size_tag
  )
{
  static_assert(Sub1::array_size == cml::array_size_of_c<Sub2>::value,
    "incompatible vector expression sizes");
}

/* Run-time binary vector expression size checking: */
template<class Sub1, class Sub2> inline void check_same_size(
  const readable_vector<Sub1>& left, const Sub2& right, dynamic_size_tag
  )
{
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
  cml_require(left.size() == cml::array_size_of(right),
    incompatible_vector_size_error, /**/);
#endif
}

/* No-op binary vector expression size checking: */
template<class Sub1, class Sub2> inline void check_same_size(
  const readable_vector<Sub1>&, const Sub2&, any_size_tag) {}



/* Compile-time minimum size checking against a constant. */
template<class Sub, int N> inline void check_minimum_size(
  const readable_vector<Sub>&, cml::int_c<N>, fixed_size_tag
  )
{
  static_assert(Sub::array_size >= N, "vector expression too short");
}

/* Run-time minimum vector size checking. */
template<class Sub, class SizeTag> inline void check_minimum_size(
  const readable_vector<Sub>& sub, int N, SizeTag)
{
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
  cml_require(sub.size() >= N, minimum_vector_size_error, /**/);
#endif
}

/* No-op minimum vector size checking. */
template<class Sub> inline void check_minimum_size(
  const readable_vector<Sub>&, int, any_size_tag) {}



/* Compile-time size checking against a constant. */
template<class Sub, int N> inline void check_size(
  const readable_vector<Sub>&, cml::int_c<N>, fixed_size_tag
  )
{
  static_assert(Sub::array_size == N, "incorrect vector expression size");
}

/* Run-time vector size checking. */
template<class Sub, class SizeTag> inline void check_size(
  const readable_vector<Sub>& sub, int N, SizeTag)
{
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
  cml_require(sub.size() == N, vector_size_error, /**/);
#endif
}

/* No-op vector size checking. */
template<class Sub> inline void check_size(
  const readable_vector<Sub>&, int, any_size_tag) {}

} // namespace detail


/* check_same_size: */

template<class Sub1, class Sub2> void
check_same_size(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  typedef vector_size_tag_of_t<Sub1> tag1;
  typedef vector_size_tag_of_t<Sub2> tag2;
  detail::check_same_size(
    left, right.actual(), size_check_promote_t<tag1,tag2>());
}

template<class Sub1, class Sub2> void
check_same_size(
  const readable_vector<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>*
  )
{
  typedef vector_size_tag_of_t<Sub1> tag1;
  typedef tag1 tag2;			// dynamic/dynamic or fixed/fixed.
  detail::check_same_size(left, right, size_check_promote_t<tag1,tag2>());
}

template<class Sub1, class Sub2> auto
check_same_size(const readable_vector<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void())
{
  typedef vector_size_tag_of_t<Sub1> tag1;
  typedef dynamic_size_tag tag2;	// dynamic/dynamic or fixed/dynamic.
  detail::check_same_size(left, right, size_check_promote_t<tag1,tag2>());
}


/* check_minimum_size: */

template<class Sub> void
check_minimum_size(const readable_vector<Sub>& left, int N)
{
  typedef vector_size_tag_of_t<Sub> tag;
  detail::check_minimum_size(left, N, tag());
}

template<class Sub, int N> void
check_minimum_size(const readable_vector<Sub>& left, cml::int_c<N>)
{
  typedef vector_size_tag_of_t<Sub> tag;
  detail::check_minimum_size(left, cml::int_c<N>(), tag());
}


/* check_size: */

template<class Sub> void
check_size(const readable_vector<Sub>& left, int N)
{
  typedef vector_size_tag_of_t<Sub> tag;
  detail::check_size(left, N, tag());
}

template<class Sub, int N> void
check_size(const readable_vector<Sub>& left, cml::int_c<N>)
{
  typedef vector_size_tag_of_t<Sub> tag;
  detail::check_size(left, cml::int_c<N>(), tag());
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
