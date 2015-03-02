/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_QUATERNION_WRITABLE_QUATERNION_TPP
#error "quaternion/writable_quaternion.tpp not included correctly"
#endif

#include <cml/vector/readable_vector.h>
#include <cml/quaternion/size_checking.h>
#if 0
#include <random>
#include <cml/scalar/binary_ops.h>
#include <cml/quaternion/detail/check_or_resize.h>
#endif

namespace cml {

/* Public methods: */

template<class DT> DT&
writable_quaternion<DT>::actual()
{
  return (DT&) *this;
}

template<class DT> auto
writable_quaternion<DT>::get(int i) -> mutable_value
{
  return this->actual().get(i);
}

template<class DT> template<class Other> DT&
writable_quaternion<DT>::set(int i, const Other& v) __CML_REF
{
  return this->actual().set(i,v);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class Other> DT&&
writable_quaternion<DT>::set(int i, const Other& v) &&
{
  this->set(i,v);		// Forward to set(...) &
  return (DT&&) *this;
}
#endif

template<class DT> auto
writable_quaternion<DT>::operator[](int i) -> mutable_value
{
  return this->get(i);
}


template<class DT> DT&
writable_quaternion<DT>::normalize() __CML_REF
{
  return this->operator/=(this->length());
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_quaternion<DT>::normalize() &&
{
  this->normalize();		// Forward to normalize &
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_quaternion<DT>::zero() __CML_REF
{
  for(int i = 0; i < this->size(); ++ i) this->set(i, value_type(0));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_quaternion<DT>::zero() &&
{
  this->zero();			// Forward to zero &
  return (DT&&) *this;
}
#endif

template<class DT> DT&
writable_quaternion<DT>::identity() __CML_REF
{
  return this->zero().set(W, value_type(1));
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_quaternion<DT>::identity() &&
{
  this->identity();		// Forward to identity &
  return (DT&&) *this;
}
#endif

#if 0
template<class DT> DT&
writable_quaternion<DT>::random(
  const_reference low, const_reference high
  ) __CML_REF
{
  typedef if_t<std::is_integral<value_type>::value
    , std::uniform_int_distribution<value_type>
    , std::uniform_real_distribution<value_type>>	distribution_type;

  std::default_random_engine gen(std::rand());
  distribution_type d(low, high);
  for(int i = 0; i < this->size(); ++ i) this->set(i, d(gen));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> DT&&
writable_quaternion<DT>::random(const_reference low, const_reference high) &&
{
  this->random(low, high);
  return (DT&&) *this;
}
#endif
#endif


template<class DT> template<class ODT> DT&
writable_quaternion<DT>::operator=(
  const readable_quaternion<ODT>& other
  ) __CML_REF
{
  return this->assign(other);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_quaternion<DT>::operator=(const readable_quaternion<ODT>& other) &&
{
  this->operator=(other);
  return (DT&&) *this;
}
#endif

template<class DT>
template<class Array, enable_if_array_t<Array>*> DT&
writable_quaternion<DT>::operator=(const Array& array) __CML_REF
{
  return this->assign(array);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT>
template<class Array, enable_if_array_t<Array>*> DT&&
writable_quaternion<DT>::operator=(const Array& array) &&
{
  this->operator=(array);
  return (DT&&) *this;
}
#endif

template<class DT> template<class Other> DT&
writable_quaternion<DT>::operator=(std::initializer_list<Other> l) __CML_REF
{
  return this->assign(l);
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class Other> DT&&
writable_quaternion<DT>::operator=(std::initializer_list<Other> l) &&
{
  return this->assign(l);
}
#endif

template<class DT> template<class ODT> DT&
writable_quaternion<DT>::operator+=(
  const readable_quaternion<ODT>& other
  ) __CML_REF
{
  typedef binary_plus_t<DT, ODT> op_type;
  for(int i = 0; i < 4; ++ i)
    this->set(i, op_type().apply(this->get(i), other.get(i)));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_quaternion<DT>::operator+=(const readable_quaternion<ODT>& other) &&
{
  this->operator+=(other);
  return (DT&&) *this;
}
#endif

template<class DT> template<class ODT> DT&
writable_quaternion<DT>::operator-=(
  const readable_quaternion<ODT>& other
  ) __CML_REF
{
  typedef binary_minus_t<DT, ODT> op_type;
  for(int i = 0; i < 4; ++ i)
    this->set(i, op_type().apply(this->get(i), other.get(i)));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> template<class ODT> DT&&
writable_quaternion<DT>::operator-=(const readable_quaternion<ODT>& other) &&
{
  this->operator-=(other);
  return (DT&&) *this;
}
#endif

template<class DT>
template<class ScalarT, typename enable_if_convertible<
    typename quaternion_traits<DT>::value_type, ScalarT>::type*>
DT&
writable_quaternion<DT>::operator*=(const ScalarT& v) __CML_REF
{
  typedef binary_multiply_t<DT, ScalarT> op_type;
  for(int i = 0; i < 4; ++ i)
    this->set(i, op_type().apply(this->get(i), v));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT>
template<class ScalarT, typename enable_if_convertible<
    typename quaternion_traits<DT>::value_type, ScalarT>::type*>
DT&&
writable_quaternion<DT>::operator*=(const ScalarT& v) &&
{
  this->operator*=(v);
  return (DT&&) *this;
}
#endif

template<class DT>
template<class ScalarT, typename enable_if_convertible<
    typename quaternion_traits<DT>::value_type, ScalarT>::type*>
DT&
writable_quaternion<DT>::operator/=(const ScalarT& v) __CML_REF
{
  typedef binary_divide_t<DT, ScalarT> op_type;
  for(int i = 0; i < 4; ++ i)
    this->set(i, op_type().apply(this->get(i), v));
  return this->actual();
}

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT>
template<class ScalarT, typename enable_if_convertible<
    typename quaternion_traits<DT>::value_type, ScalarT>::type*>
DT&&
writable_quaternion<DT>::operator/=(const ScalarT& v) &&
{
  this->operator/=(v);
  return (DT&&) *this;
}
#endif



/* Internal methods: */

template<class DT> template<class ODT> DT&
writable_quaternion<DT>::assign(const readable_quaternion<ODT>& other)
{
  this->set(W, other.get(W));
  this->set(X, other.get(X));
  this->set(Y, other.get(Y));
  this->set(Z, other.get(Z));
  return this->actual();
}

template<class DT> template<class ODT, class E0> DT&
writable_quaternion<DT>::assign(
  const readable_vector<ODT>& other, const E0& e0
  )
{
  cml::check_size(other, cml::int_c<3>());
  this->set(W, e0);
  this->set(X, other.get(0));
  this->set(Y, other.get(1));
  this->set(Z, other.get(2));
  return this->actual();
}

template<class DT>
template<class Array, enable_if_array_t<Array>*> DT&
writable_quaternion<DT>::assign(const Array& array)
{
  static const int N = array_size_of_c<Array>::value;
  static_assert(N == 4, "incorrect quaternion expression size");
  this->set(W, array[W]);
  this->set(X, array[X]);
  this->set(Y, array[Y]);
  this->set(Z, array[Z]);
  return this->actual();
}

template<class DT>
template<class Pointer, enable_if_pointer_t<Pointer>*> DT&
writable_quaternion<DT>::assign(const Pointer& array)
{
  this->set(W, array[W]);
  this->set(X, array[X]);
  this->set(Y, array[Y]);
  this->set(Z, array[Z]);
  return this->actual();
}

template<class DT>
template<class Array, class E0, enable_if_array_t<Array>*> DT&
writable_quaternion<DT>::assign(const Array& array, const E0& e0)
{
  static const int N = array_size_of_c<Array>::value;
  static_assert(N == 3, "incorrect quaternion expression size");
  this->set(W, e0);
  this->set(X, array[0]);
  this->set(Y, array[1]);
  this->set(Z, array[2]);
  return this->actual();
}

template<class DT> template<class Other> DT&
writable_quaternion<DT>::assign(const std::initializer_list<Other>& l)
{
#ifndef CML_NO_RUNTIME_QUATERNION_SIZE_CHECKS
  cml_require(l.size() == 4, quaternion_size_error, /**/);
#endif
  auto array = l.begin();
  this->set(W, array[W]);
  this->set(X, array[X]);
  this->set(Y, array[Y]);
  this->set(Z, array[Z]);
  return this->actual();
}

namespace {

template<int N, class... Args> inline auto item_at(Args&&... args)
-> decltype(std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...)))
{
  return std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...));
}

}

template<class DT>
template<class E0, class E1, class E2, class E3> DT&
writable_quaternion<DT>::assign_elements(
  const E0& e0, const E1& e1, const E2& e2, const E3& e3
  )
{
  this->set(W, item_at<W>(e0, e1, e2, e3));
  this->set(X, item_at<X>(e0, e1, e2, e3));
  this->set(Y, item_at<Y>(e0, e1, e2, e3));
  this->set(Z, item_at<Z>(e0, e1, e2, e3));
  return this->actual();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
