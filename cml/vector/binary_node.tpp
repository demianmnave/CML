/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_BINARY_NODE_TPP
#error "vector/binary_node.tpp not included correctly"
#endif

namespace cml {

/* vector_binary_node 'structors: */

template<class Sub1, class Sub2, class Op>
vector_binary_node<Sub1,Sub2,Op>::vector_binary_node(
  const readable_vector<Sub1>& sub1, const readable_vector<Sub2>& sub2
  )
: m_sub1(sub1.actual()), m_sub2(sub2.actual())
{
  // cml::require_same_size(sub1, sub2);
}



/* Public methods: */

template<class Sub1, class Sub2, class Op> int
vector_binary_node<Sub1,Sub2,Op>::size() const
{
  return this->m_sub1.size();
}

template<class Sub1, class Sub2, class Op> auto
vector_binary_node<Sub1,Sub2,Op>::get(int i) const -> immutable_value
{
  return Op().apply(this->m_sub1.get(i), this->m_sub2.get(i));
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
