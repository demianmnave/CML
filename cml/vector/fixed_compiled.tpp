/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_FIXED_COMPILED_TPP
#error "vector/fixed_compiled.tpp not included correctly"
#endif

namespace cml {

/* fixed 'structors: */

template<class E, int S> template<class Sub>
vector<E, fixed<S>>::vector(const readable_vector<Sub>& sub)
{
  this->assign(sub);
}

#if 0
// XXX Should be here, but VC++12 has brain-dead out-of-line template
// argument matching...
template<class E, int S>
template<class E0, class... Es, enable_if_convertible<
  typename scalar_traits<E>::value_type, E0, Es...>::type*
>
vector<E, fixed<S>>::vector(const E0& e0, const Es&... eN)
{
  this->assign_elements(e0, eN...);
}
#endif

template<class E, int S> template<class Array>
vector<E, fixed<S>>::vector(const Array& array, enable_if_array_t<Array>*)
{
  this->assign(array);
}

template<class E, int S> template<class Other>
vector<E, fixed<S>>::vector(std::initializer_list<Other> l)
{
  this->assign(l);
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

template<class E, int S> template<class Other> auto
vector<E, fixed<S>>::set(int i, const Other& v) __CML_REF -> vector_type&
{
  this->m_data[i] = v;
  return *this;
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class E, int S> template<class Other> auto
vector<E, fixed<S>>::set(int i, const Other& v) && -> vector_type&&
{
  this->set(i,v);
  return (vector_type&&) *this;
}
#endif

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

template<class E, int S> auto
vector<E, fixed<S>>::begin() const -> const_pointer
{
  return &this->m_data[0];
}

template<class E, int S> auto
vector<E, fixed<S>>::end() const -> const_pointer
{
  return (&this->m_data[0]) + S;
}

template<class E, int S> auto
vector<E, fixed<S>>::operator=(const vector_type& other)
-> vector_type&
{
  return this->assign(other);
}

template<class E, int S> auto
vector<E, fixed<S>>::operator=(vector_type&& other)
-> vector_type&
{
  for(int i = 0; i < S; ++ i) this->m_data[i] = std::move(other.m_data[i]);
  return *this;
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
