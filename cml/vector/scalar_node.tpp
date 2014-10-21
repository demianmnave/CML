/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_SCALAR_NODE_TPP
#error "vector/scalar_node.tpp not included correctly"
#endif

namespace cml {

/* vector_scalar_node 'structors: */

template<class Sub, class Scalar, class Op>
vector_scalar_node<Sub,Scalar,Op>::vector_scalar_node(
  const readable_vector<Sub>& sub, const Scalar& v
  )
: m_sub(sub.actual()), m_v(v)
{
}



/* Public methods: */

template<class Sub, class Scalar, class Op> int
vector_scalar_node<Sub,Scalar,Op>::size() const
{
  return this->m_sub.size();
}

template<class Sub, class Scalar, class Op> auto
vector_scalar_node<Sub,Scalar,Op>::get(int i) const -> immutable_value
{
  return Op().apply(this->m_sub.get(i), this->m_v);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
