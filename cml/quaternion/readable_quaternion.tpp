/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_QUATERNION_READABLE_QUATERNION_TPP
#error "quaternion/readable_quaternion.tpp not included correctly"
#endif

#include <cml/scalar/functions.h>
#include <cml/quaternion/scalar_node.h>
#include <cml/quaternion/imaginary_node.h>
#include <cml/quaternion/conjugate_node.h>

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

template<class DT> auto
readable_quaternion<DT>::length_squared() const -> value_type
{
  value_type accum = cml::sqr(this->get(0));
  for(int i = 1; i < 4; ++ i) accum += cml::sqr(this->get(i));
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

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> auto
readable_quaternion<DT>::conjugate() const & -> conjugate_node<const DT&>
{
  return conjugate_node<const DT&>(this->actual());
}

template<class DT> auto
readable_quaternion<DT>::conjugate() const && -> conjugate_node<DT&&>
{
  return conjugate_node<DT&&>((DT&&) this->actual());
}
#else
template<class DT> auto
readable_quaternion<DT>::conjugate() const -> conjugate_node<DT&&>
{
  return conjugate_node<DT&&>((DT&&) this->actual());
}
#endif

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
template<class DT> auto
readable_quaternion<DT>::inverse() const & -> inverse_node<const DT&>
{
  return inverse_node<const DT&>(this->actual());
}

template<class DT> auto
readable_quaternion<DT>::inverse() const && -> inverse_node<DT&&>
{
  return inverse_node<DT&&>((DT&&) this->actual());
}
#else
template<class DT> auto
readable_quaternion<DT>::inverse() const -> inverse_node<DT&&>
{
  return inverse_node<DT&&>((DT&&) this->actual());
}
#endif

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
