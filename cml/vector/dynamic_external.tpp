/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_DYNAMIC_EXTERNAL_TPP
#error "vector/dynamic_external.tpp not included correctly"
#endif

#include <cml/common/exception.h>

namespace cml {

/* dynamic_external 'structors: */

template<class E>
vector<E, external<>>::vector(pointer data, int size)
: m_data(data)
, m_size(size)
{
  cml_require(size >= 0, std::invalid_argument, "size < 0");
}

template<class E>
vector<E, external<>>::vector(vector_type&& other)
{
  this->m_data = other.m_data;
  other.m_data = nullptr;
  this->m_size = other.m_size;
  other.m_size = 0;
}



/* Public methods: */

template<class E> int
vector<E, external<>>::size() const
{
  return this->m_size;
}

template<class E> auto
vector<E, external<>>::get(int i) -> mutable_value
{
  return this->m_data[i];
}

template<class E> auto
vector<E, external<>>::get(int i) const -> immutable_value
{
  return this->m_data[i];
}

template<class E> template<class Other> auto
vector<E, external<>>::set(int i, const Other& v) -> vector_type&
{
  this->m_data[i] = v;
  return *this;
}

template<class E> auto
vector<E, external<>>::data() -> pointer
{
  return this->m_data;
}

template<class E> auto
vector<E, external<>>::data() const -> const_pointer
{
  return this->m_data;
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
