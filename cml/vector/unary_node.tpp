/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_UNARY_NODE_TPP
#error "vector/unary_node.tpp not included correctly"
#endif

namespace cml {

/* vector_unary_node 'structors: */

template<class Sub, class Op>
vector_unary_node<Sub,Op>::vector_unary_node(Sub sub)
: m_sub(std::move(sub))
{
}

template<class Sub, class Op>
vector_unary_node<Sub,Op>::vector_unary_node(node_type&& other)
: m_sub(std::move(other.m_sub))
{
}



/* Public methods: */

template<class Sub, class Op> int
vector_unary_node<Sub,Op>::size() const
{
  return this->m_sub.size();
}

template<class Sub, class Op> auto
vector_unary_node<Sub,Op>::get(int i) const -> immutable_value
{
  return Op().apply(this->m_sub.get(i));
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
