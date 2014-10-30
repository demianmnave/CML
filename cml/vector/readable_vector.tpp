/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_READABLE_VECTOR_TPP
#error "vector/readable_vector.tpp not included correctly"
#endif

namespace cml {

/* Public methods: */

template<class DT> const DT&
readable_vector<DT>::actual() const
{
  return (const DT&) *this;
}

template<class DT> int
readable_vector<DT>::size() const
{
  return this->actual().size();
}

template<class DT> auto
readable_vector<DT>::get(int i) const -> immutable_value
{
  return this->actual().get(i);
}

template<class DT> auto
readable_vector<DT>::operator[](int i) const -> immutable_value
{
  return this->get(i);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
