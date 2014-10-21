/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_FIXED_TPP
#error "vector/fixed.tpp not included correctly"
#endif

namespace cml {

/* fixed 'structors: */

template<class E, int S>
vector<E, fixed<S>>::vector()
{
}

template<class E, int S>
vector<E, fixed<S>>::vector(const value_type data[S])
{
  for(int i = 0; i < S; ++ i) this->m_data[i] = data[i];
}

template<class E, int S> template<class Other>
vector<E, fixed<S>>::vector(std::initializer_list<Other> l)
{
  // cml::require_same_size(self, l);
  int i = 0; for(Other v : l) { this->m_data[i++] = v; }
}



/* Public methods: */

template<class E, int S> int
vector<E, fixed<S>>::size() const
{
  return S;
}

template<class E, int S> auto
vector<E, fixed<S>>::get(int i) -> mutable_value
{
  return this->m_data[i];
}

template<class E, int S> auto
vector<E, fixed<S>>::get(int i) const -> immutable_value
{
  return this->m_data[i];
}

template<class E, int S> auto
vector<E, fixed<S>>::set(int i, mutable_value v) -> vector_type&
{
  this->m_data[i] = v;
  return *this;
}

template<class E, int S> auto
vector<E, fixed<S>>::data() -> pointer
{
  return &this->m_data[0];
}

template<class E, int S> auto
vector<E, fixed<S>>::data() const -> const_pointer
{
  return &this->m_data[0];
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
