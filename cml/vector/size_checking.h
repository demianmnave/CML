/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_size_checking_h
#define	cml_vector_size_checking_h

#include <cml/common/mpl/int_c.h>
#include <cml/common/mpl/enable_if_array.h>
#include <cml/common/exception.h>

namespace cml {

/* Forward declarations: */
template<class Sub> class readable_vector;

/** Exception thrown when run-time size checking is enabled, and the
 * operands of a vector expression have incompatible sizes.
 */
struct incompatible_vector_size_error : std::runtime_error {
  incompatible_vector_size_error()
    : std::runtime_error("incompatible vector expression sizes") {}
};

/** Exception thrown when run-time size checking is enabled, and the
 * operand of a vector expression does not meet a minimum size.
 */
struct minimum_vector_size_error : std::runtime_error {
  minimum_vector_size_error()
    : std::runtime_error("vector expression too short") {}
};

/** Exception thrown when run-time size checking is enabled, and the
 * operand of a vector expression does not have the required size.
 */
struct vector_size_error : std::runtime_error {
  vector_size_error()
    : std::runtime_error("incorrect vector expression size") {}
};


/** Front-end for both compile-time and run-time vector binary expression
 * length checking.  Both expressions must derive from readable_vector.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First vector expression.
 * @param right Second vector expression.
 *
 * @throws incompatible_vector_size_error at run-time if either left or
 * right is a dynamically-sized expression, and left.size() !=
 * right.size().  If both are fixed-size expressions, then the sizes are
 * checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void check_same_size(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right);

/** Front-end for both compile-time and run-time vector binary expression
 * length checking against a fixed-length array.  The first expression must
 * derive from readable_vector, and std::is_array<>::value must be true for
 * the second expression (e.g. double v[3]).
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left Vector expression.
 * @param right Fixed-length array.
 *
 * @throws incompatible_vector_size_error at run-time if left is a
 * dynamically-sized expression, and left.size() != array_size_of(right).
 * If left is a fixed-size expression, then the sizes are checked at
 * compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2> void
check_same_size(const readable_vector<Sub1>& left, const Sub2& right,
  cml::enable_if_array_t<Sub2>* = 0);

/** Front-end for run-time vector binary expression length checking.  The
 * first expression must derive from readable_vector, and the second must
 * implement a size() method for this overload to be enabled.
 *
 * @tparam Sub1 the actual type of the first expression.
 * @tparam Sub2 the actual type of the second expression.
 *
 * @param left First vector expression.
 * @param right Second expression.
 *
 * @throws incompatible_vector_size_error if left.size() != right.size().
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub1, class Sub2>
auto check_same_size(const readable_vector<Sub1>& left, const Sub2& right)
-> decltype(right.size(), void());


/** Front-end for minimum vector expression length checking against a
 * run-time size.  The expression must derive from readable_vector.
 *
 * @throws minimum_vector_size_error if left.size() < N.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub>
void check_minimum_size(const readable_vector<Sub>& left, int N);

/** Front-end for compile-time and run-time minimum vector expression
 * length checking against an integer constant via cml::int_c<N>.  The
 * expression must derive from readable_vector.
 *
 * @throws minimum_vector_size_error at run-time if left is a
 * dynamically-sized expression and left.size() < N. If left is a
 * fixed-size expression, then the size is checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub, int N>
void check_minimum_size(const readable_vector<Sub>& left, cml::int_c<N>);


/** Front-end for vector expression length checking against a run-time
 * size.  The expression must derive from readable_vector.
 *
 * @throws vector_size_error if left.size() != N.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub>
void check_size(const readable_vector<Sub>& left, int N);

/** Front-end for compile-time and run-time vector expression length
 * checking against an integer constant via int_c<N>.  The expression must
 * derive from readable_vector.
 *
 * @throws vector_size_error at run-time if left is a dynamically-sized
 * expression and left.size() != N. If left is a fixed-size expression,
 * then the size is checked at compile time.
 *
 * @note Run-time checking can be disabled by defining
 * CML_NO_RUNTIME_VECTOR_SIZE_CHECKS at compile time.
 */
template<class Sub, int N>
void check_size(const readable_vector<Sub>& left, cml::int_c<N>);

} // namespace cml

#define __CML_VECTOR_SIZE_CHECKING_TPP
#include <cml/vector/size_checking.tpp>
#undef __CML_VECTOR_SIZE_CHECKING_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
