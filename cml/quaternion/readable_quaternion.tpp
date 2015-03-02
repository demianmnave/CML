/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_QUATERNION_READABLE_QUATERNION_TPP
#error "quaternion/readable_quaternion.tpp not included correctly"
#endif

#include <cml/scalar/functions.h>
#include <cml/scalar/binary_ops.h>
#if 0
#include <cml/vector/size_checking.h>
#include <cml/quaternion/scalar_node.h>
#endif

namespace cml {

/* Public methods: */

template<class DT> const DT&
readable_quaternion<DT>::actual() const
{
  return (const DT&) *this;
}

template<class DT> auto
readable_quaternion<DT>::get(int i) const -> immutable_value
{
  return this->actual().get(i);
}

template<class DT> auto
readable_quaternion<DT>::operator[](int i) const -> immutable_value
{
  return this->get(i);
}

template<class DT> auto
readable_quaternion<DT>::real() const -> immutable_value
{
  return this->get(order_type::W);
}

template<class DT> auto
readable_quaternion<DT>::length_squared() const -> value_type
{
  value_type accum = cml::sqr(this->get(0));
  for(int i = 1; i < this->size(); ++ i) accum += cml::sqr(this->get(i));
  return accum;
}

template<class DT> auto
readable_quaternion<DT>::length() const -> value_type
{
  return element_traits::sqrt(this->length_squared());
}

template<class DT> auto
readable_quaternion<DT>::norm() const -> value_type
{
  return this->length_squared();
}

#if 0
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> auto
readable_quaternion<DT>::imaginary() const & -> imaginary_node<const DT&>
{
  return imaginary_node<const DT&>((const DT&) *this);
}

template<class DT> auto
readable_quaternion<DT>::imaginary() const && -> imaginary_node<DT&&>
{
  return imaginary_node<DT&&>((DT&&) *this);
}
#else
template<class DT> auto
readable_quaternion<DT>::imaginary() const -> imaginary_node<DT&&>
{
  return imaginary_node<DT&&>((DT&&) *this);
}
#endif
#endif

#if 0
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> auto
readable_quaternion<DT>::normalize() const & -> quaternion_scalar_node<
	const DT&, value_type, op::binary_divide<value_type,value_type>>
{
  return quaternion_scalar_node<
    const DT&, value_type, op::binary_divide<value_type,value_type>>
    (this->actual(), this->length());
}

template<class DT> auto
readable_quaternion<DT>::normalize() const && -> quaternion_scalar_node<
	DT&&, value_type, op::binary_divide<value_type,value_type>>
{
  return quaternion_scalar_node<
    DT&&, value_type, op::binary_divide<value_type,value_type>>
    ((DT&&) this->actual(), this->length());
}
#else
template<class DT> auto
readable_quaternion<DT>::normalize() const -> quaternion_scalar_node<
	DT&&, value_type, op::binary_divide<value_type,value_type>>
{
  return quaternion_scalar_node<
    DT&&, value_type, op::binary_divide<value_type,value_type>>
    ((DT&&) this->actual(), this->length());
}
#endif
#endif

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
