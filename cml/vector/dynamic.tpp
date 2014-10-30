/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_DYNAMIC_TPP
#error "vector/dynamic.tpp not included correctly"
#endif

#include <cml/common/exception.h>

namespace cml {

/* dynamic 'structors: */

template<class E, class A>
vector<E, dynamic<A>>::vector()
: m_data()
{
}

template<class E, class A>
vector<E, dynamic<A>>::vector(int size)
: m_data()
{
  cml_require(size >= 0, std::invalid_argument, "size < 0");
  this->resize(size);
}

template<class E, class A>
vector<E, dynamic<A>>::vector(const vector_type& other)
{
  this->assign(other);
}

template<class E, class A>
vector<E, dynamic<A>>::vector(vector_type&& other)
: m_data(std::move(other.m_data))
{
}

template<class E, class A> template<class Sub>
vector<E, dynamic<A>>::vector(const readable_vector<Sub>& sub)
{
  this->assign(sub);
}

template<class E, class A> template<class Array>
vector<E, dynamic<A>>::vector(
  const Array& array, cml::enable_if_array_t<Array>*
  )
{
  this->assign(array);
}

template<class E, class A> template<class Other>
vector<E, dynamic<A>>::vector(std::initializer_list<Other> l)
{
  this->assign(l);
}



/* Public methods: */

template<class E, class A> int
vector<E, dynamic<A>>::size() const
{
  return int(this->m_data.size());
}

template<class E, class A> auto
vector<E, dynamic<A>>::get(int i) -> mutable_value
{
  return this->m_data[i];
}

template<class E, class A> auto
vector<E, dynamic<A>>::get(int i) const -> immutable_value
{
  return this->m_data[i];
}

template<class E, class A> auto
vector<E, dynamic<A>>::set(int i, immutable_value v) -> vector_type&
{
  this->m_data[i] = v;
  return *this;
}

template<class E, class A> auto
vector<E, dynamic<A>>::data() -> pointer
{
  return this->m_data.data();
}

template<class E, class A> auto
vector<E, dynamic<A>>::data() const -> const_pointer
{
  return this->m_data.data();
}

template<class E, class A> void
vector<E, dynamic<A>>::resize(int n)
{
  this->m_data.resize(n);
  this->m_data.shrink_to_fit();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
