/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_TRANSPOSE_NODE_TPP
#error "matrix/transpose_node.tpp not included correctly"
#endif

namespace cml {

/* matrix_transpose_node 'structors: */

template<class Sub>
matrix_transpose_node<Sub>::matrix_transpose_node(Sub sub)
: m_sub(std::move(sub))
{
}

template<class Sub>
matrix_transpose_node<Sub>::matrix_transpose_node(node_type&& other)
: m_sub(std::move(other.m_sub))
{
}



/* Public methods: */

template<class Sub> int
matrix_transpose_node<Sub>::rows() const
{
  return this->m_sub.cols();
}

template<class Sub> int
matrix_transpose_node<Sub>::cols() const
{
  return this->m_sub.rows();
}

template<class Sub> auto
matrix_transpose_node<Sub>::get(int i, int j) const -> immutable_value
{
  return this->m_sub.get(j,i);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
