/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_FIXED_EXTERNAL_TPP
#error "vector/fixed_external.tpp not included correctly"
#endif

namespace cml {

/* fixed_external 'structors: */

template<class E, int S>
vector<E, external<S>>::vector(pointer data)
: m_data(data)
{
}

template<class E, int S>
vector<E, external<S>>::vector(vector_type&& other)
{
  this->m_data = other.m_data;
  other.m_data = nullptr;
}



/* Public methods: */

template<class E, int S> int
vector<E, external<S>>::size() const
{
  return S;
}

template<class E, int S> auto
vector<E, external<S>>::get(int i) -> mutable_value
{
  return this->m_data[i];
}

template<class E, int S> auto
vector<E, external<S>>::get(int i) const -> immutable_value
{
  return this->m_data[i];
}

template<class E, int S> auto
vector<E, external<S>>::set(int i, immutable_value v) -> vector_type&
{
  this->m_data[i] = v;
  return *this;
}

template<class E, int S> auto
vector<E, external<S>>::data() -> pointer
{
  return this->m_data;
}

template<class E, int S> auto
vector<E, external<S>>::data() const -> const_pointer
{
  return this->m_data;
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
