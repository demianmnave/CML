/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_scalar_traits_h
#define	cml_common_scalar_traits_h

namespace cml {

/** Specializable class aggregating scalar properties.  The default is
 * valid for basic types (int, float, double, etc.).  If scalar_traits<> is
 * specialized for a particular type T, T must be default constructible and
 * assignable.
 */
template<typename Scalar> struct scalar_traits
{
  typedef Scalar					value_type;
  typedef value_type*					pointer;
  typedef value_type&					reference;
  typedef value_type const*				const_pointer;
  typedef value_type const&				const_reference;
  typedef value_type&					mutable_value;
  typedef value_type const				immutable_value;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
