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

template<class SN, class Op>
vector_unary_node<SN,Op>::vector_unary_node(const readable_vector<SN>& sub)
: m_sub(sub.actual())
{
}



/* Public methods: */

template<class SN, class Op> int
vector_unary_node<SN,Op>::size() const
{
  return this->m_sub.size();
}

template<class SN, class Op> auto
vector_unary_node<SN,Op>::get(int i) const -> immutable_value
{
  return Op().apply(this->m_sub.get(i));
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
