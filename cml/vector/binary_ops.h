/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_binary_ops_h
#define	cml_vector_binary_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/vector/binary_node.h>

namespace cml {

/** Template helper for binary minus. */
template<class Sub1, class Sub2> using binary_minus_type
= op::binary_minus<typename Sub1::value_type, typename Sub2::value_type>;

/** Template helper for binary plus. */
template<class Sub1, class Sub2> using binary_plus_type
= op::binary_plus<typename Sub1::value_type, typename Sub2::value_type>;

/** Macro to create four boilerplate binary vector operator functions
 * taking const& and && arguments. To create the four operators for binary
 * minus:
 *
 * __CML_MAKE_VECTOR_BINARY_OPERATORS( - , binary_minus_type)
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
 */
#define __CML_MAKE_VECTOR_BINARY_OPERATORS(_sym_, _op_type_)		\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  const readable_vector<Sub1>& sub1, const readable_vector<Sub2>& sub2)	\
-> vector_binary_node<const Sub1&, const Sub2&, _op_type_ <Sub1,Sub2>> 	\
{									\
  return vector_binary_node<const Sub1&, const Sub2&,			\
	 _op_type_ <Sub1,Sub2>>(sub1.actual(), sub2.actual());		\
}									\
									\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  const readable_vector<Sub1>& sub1, readable_vector<Sub2>&& sub2)	\
-> vector_binary_node<const Sub1&, Sub2&&, _op_type_ <Sub1, Sub2>>	\
{									\
  return vector_binary_node<const Sub1&, Sub2&&,			\
	 _op_type_<Sub1,Sub2>>(sub1.actual(), (Sub2&&) sub2);		\
}									\
									\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  readable_vector<Sub1>&& sub1, const readable_vector<Sub2>& sub2)	\
-> vector_binary_node<Sub1&&, const Sub2&, _op_type_ <Sub1, Sub2>>	\
{									\
  return vector_binary_node<Sub1&&, const Sub2&,			\
	 _op_type_<Sub1,Sub2>>((Sub1&&) sub1, sub2.actual());		\
}									\
									\
template<class Sub1, class Sub2> inline auto operator _sym_ (		\
  readable_vector<Sub1>&& sub1, readable_vector<Sub2>&& sub2)		\
-> vector_binary_node<Sub1&&, Sub2&&, _op_type_ <Sub1, Sub2>>		\
{									\
  return vector_binary_node<Sub1&&, Sub2&&,				\
	 _op_type_<Sub1,Sub2>>((Sub1&&) sub1, (Sub2&&) sub2);		\
}

} // namespace cml

#define __CML_VECTOR_BINARY_OPS_TPP
#include <cml/vector/binary_ops.tpp>
#undef __CML_VECTOR_BINARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
