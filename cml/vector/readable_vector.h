/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_readable_vector_h
#define	cml_vector_readable_vector_h

#include <cml/vector/vector.h>
#include <cml/vector/traits.h>

namespace cml {

/** Base class for readable vector types.  Readable vectors support const
 * access to its elements.
 *
 * DerivedT must implement:
 *
 * - int size() const, returning the number of vector elements (even if
 * static); and
 *
 * - <X> get(int i) const, where <X> is the immutable_value type defined by
 * vector_traits<DerivedT>.  Note that immutable_value is not necessarily a
 * reference or const type.
 */
template<class DerivedT>
class readable_vector
{
  public:

    typedef DerivedT					vector_type;
    typedef vector_traits<vector_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    /** Return a const reference to the vector cast as DerivedT. */
    const DerivedT& actual() const;

    /** Return the number of vector elements. */
    int size() const;

    /** Return const element @c i. */
    immutable_value get(int i) const;

    /** Return const element @c i. */
    immutable_value operator[](int i) const;
};

} // namespace cml

#define __CML_VECTOR_READABLE_VECTOR_TPP
#include <cml/vector/readable_vector.tpp>
#undef __CML_VECTOR_READABLE_VECTOR_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
