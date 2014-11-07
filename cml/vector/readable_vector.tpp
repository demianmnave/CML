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
  return std::sqrt(this->length_squared());
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
