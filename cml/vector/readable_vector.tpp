/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_READABLE_VECTOR_TPP
#error "vector/readable_vector.tpp not included correctly"
#endif

#include <cmath>
#include <cml/vector/dot.h>
#include <cml/vector/subvector_node.h>

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


template<class DT> auto
readable_vector<DT>::length_squared() const -> value_type
{
  return cml::dot(this->actual(),this->actual());
}

template<class DT> auto
readable_vector<DT>::length() const -> value_type
{
  return element_traits::sqrt(this->length_squared());
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> auto
readable_vector<DT>::subvector(int i) const & -> subvector_node<const DT&>
{
  return std::move(subvector_node<const DT&>((const DT&) *this, i));
}

template<class DT> auto
readable_vector<DT>::subvector(int i) const && -> subvector_node<DT&&>
{
  return std::move(subvector_node<DT&&>((DT&&) *this, i));
}
#else
template<class DT> auto
readable_vector<DT>::subvector(int i) const
-> subvector_node<temporary_type&&>
{
  return std::move(subvector_node<temporary_type&&>(temporary_type(*this), i));
}
#endif

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
