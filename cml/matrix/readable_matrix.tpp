/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_MATRIX_READABLE_MATRIX_TPP
#error "matrix/readable_matrix.tpp not included correctly"
#endif

namespace cml {

/* Public methods: */

template<class DT> const DT&
readable_matrix<DT>::actual() const
{
  return (const DT&) *this;
}

template<class DT> int
readable_matrix<DT>::rows() const
{
  return this->actual().rows();
}

template<class DT> int
readable_matrix<DT>::cols() const
{
  return this->actual().cols();
}

template<class DT> std::pair<int,int>
readable_matrix<DT>::size() const
{
  return std::make_pair(this->rows(), this->cols());
}

template<class DT> auto
readable_matrix<DT>::get(int i, int j) const -> immutable_value
{
  return this->actual().get(i,j);
}

template<class DT> auto
readable_matrix<DT>::operator()(int i, int j) const -> immutable_value
{
  return this->get(i,j);
}

template<class DT> auto
readable_matrix<DT>::basis_element(int i, int j) const -> immutable_value
{
  return this->basis_element(i,j, basis_tag());
}



/* Internal methods: */

template<class DT> auto
readable_matrix<DT>::basis_element(int i, int j, row_basis) const
-> immutable_value
{
  return this->get(i,j);
}

template<class DT> auto
readable_matrix<DT>::basis_element(int i, int j, col_basis) const
-> immutable_value
{
  return this->get(j,i);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
