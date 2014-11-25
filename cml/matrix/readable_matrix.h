/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_readable_matrix_h
#define	cml_matrix_readable_matrix_h

#include <utility>
#include <cml/matrix/basis_tags.h>
#include <cml/matrix/traits.h>

namespace cml {

/** Return type for readable_matrix<>::size(). */
typedef std::pair<int,int> matrix_size;

/** Base class for readable matrix types.  Readable matrices support const
 * access to its elements.
 *
 * DerivedT must implement:
 *
 * - int rows() const, returning the number of rows (even if static);
 *
 * - int cols() const, returning the number of columns (even if static);
 *
 * - <X> get(int i, int j) const returning matrix element @c (i,j), where
 * <X> is the immutable_value type defined by matrix_traits<DerivedT>.
 * Note that immutable_value is not necessarily a reference or const type.
 *
 * - <X> basis_element(int i, int j) const returning element @c j of basis
 * vector @c i, where <X> is the immutable_value type defined by
 * matrix_traits<DerivedT>.  Note that immutable_value is not necessarily a
 * reference or const type.
 */
template<class DerivedT>
class readable_matrix
{
  public:

    typedef DerivedT					matrix_type;
    typedef matrix_traits<matrix_type>			traits_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;
    typedef typename traits_type::basis_tag		basis_tag;
    typedef typename traits_type::layout_tag		layout_tag;
    typedef typename traits_type::temporary_type	temporary_type;


  public:

    /** Return a const reference to the matrix cast as DerivedT. */
    const DerivedT& actual() const;

    /** Return the number of rows. */
    int rows() const;

    /** Return the number of columns. */
    int cols() const;

    /** Returns the matrix size as a std::pair<>. */
    matrix_size size() const;

    /** Return const element at @c i, @c j. */
    immutable_value get(int i, int j) const;

    /** Return const element at @c i, @c j. */
    immutable_value operator()(int i, int j) const;

    /** Returns element @c j of basis vector @c i.  The returned value
     * depends upon the basis orientation.
     */
    immutable_value basis_element(int i, int j) const;


  protected:

    /** Return basis element @c (i,j) for a row-basis matrix. */
    immutable_value basis_element(int i, int j, row_basis) const;

    /** Return basis element @c (i,j) for a column-basis matrix. */
    immutable_value basis_element(int i, int j, col_basis) const;


  protected:

    // Use the compiler-generated default constructor:
    readable_matrix() = default;

    // Use the compiler-generated copy constructor:
    readable_matrix(const readable_matrix&) = default;

#ifdef CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
    // Use the compiler-generated move constructor:
    readable_matrix(readable_matrix&&) = default;
#endif
};

} // namespace cml

#define __CML_MATRIX_READABLE_MATRIX_TPP
#include <cml/matrix/readable_matrix.tpp>
#undef __CML_MATRIX_READABLE_MATRIX_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
