/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_dynamic_h
#define	cml_matrix_dynamic_h

#include <cml/common/dynamic_selector.h>
#include <cml/common/size_tags.h>
#include <cml/common/scalar_traits.h>
#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/matrix.h>

namespace cml {

template<class Element, class Allocator, typename BasisOrient, typename Layout>
struct matrix_traits< matrix<Element, dynamic<Allocator>, BasisOrient, Layout> >
{
  typedef scalar_traits<Element>			element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::pointer		pointer;
  typedef typename element_traits::reference		reference;
  typedef typename element_traits::const_pointer	const_pointer;
  typedef typename element_traits::const_reference	const_reference;
  typedef typename element_traits::mutable_value	mutable_value;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef dynamic_size_tag				size_tag;
  typedef BasisOrient					basis_tag;
  typedef Layout					layout_tag;
  typedef matrix<Element,
	  dynamic<Allocator>, BasisOrient, Layout>	temporary_type;
};

/** Fixed-size matrix. */
template<class Element, class Allocator, typename BasisOrient, typename Layout>
class matrix<Element, dynamic<Allocator>, BasisOrient, Layout>
: public writable_matrix<
  matrix<Element, dynamic<Allocator>, BasisOrient, Layout>>
{
  // The basis must be col_basis or row_basis (NOT is_basis_tag!):
  static_assert(std::is_same<BasisOrient,row_basis>::value
    || std::is_same<BasisOrient,col_basis>::value, "invalid basis");

  // The layout must be col_major or row_major (NOT is_layout_tag!):
  static_assert(std::is_same<Layout,row_major>::value
    || std::is_same<Layout,col_major>::value, "invalid layout");

  protected:

    /** The real allocator type. */
    typedef typename Allocator::template
      rebind<Element>::other				allocator_type;

    /** Require a stateless allocator. */
    static_assert(std::is_empty<allocator_type>::value,
      "cannot use a stateful allocator for dynamic<> matrices");


  public:

    typedef matrix<Element,
	    dynamic<Allocator>, BasisOrient, Layout>	matrix_type;
    typedef writable_matrix<matrix_type>		writable_type;
    typedef matrix_traits<matrix_type>			traits_type;
    typedef typename traits_type::element_traits	element_traits;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::pointer		pointer;
    typedef typename traits_type::reference		reference;
    typedef typename traits_type::const_pointer		const_pointer;
    typedef typename traits_type::const_reference	const_reference;
    typedef typename traits_type::mutable_value		mutable_value;
    typedef typename traits_type::immutable_value	immutable_value;
    typedef typename traits_type::size_tag		size_tag;
    typedef typename traits_type::basis_tag		basis_tag;
    typedef typename traits_type::layout_tag		layout_tag;
    typedef typename traits_type::temporary_type	temporary_type;


  public:

#ifndef CML_HAS_MSVC_BRAIN_DEAD_ASSIGNMENT_OVERLOADS
    /* Include methods from writable_type: */
    using writable_type::operator=;
#endif


  public:

    /** Constant containing the number of rows. */
    static const int array_rows = -1;

    /** Constant containing the number of columns. */
    static const int array_cols = -1;

    /** Constant containing the matrix basis enumeration value. */
    static const basis_kind matrix_basis = basis_tag::value;

    /** Constant containing the array layout enumeration value. */
    static const layout_kind array_layout = layout_tag::value;


  public:

    /** Default constructor.
     *
     * @note The matrix has no elements.
     */
    matrix();

    /** Construct given a size.
     *
     * @throws std::invalid_argument if  @c ros < 0 or @c cols < 0.
     */
    matrix(int rows, int cols);

    /** Copy constructor. */
    matrix(const matrix_type& other);

    /** Move constructor. */
    matrix(matrix_type&& other);

    /** Construct from a readable_matrix. */
    template<class Sub> matrix(const readable_matrix<Sub>& sub);

    /** Construct from at least 1 value.
     *
     * @note This overload is enabled only if all of the arguments are
     * convertible to value_type.
     */
    template<class E0, class... Elements,
      typename std::enable_if<
	cml::are_convertible_to_scalar<typename matrix_traits<
	  matrix<Element,dynamic<Allocator>,BasisOrient,Layout>>::value_type
	  , E0, Elements...>::value>::type* = nullptr
	>
      matrix(int rows, int cols, const E0& e0, const Elements&... eN);

    /** Construct from an array type. */
    template<class Array> matrix(int rows, int cols,
      const Array& array, cml::enable_if_array_t<Array>* = 0);

    /** Construct from a C-array type. */
    template<class Other, int Rows, int Cols>
      matrix(Other const (&array)[Rows][Cols]);

    /** Destructor. */
    ~matrix();


  public:

    /** Return the number of rows. */
    int rows() const;

    /** Return the number of columns. */
    int cols() const;

    /** Return matrix element @c (i,j). */
    mutable_value get(int i, int j);

    /** Return matrix const element @c (i,j). */
    immutable_value get(int i, int j) const;

    /** Set element @c i. */
    template<class Other> matrix_type&
      set(int i, int j, const Other& v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
    /** Set element @c i on a temporary. */
    template<class Other> matrix_type&& set(int i, int j, const Other& v) &&;
#endif

    /** Return access to the matrix data as a raw pointer. */
    pointer data();

    /** Return const access to the matrix data as a raw pointer. */
    const_pointer data() const;

    /** Read-only iterator over the elements as a 1D array. */
    const_pointer begin() const;

    /** Read-only iterator over the elements as a 1D array. */
    const_pointer end() const;

    /** Resize the matrix to the specified size.
     *
     * @note This will reallocate the array and copy existing elements, if
     * any.
     *
     * @throws std::invalid_argument if @c rows or @c cols is negative.
     */
    void resize(int rows, int cols);

    /** Resize the matrix to the specified size without copying the old
     * elements.
     *
     * @throws std::invalid_argument if @c rows or @c cols is negative.
     */
    void resize_fast(int rows, int cols);


  public:

    /** Copy assignment. */
    matrix_type& operator=(const matrix_type& other);

    /** Move assignment. */
    matrix_type& operator=(matrix_type&& other);

#ifdef CML_HAS_MSVC_BRAIN_DEAD_ASSIGNMENT_OVERLOADS
    template<class Other>
      inline matrix_type& operator=(const readable_matrix<Other>& other) {
	return this->assign(other);
      }

    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
      inline matrix_type& operator=(const Array& array) {
	return this->assign(array);
      }

    template<class Other, int Rows, int Cols>
      inline matrix_type& operator=(Other const (&array)[Rows][Cols]) {
	return this->assign(array);
      }

    template<class Other>
      inline matrix_type& operator=(std::initializer_list<Other> l) {
	return this->assign(l);
      }
#endif


  protected:

    /** No-op for trivially destructible elements
     * (is_trivially_destructible).
     */
    void destruct(pointer, int, std::true_type);

    /** Invoke non-trivial destructors for @c n elements starting at @c
     * data.
     */
    void destruct(pointer data, int n, std::false_type);


  protected:

    /** Dynamic storage. */
    pointer			m_data;

    /** Matrix rows. */
    int				m_rows;

    /** Matrix columns. */
    int				m_cols;
};

} // namespace cml

#define __CML_MATRIX_DYNAMIC_TPP
#include <cml/matrix/dynamic.tpp>
#undef __CML_MATRIX_DYNAMIC_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
