/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_SIZE_CHECKING_TPP
#error "vector/size_checking.tpp not included correctly"
#endif

#include <cml/common/mpl/array_size_of.h>
#include <cml/common/size_tags.h>
#include <cml/vector/readable_vector.h>

namespace cml {
namespace detail {

/** Run-time size checking between a vector and another object implementing
 * a size() method or a fixed-length array, when enabled.
 */
template<class SizeTag1, class SizeTag2> struct check_binary_size
{
  /** Check against array_size_of(right). */
  template<class Sub1, class Sub2> static void
    check(const readable_vector<Sub1>& left, const Sub2& right)
    {
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
      cml_require(left.actual().size() == cml::array_size_of(right),
	incompatible_vector_size_error, /**/);
#endif
    }
};

/** Compile-time size checking of fixed-size vector expressions. */
template<> struct check_binary_size<fixed_size_tag, fixed_size_tag>
{
  /** Check for a fixed-length vector or array. */
  template<class Sub1, class Sub2> static void
    check(const readable_vector<Sub1>&, const Sub2&)
    {
      static_assert(Sub1::array_size == cml::array_size_of_c<Sub2>::value,
	"incompatible vector expression sizes");
    }
};


/** Run-time minimum size checking. */
template<class Sub, class SizeTag> void check_minimum_size(
  const readable_vector<Sub>& sub, int N, SizeTag)
{
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
  cml_require(sub.actual().size() >= N, minimum_vector_size_error, /**/);
#endif
}

/** Run-time minimum size checking against a constant. */
template<class Sub, int N> void check_minimum_size(
  const readable_vector<Sub>& sub, cml::int_c<N>, dynamic_size_tag)
{
  check_minimum_size(sub, N, dynamic_size_tag());
}

/** Compile-time minimum size checking against a constant. */
template<class Sub, int N> void check_minimum_size(
  const readable_vector<Sub>&, cml::int_c<N>, fixed_size_tag)
{
  static_assert(Sub::array_size >= N, "vector expression too short");
}


/** Run-time size checking. */
template<class Sub, class SizeTag> void check_size(
  const readable_vector<Sub>& sub, int N, SizeTag)
{
#ifndef CML_NO_RUNTIME_VECTOR_SIZE_CHECKS
  cml_require(sub.actual().size() == N, vector_size_error, /**/);
#endif
}

/** Run-time size checking against a constant. */
template<class Sub, int N> void check_size(
  const readable_vector<Sub>& sub, cml::int_c<N>, dynamic_size_tag)
{
  check_size(sub, N, dynamic_size_tag());
}

/** Compile-time size checking against a constant. */
template<class Sub, int N> void check_size(
  const readable_vector<Sub>&, cml::int_c<N>, fixed_size_tag)
{
  static_assert(Sub::array_size == N, "incorrect vector expression size");
}

} // namespace detail


/* check_same_size: */

template<class Sub1, class Sub2> void
check_same_size(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  typedef size_tag_of<Sub1> tag1;
  typedef size_tag_of<Sub2> tag2;
  detail::check_binary_size<tag1,tag2>::check(left.actual(), right.actual());
}

template<class Sub1, class Sub2> void
check_same_size(
  const readable_vector<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>*
  )
{
  typedef size_tag_of<Sub1> tag1;
  typedef tag1 tag2;			// dynamic/dynamic or fixed/fixed.
  detail::check_binary_size<tag1,tag2>::check(left.actual(), right);
}

template<class Sub1, class Sub2> auto
check_same_size(const readable_vector<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void())
{
  typedef size_tag_of<Sub1> tag1;
  typedef dynamic_size_tag tag2;	// dynamic/dynamic or fixed/dynamic.
  detail::check_binary_size<tag1,tag2>::check(left.actual(), right);
}


/* check_minimum_size: */

template<class Sub> void
check_minimum_size(const readable_vector<Sub>& left, int N)
{
  typedef size_tag_of<Sub> tag;
  detail::check_minimum_size(left, N, tag());
}

template<class Sub, int N> void
check_minimum_size(const readable_vector<Sub>& left, cml::int_c<N>)
{
  typedef size_tag_of<Sub> tag;
  detail::check_minimum_size(left, cml::int_c<N>(), tag());
}


/* check_size: */

template<class Sub> void
check_size(const readable_vector<Sub>& left, int N)
{
  typedef size_tag_of<Sub> tag;
  detail::check_size(left, N, tag());
}

template<class Sub, int N> void
check_size(const readable_vector<Sub>& left, cml::int_c<N>)
{
  typedef size_tag_of<Sub> tag;
  detail::check_size(left, cml::int_c<N>(), tag());
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
