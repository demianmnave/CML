/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_SUBVECTOR_NODE_TPP
#error "vector/subvector_node.tpp not included correctly"
#endif

namespace cml {

/* subvector_node 'structors: */

template<class Sub>
subvector_node<Sub>::subvector_node(Sub sub, int skip)
: m_sub(std::move(sub)), m_skip(skip)
{
}

template<class Sub>
subvector_node<Sub>::subvector_node(node_type&& other)
: m_sub(std::move(other.m_sub)), m_skip(other.m_skip)
{
}



/* Public methods: */

template<class Sub> int
subvector_node<Sub>::size() const
{
  return this->m_sub.size() - 1;
}

template<class Sub> auto
subvector_node<Sub>::get(int i) const -> immutable_value
{
  return this->m_sub.get((i < this->m_skip) ? i : (i+1));
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
