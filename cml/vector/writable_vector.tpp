/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_WRITABLE_VECTOR_TPP
#error "vector/writable_vector.tpp not included correctly"
#endif

#include <random>
#include <cml/vector/scalar_ops.h>
#include <cml/vector/unary_ops.h>
#include <cml/vector/binary_ops.h>
#include <cml/vector/detail/check_or_resize.h>

namespace cml {
namespace detail {

/* Terminate the assignment recursion at the final element. */
template<int I, class Sub, class E0> inline void
assign_elements(writable_vector<Sub>& sub, const E0& e0)
{
  sub.set(I,e0);
}

/* Set element I of sub to e0, then assign the remainder of the elements
 * starting from I+1.
 */
template<int I, class Sub, class E0, class... Es> inline void
assign_elements(writable_vector<Sub>& sub, const E0& e0, const Es&... eN)
{
  sub.set(I,e0);
  assign_elements<I+1>(sub, eN...);
}

/* Assign the elements of sub from eN, starting from index 0. */
template<class Sub, class... Es> inline void
assign_elements(writable_vector<Sub>& sub, const Es&... eN)
{
  assign_elements<0>(sub, eN...);
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

template<class DT> template<class Other> DT&
writable_vector<DT>::set(int i, const Other& v) __CML_REF
{
  return this->actual().set(i,v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class Other> DT&&
writable_vector<DT>::set(int i, const Other& v) &&
{
  this->set(i,v);		// Forward to set(...) &
  return (DT&&) *this;
}
#endif

template<class DT> auto
writable_vector<DT>::operator[](int i) -> mutable_value
{
  return this->get(i);
}


template<class DT> DT&
writable_vector<DT>::normalize() __CML_REF
{
  return this->operator/=(this->length());
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_vector<DT>::normalize() &&
{
  this->normalize();		// Forward to normalize &
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_vector<DT>::zero() __CML_REF
{
  for(int i = 0; i < this->size(); ++ i) this->set(i, value_type(0));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_vector<DT>::zero() &&
{
  this->zero();			// Forward to zero &
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_vector<DT>::cardinal(int i) __CML_REF
{
  return this->zero().set(i, value_type(1));
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_vector<DT>::cardinal(int i) &&
{
  this->cardinal(i);		// Forward to cardinal &
  return (DT&&) *this;
}
#endif

template<class DT> template<class ODT> DT&
writable_vector<DT>::minimize(const readable_vector<ODT>& other) __CML_REF
{
  cml::check_same_size(*this, other);
  for(int i = 0; i < this->size(); ++ i) {
    this->set(i, std::min(this->get(i), other.get(i)));
  }
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_vector<DT>::minimize(const readable_vector<ODT>& other) &&
{
  this->minimize(other);		// Forward to minimize &
  return (DT&&) *this;
}
#endif

template<class DT> template<class ODT> DT&
writable_vector<DT>::maximize(const readable_vector<ODT>& other) __CML_REF
{
  cml::check_same_size(*this, other);
  for(int i = 0; i < this->size(); ++ i) {
    this->set(i, std::max(this->get(i), other.get(i)));
  }
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_vector<DT>::maximize(const readable_vector<ODT>& other) &&
{
  this->maximize(other);		// Forward to maximize &
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_vector<DT>::random(
  const_reference low, const_reference high
  ) __CML_REF
{
  typedef if_t<std::is_integral<value_type>::value
    , std::uniform_int_distribution<value_type>
    , std::uniform_real_distribution<value_type>>	distribution_type;

  std::random_device rd;	// Non-deterministic seed, if supported.
  std::default_random_engine gen(rd());
  distribution_type d(low, high);
  for(int i = 0; i < this->size(); ++ i) this->set(i, d(gen));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_vector<DT>::random(const_reference low, const_reference high) &&
{
  this->random(low, high);
  return (DT&&) *this;
}
#endif


template<class DT> template<class ODT> DT&
writable_vector<DT>::operator=(const readable_vector<ODT>& other) __CML_REF
{
  return this->assign(other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_vector<DT>::operator=(const readable_vector<ODT>& other) &&
{
  this->operator=(other);
  return (DT&&) *this;
}
#endif

template<class DT>
template<class Array, enable_if_array_t<Array>*> DT&
writable_vector<DT>::operator=(const Array& array) __CML_REF
{
  return this->assign(array);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT>
template<class Array, enable_if_array_t<Array>*> DT&&
writable_vector<DT>::operator=(const Array& array) &&
{
  this->operator=(array);
  return (DT&&) *this;
}
#endif

template<class DT> template<class Other> DT&
writable_vector<DT>::operator=(std::initializer_list<Other> l) __CML_REF
{
  return this->assign(l);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class Other> DT&&
writable_vector<DT>::operator=(std::initializer_list<Other> l) &&
{
  return this->assign(l);
}
#endif

template<class DT> template<class ODT> DT&
writable_vector<DT>::operator+=(const readable_vector<ODT>& other) __CML_REF
{
  return this->assign(*this + other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_vector<DT>::operator+=(const readable_vector<ODT>& other) &&
{
  this->operator+=(other);
  return (DT&&) *this;
}
#endif

template<class DT> template<class ODT> DT&
writable_vector<DT>::operator-=(const readable_vector<ODT>& other) __CML_REF
{
  return this->assign(*this - other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_vector<DT>::operator-=(const readable_vector<ODT>& other) &&
{
  this->operator-=(other);
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_vector<DT>::operator*=(const_reference v) __CML_REF
{
  return this->assign((*this)*v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_vector<DT>::operator*=(const_reference v) &&
{
  this->operator*=(v);
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_vector<DT>::operator/=(const_reference v) __CML_REF
{
  return this->assign((*this)/v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_vector<DT>::operator/=(const_reference v) &&
{
  this->operator/=(v);
  return (DT&&) *this;
}
#endif



/* Internal methods: */

template<class DT> template<class ODT> DT&
writable_vector<DT>::assign(const readable_vector<ODT>& other)
{
  detail::check_or_resize(*this, other);
  for(int i = 0; i < this->size(); ++ i) this->set(i, other.get(i));
  return this->actual();
}

template<class DT>
template<class Array, enable_if_array_t<Array>*> DT&
writable_vector<DT>::assign(const Array& array)
{
  static const int N = array_size_of_c<Array>::value;
  detail::check_or_resize(*this, N);
  for(int i = 0; i < N; ++ i) this->set(i, array[i]);
  return this->actual();
}

template<class DT> template<class Other> DT&
writable_vector<DT>::assign(const std::initializer_list<Other>& l)
{
  detail::check_or_resize(*this, l);
  int i = 0; for(Other v : l) { this->set(i ++, v); }
  return this->actual();
}

template<class DT> template<class... Es> DT&
writable_vector<DT>::assign_elements(const Es&... eN)
{
  static const int N = int(sizeof...(eN));
  detail::check_or_resize(*this, int_c<N>());
  detail::assign_elements(*this, eN...);
  return this->actual();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
