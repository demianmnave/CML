/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_scalar_ops_h
#define	cml_matrix_scalar_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/matrix/scalar_node.h>

namespace cml {

/** Template helper for scalar multiplication. */
template<class Sub, class Scalar> using matrix_scalar_multiply
= op::binary_multiply<typename Sub::value_type, Scalar>;

/** Template helper for scalar division. */
template<class Sub, class Scalar> using matrix_scalar_divide
= op::binary_divide<typename Sub::value_type, Scalar>;

} // namespace cml

/** Macro to create two boilerplate scalar-matrix operator functions
 * taking const& and && arguments. To create the operators for
 * left multiplication:
 *
 * __CML_MAKE_RIGHT_MATRIX_SCALAR_OPERATORS( * , matrix_scalar_multiply)
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
#define __CML_MAKE_RIGHT_MATRIX_SCALAR_OPERATORS(_sym_, _op_type_)	\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  const Scalar& v, const readable_matrix<Sub>& sub			\
  )									\
-> matrix_scalar_node<const Sub&, Scalar, _op_type_ <Sub,Scalar>> 	\
{									\
  return matrix_scalar_node<const Sub&, Scalar,				\
	 _op_type_ <Sub,Scalar>>(sub.actual(), v);			\
}									\
 									\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  const Scalar& v, readable_matrix<Sub>&& sub				\
  )									\
-> matrix_scalar_node<Sub&&, Scalar, _op_type_ <Sub,Scalar>> 		\
{									\
  return matrix_scalar_node<						\
  	Sub&&, Scalar, _op_type_ <Sub,Scalar>>((Sub&&) sub, v);		\
}									\

/** Macro to create two boilerplate matrix-scalar operator functions
 * taking const& and && arguments. To create the operators for
 * right multiplication:
 *
 * __CML_MAKE_LEFT_MATRIX_SCALAR_OPERATORS( * , matrix_scalar_multiply)
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
#define __CML_MAKE_LEFT_MATRIX_SCALAR_OPERATORS(_sym_, _op_type_)	\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  const readable_matrix<Sub>& sub, const Scalar& v 			\
  )									\
-> matrix_scalar_node<const Sub&, Scalar, _op_type_ <Sub,Scalar>> 	\
{									\
  return matrix_scalar_node<const Sub&, Scalar,				\
	 _op_type_ <Sub,Scalar>>(sub.actual(), v);			\
}									\
 									\
template<class Scalar, class Sub> inline auto operator _sym_ (		\
  readable_matrix<Sub>&& sub, const Scalar& v 				\
  )									\
-> matrix_scalar_node<Sub&&, Scalar, _op_type_ <Sub,Scalar>> 		\
{									\
  return matrix_scalar_node<						\
  	Sub&&, Scalar, _op_type_ <Sub,Scalar>>((Sub&&) sub, v);		\
}									\

#define __CML_MATRIX_SCALAR_OPS_TPP
#include <cml/matrix/scalar_ops.tpp>
#undef __CML_MATRIX_SCALAR_OPS_TPP

#undef __CML_MAKE_RIGHT_MATRIX_SCALAR_OPERATORS
#undef __CML_MAKE_LEFT_MATRIX_SCALAR_OPERATORS

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
