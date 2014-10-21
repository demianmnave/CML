/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_writable_vector_h
#define	cml_vector_writable_vector_h

#include <initializer_list>
#include <cml/vector/readable_vector.h>

namespace cml {

/** Mixin class for writable vector types.  Writable vectors support
 * non-const read-write access to its elements.
 *
 * DerivedT must implement <X> get(int i) const, and set(int i, <X>), where
 * <X> is the mutable_value type defined by vector_traits<DerivedT>.  Note
 * that mutable_value is not necessarily a reference type.
 */
template<class DerivedT>
class writable_vector
: public readable_vector<DerivedT>
{
  public:

    DerivedT& actual() { return (DerivedT&) *this; }


  public:

    typedef DerivedT					vector_type;
    typedef readable_vector<vector_type>		readable_type;
    typedef vector_traits<vector_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::mutable_value		mutable_value;


  public:

    /* Disambiguate operator[]: */
    using readable_type::operator[];


  public:

    /** Conversion to mutable DerivedT. */
    operator DerivedT& ();

    /** Return a mutable reference to element @c i. */
    mutable_value operator[](int i);

    template<class Other>
      DerivedT& operator=(std::initializer_list<Other> l);
};

} // namespace cml

#define __CML_VECTOR_WRITABLE_VECTOR_TPP
#include <cml/vector/writable_vector.tpp>
#undef __CML_VECTOR_WRITABLE_VECTOR_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
