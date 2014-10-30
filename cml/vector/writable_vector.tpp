/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_WRITABLE_VECTOR_TPP
#error "vector/writable_vector.tpp not included correctly"
#endif

#include <cml/vector/size_checking.h>
#include <cml/vector/scalar_ops.h>
#include <cml/vector/unary_ops.h>
#include <cml/vector/binary_ops.h>

namespace cml {
namespace detail {

/** check_or_resize for a read-only vector @c left that just forwards to
 * check_same_size.
 */
template<class Sub, class Other> inline void
check_or_resize(const readable_vector<Sub>& left, const Other& right)
{
  cml::check_same_size(left, right);
}

/** check_or_resize for a read-write vector @c left that resizes the vector
 * to ensure it has the same size as @c right.
 */
template<class Sub, class Other> inline auto
check_or_resize(writable_vector<Sub>& left, const Other& right)
-> decltype(left.actual().resize(0), void())
{
  left.actual().resize(cml::array_size_of(right));
}

} // namespace detail



/* Public methods: */

template<class DT> DT&
writable_vector<DT>::actual()
{
  return (DT&) *this;
}

template<class DT> auto
writable_vector<DT>::get(int i) -> mutable_value
{
  return this->actual().get(i);
}

template<class DT> DT&
writable_vector<DT>::set(int i, immutable_value v)
{
  return this->actual().set(i,v);
}

template<class DT> auto
writable_vector<DT>::operator[](int i) -> mutable_value
{
  return this->get(i);
}

template<class DT> template<class ODT> DT&
writable_vector<DT>::operator=(const readable_vector<ODT>& other)
{
  return this->assign(other);
}

template<class DT>
template<class Array, typename cml::enable_if_array_t<Array>*> DT&
writable_vector<DT>::operator=(const Array& array)
{
  return this->assign(array);
}

template<class DT> template<class Other> DT&
writable_vector<DT>::operator=(std::initializer_list<Other> l)
{
  return this->assign(l);
}

template<class DT> template<class ODT> DT&
writable_vector<DT>::operator+=(const readable_vector<ODT>& other)
{
  return (*this = *this + other);
}

template<class DT> template<class ODT> DT&
writable_vector<DT>::operator-=(const readable_vector<ODT>& other)
{
  return (*this = *this - other);
}

template<class DT> DT&
writable_vector<DT>::operator*=(immutable_value v)
{
  return (*this = (*this)*v);
}

template<class DT> DT&
writable_vector<DT>::operator/=(immutable_value v)
{
  return (*this = (*this)/v);
}



/* Internal methods: */

template<class DT> template<class ODT> DT&
writable_vector<DT>::assign(const readable_vector<ODT>& other)
{
  detail::check_or_resize(*this, other);
  for(int i = 0; i < this->size(); ++ i) this->set(i, other.get(i));
  return this->actual();
}

template<class DT>
template<class Array, typename cml::enable_if_array_t<Array>*> DT&
writable_vector<DT>::assign(const Array& array)
{
  detail::check_or_resize(*this, array);
  for(int i = 0; i < cml::array_size_of_c<Array>::value; ++ i) {
    this->set(i, array[i]);
  }
  return this->actual();
}

template<class DT> template<class Other> DT&
writable_vector<DT>::assign(const std::initializer_list<Other>& l)
{
  detail::check_or_resize(*this, l);
  int i = 0; for(Other v : l) { this->set(i ++, v); }
  return this->actual();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
