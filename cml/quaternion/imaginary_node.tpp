/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#ifndef __CML_QUATERNION_IMAGINARY_NODE_TPP
#  error "quaternion/imaginary_node.tpp not included correctly"
#endif

#include <cml/quaternion/order_tags.h>

namespace cml {

/* imaginary_node 'structors: */

template<class Sub>
imaginary_node<Sub>::imaginary_node(Sub sub)
: m_sub(std::move(sub))
{}

template<class Sub>
imaginary_node<Sub>::imaginary_node(node_type&& other)
: m_sub(std::move(other.m_sub))
{}

template<class Sub>
imaginary_node<Sub>::imaginary_node(const node_type& other)
: m_sub(other.m_sub)
{}

/* Internal methods: */

/* readable_vector interface: */

template<class Sub>
int
imaginary_node<Sub>::i_size() const
{
  return 3;
}

template<class Sub>
auto
imaginary_node<Sub>::i_get(int i) const -> immutable_value
{
  using order_type = order_type_trait_of_t<sub_type>;
  return this->m_sub.get(order_type::X + i);
  /* Note: X is either 0 (imaginary_first) or 1 (real_first). */
}

}  // namespace cml
