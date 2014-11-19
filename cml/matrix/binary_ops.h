/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_binary_ops_h
#define	cml_matrix_binary_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/matrix/binary_node.h>

namespace cml {

/** Template helper for binary minus. */
template<class Sub1, class Sub2> using matrix_binary_minus
  = op::binary_minus<typename matrix_traits<Sub1>::value_type,
  typename matrix_traits<Sub2>::value_type>;

/** Template helper for binary plus. */
template<class Sub1, class Sub2> using matrix_binary_plus
  = op::binary_plus<typename matrix_traits<Sub1>::value_type,
  typename matrix_traits<Sub2>::value_type>;

} // namespace cml

/** Macro to create four boilerplate binary matrix operator functions
 * taking const& and && arguments. To create the four operators for binary
 * minus:
 *
 * __CML_MAKE_MATRIX_BINARY_OPERATORS( - , binary_minus_type)
 *
 * This creates:
 *
 * operator-(const&, const&)
 * operator-(const&, &&)
 * operator-(&&, const&)
 * operator-(&&, &&)
 *
 * The && arguments capture temporary nodes in the expression tree, and
 * ensure that they are copied by value into the returned node.  This
 * avoids prematurely destructing temporary nodes before they are used,
 * particulary in statements like "auto xpr = a-b".
 *
 * @throws incompatible_matrix_sizes at run-time if either Sub1 or Sub2 is
 * a dynamically-sized matrix, and sub1.size() != sub2.size().  If both
 * Sub1 and Sub2 are fixed-size expressions, then the sizes are checked at
 * compile time.
 */
#define __CML_MAKE_MATRIX_BINARY_OPERATORS(_sym_, _op_type_)		\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  const readable_matrix<Sub1>& sub1, const readable_matrix<Sub2>& sub2)	\
-> matrix_binary_node<const Sub1&, const Sub2&, _op_type_ <Sub1,Sub2>> 	\
{									\
  return matrix_binary_node<const Sub1&, const Sub2&,			\
	 _op_type_ <Sub1,Sub2>>(sub1.actual(), sub2.actual());		\
}									\
									\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  const readable_matrix<Sub1>& sub1, readable_matrix<Sub2>&& sub2)	\
-> matrix_binary_node<const Sub1&, Sub2&&, _op_type_ <Sub1, Sub2>>	\
{									\
  return matrix_binary_node<const Sub1&, Sub2&&,			\
	 _op_type_<Sub1,Sub2>>(sub1.actual(), (Sub2&&) sub2);		\
}									\
									\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  readable_matrix<Sub1>&& sub1, const readable_matrix<Sub2>& sub2)	\
-> matrix_binary_node<Sub1&&, const Sub2&, _op_type_ <Sub1, Sub2>>	\
{									\
  return matrix_binary_node<Sub1&&, const Sub2&,			\
	 _op_type_<Sub1,Sub2>>((Sub1&&) sub1, sub2.actual());		\
}									\
									\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  readable_matrix<Sub1>&& sub1, readable_matrix<Sub2>&& sub2)		\
-> matrix_binary_node<Sub1&&, Sub2&&, _op_type_ <Sub1, Sub2>>		\
{									\
  return matrix_binary_node<Sub1&&, Sub2&&,				\
	 _op_type_<Sub1,Sub2>>((Sub1&&) sub1, (Sub2&&) sub2);		\
}

#define __CML_MATRIX_BINARY_OPS_TPP
#include <cml/matrix/binary_ops.tpp>
#undef __CML_MATRIX_BINARY_OPS_TPP

#undef __CML_MAKE_MATRIX_BINARY_OPERATORS

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
