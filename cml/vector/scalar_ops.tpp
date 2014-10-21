/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_SCALAR_OPS_TPP
#error "vector/scalar_ops.tpp not included correctly"
#endif

namespace cml {

template<class Sub, class Scalar> inline auto
operator*(
  const readable_vector<Sub>&	sub,
  const Scalar&			v
  )
-> vector_scalar_node<Sub, Scalar,
  op::binary_multiply<typename Sub::value_type, Scalar>>
{
  return vector_scalar_node<Sub, Scalar, op::binary_multiply<
    typename Sub::value_type, Scalar>>(sub,v);
}

template<class Scalar, class Sub> inline auto
operator*(
  const Scalar&			v,
  const readable_vector<Sub>&	sub
  )
-> vector_scalar_node<Sub, Scalar,
  op::binary_multiply<typename Sub::value_type, Scalar>>
{
  return vector_scalar_node<Sub, Scalar, op::binary_multiply<
    typename Sub::value_type, Scalar>>(sub,v);
}

template<class Sub, class Scalar> inline auto
operator/(
  const readable_vector<Sub>& sub,
  const Scalar&			   v
  )
-> vector_scalar_node<Sub, Scalar,
  op::binary_divide<typename Sub::value_type, Scalar>>
{
  return vector_scalar_node<Sub, Scalar, op::binary_divide<
    typename Sub::value_type, Scalar>>(sub,v);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
