/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_scalar_ops_h
#define	cml_vector_scalar_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/vector/scalar_node.h>

namespace cml {

/** Template helper for scalar multiplication. */
template<class Sub, class Scalar> using scalar_multiply_type
= op::binary_multiply<typename Sub::value_type, Scalar>;

/** Template helper for scalar division. */
template<class Sub, class Scalar> using scalar_divide_type
= op::binary_divide<typename Sub::value_type, Scalar>;

} // namespace cml

/** Macro to create two boilerplate scalar-vector operator functions
 * taking const& and && arguments. To create the operators for
 * left multiplication:
 *
 * __CML_MAKE_RIGHT_VECTOR_SCALAR_OPERATORS( * , scalar_multiply_type)
 *
 * This creates:
 *
 * operator*(const&, const&)
 * operator*(const&, &&)
 *
 * The && arguments capture temporary nodes in the expression tree, and
 * ensure that they are copied by value into the returned node.  This
 * avoids prematurely destructing temporary nodes before they are used,
 * particulary in statements like "auto xpr = 2.*(a+b)".
 */
#define __CML_MAKE_RIGHT_VECTOR_SCALAR_OPERATORS(_sym_, _op_type_)	\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  const Scalar& v, const readable_vector<Sub>& sub			\
  )									\
-> vector_scalar_node<const Sub&, Scalar, _op_type_ <Sub,Scalar>> 	\
{									\
  return vector_scalar_node<const Sub&, Scalar,				\
	 _op_type_ <Sub,Scalar>>(sub.actual(), v);			\
}									\
 									\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  const Scalar& v, readable_vector<Sub>&& sub				\
  )									\
-> vector_scalar_node<Sub&&, Scalar, _op_type_ <Sub,Scalar>> 		\
{									\
  return vector_scalar_node<						\
  	Sub&&, Scalar, _op_type_ <Sub,Scalar>>((Sub&&) sub, v);		\
}									\

/** Macro to create two boilerplate vector-scalar operator functions
 * taking const& and && arguments. To create the operators for
 * right multiplication:
 *
 * __CML_MAKE_LEFT_VECTOR_SCALAR_OPERATORS( * , scalar_multiply_type)
 *
 * This creates:
 *
 * operator*(const&, const&)
 * operator*(&&, const&)
 *
 * The && arguments capture temporary nodes in the expression tree, and
 * ensure that they are copied by value into the returned node.  This
 * avoids prematurely destructing temporary nodes before they are used,
 * particulary in statements like "auto xpr = (a+b)*2.".
 */
#define __CML_MAKE_LEFT_VECTOR_SCALAR_OPERATORS(_sym_, _op_type_)	\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  const readable_vector<Sub>& sub, const Scalar& v 			\
  )									\
-> vector_scalar_node<const Sub&, Scalar, _op_type_ <Sub,Scalar>> 	\
{									\
  return vector_scalar_node<const Sub&, Scalar,				\
	 _op_type_ <Sub,Scalar>>(sub.actual(), v);			\
}									\
 									\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  readable_vector<Sub>&& sub, const Scalar& v 				\
  )									\
-> vector_scalar_node<Sub&&, Scalar, _op_type_ <Sub,Scalar>> 		\
{									\
  return vector_scalar_node<						\
  	Sub&&, Scalar, _op_type_ <Sub,Scalar>>((Sub&&) sub, v);		\
}									\

#define __CML_VECTOR_SCALAR_OPS_TPP
#include <cml/vector/scalar_ops.tpp>
#undef __CML_VECTOR_SCALAR_OPS_TPP

#undef __CML_MAKE_RIGHT_VECTOR_SCALAR_OPERATORS
#undef __CML_MAKE_LEFT_VECTOR_SCALAR_OPERATORS

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
