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
vector<E, external<S>>::vector()
: m_data(0)
{
#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  static_assert(false, "external vector default constructor not supported");
#endif
}

template<class E, int S>
vector<E, external<S>>::vector(pointer data)
: m_data(data)
{
}

template<class E, int S>
vector<E, external<S>>::vector(vector_type&& other)
{
  this->operator=(std::move(other));
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

template<class E, int S> template<class Other> auto
vector<E, external<S>>::set(int i, const Other& v) __CML_REF -> vector_type&
{
  this->m_data[i] = v;
  return *this;
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class E, int S> template<class Other> auto
vector<E, external<S>>::set(int i, const Other& v) && -> vector_type&&
{
  this->set(i,v);
  return (vector_type&&) *this;
}
#endif

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

template<class E, int S> auto
vector<E, external<S>>::begin() const -> const_pointer
{
  return this->m_data;
}

template<class E, int S> auto
vector<E, external<S>>::end() const -> const_pointer
{
  return this->m_data + S;
}


template<class E, int S> auto
vector<E, external<S>>::operator=(const vector_type& other) -> vector_type&
{
  return this->assign(other);
}

template<class E, int S> auto
vector<E, external<S>>::operator=(vector_type&& other) -> vector_type&
{
  this->m_data = other.m_data;
  other.m_data = nullptr;
  return *this;
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
