/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_size_checking_h
#define	cml_vector_size_checking_h

#include <cml/common/mpl/enable_if_array.h>
#include <cml/common/exception.h>
#include <cml/vector/readable_vector.h>

namespace cml {

/** Exception thrown when run-time size checking is enabled, and the
 * operands of a vector expression have incompatible sizes.
 */
struct incompatible_vector_sizes : std::runtime_error {
  incompatible_vector_sizes()
    : std::runtime_error("incompatible vector expression sizes") {}
};

/** Front-end for both compile-time and run-time binary expression length
 * checking.  Both expressions must derive from readable_vector.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First vector expression.
 * @param right Second vector expression.
 *
 * @throws incompatible_vector_sizes at run-time if either Sub1 or Sub2 is
 * a dynamically-sized vector, and sub1.size() != sub2.size().  If both
 * Sub1 and Sub2 are fixed-size expressions, then the sizes are checked at
 * compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void check_same_size(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right);

/** Front-end for both compile-time and run-time binary expression length
 * checking against a fixed-length array.  The first expression must derive
 * from readable_vector, and std::is_array<>::value must be true for the
 * second expression (e.g. double v[3]).
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left Vector expression.
 * @param right Fixed-length array.
 *
 * @throws incompatible_vector_sizes at run-time if Sub1 is a
 * dynamically-sized vector, and sub1.size() != array_size_of(sub2).  If
 * Sub1 is a fixed-size expressions, then the sizes are checked at compile
 * time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void
check_same_size(const readable_vector<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>* = 0);

/** Front-end for run-time binary expression length checking.  The first
 * expression must derive from readable_vector, and the second must
 * implement a size() method for this overload to be enabled.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First vector expression.
 * @param right Second expression.
 *
 * @throws incompatible_vector_sizes if sub1.size() != sub2.size().
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2>
auto check_same_size(const readable_vector<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void());

} // namespace cml

#define __CML_VECTOR_SIZE_CHECKING_TPP
#include <cml/vector/size_checking.tpp>
#undef __CML_VECTOR_SIZE_CHECKING_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
