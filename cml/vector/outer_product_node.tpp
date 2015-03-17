/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_OUTER_PRODUCT_NODE_TPP
#error "vector/outer_product_node.tpp not included correctly"
#endif

namespace cml {

/* outer_product_node 'structors: */

template<class Sub1, class Sub2>
outer_product_node<Sub1,Sub2>::outer_product_node(Sub1 left, Sub2 right)
: m_left(std::move(left)), m_right(std::move(right))
{
}

template<class Sub1, class Sub2>
outer_product_node<Sub1,Sub2>::outer_product_node(node_type&& other)
: m_left(std::move(other.m_left)), m_right(std::move(other.m_right))
{
}



/* Internal methods: */

/* readable_matrix interface: */

template<class Sub1, class Sub2> int
outer_product_node<Sub1,Sub2>::i_rows() const
{
  return this->m_left.size();
}

template<class Sub1, class Sub2> int
outer_product_node<Sub1,Sub2>::i_cols() const
{
  return this->m_right.size();
}

template<class Sub1, class Sub2> auto
outer_product_node<Sub1,Sub2>::i_get(int i, int j) const -> immutable_value
{
  return this->m_left.get(i)*this->m_right.get(j);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
