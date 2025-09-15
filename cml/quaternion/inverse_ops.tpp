/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/


#ifndef __CML_QUATERNION_INVERSE_OPS_TPP
#  error "quaternion/inverse_ops.tpp not included correctly"
#endif

namespace cml {
template<class Sub>
auto
inverse(const readable_quaternion<Sub>& q) -> inverse_node<const Sub&>
{
  return inverse_node<const Sub&>(q.actual());
}

template<class Sub>
auto
inverse(readable_quaternion<Sub>&& q) -> inverse_node<Sub&&>
{
  return inverse_node<Sub&&>((Sub&&) q);
}
} // namespace cml
