/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_fixed_h
#define	cml_matrix_fixed_h

#include <cml/common/mpl/are_convertible.h>
#include <cml/common/fixed_selector.h>
#include <cml/common/size_tags.h>
#include <cml/common/scalar_traits.h>
#include <cml/matrix/writable_matrix.h>
#include <cml/matrix/matrix.h>

namespace cml {

template<class Element,
  int Rows, int Cols, typename BasisOrient, typename Layout>
struct matrix_traits< matrix<Element, fixed<Rows,Cols>, BasisOrient, Layout> >
{
  typedef scalar_traits<Element>			element_traits;
  typedef typename element_traits::value_type		value_type;
  typedef typename element_traits::pointer		pointer;
  typedef typename element_traits::reference		reference;
  typedef typename element_traits::const_pointer	const_pointer;
  typedef typename element_traits::const_reference	const_reference;
  typedef typename element_traits::mutable_value	mutable_value;
  typedef typename element_traits::immutable_value	immutable_value;
  typedef fixed_size_tag				size_tag;
  typedef BasisOrient					basis_tag;
  typedef Layout					layout_tag;
  typedef matrix<Element,
	  fixed<Rows,Cols>, BasisOrient, Layout>	temporary_type;
};

/** Fixed-size matrix. */
template<class Element,
  int Rows, int Cols, typename BasisOrient, typename Layout>
class matrix<Element, fixed<Rows,Cols>, BasisOrient, Layout>
: public writable_matrix<
  matrix<Element, fixed<Rows,Cols>, BasisOrient, Layout>>
{
  static_assert(Rows >= 1 && Cols >= 1, "invalid matrix dimensions");

  // The basis must be col_basis or row_basis (NOT is_basis_tag!):
  static_assert(std::is_same<BasisOrient,row_basis>::value
    || std::is_same<BasisOrient,col_basis>::value, "invalid basis");

  // The layout must be col_major or row_major (NOT is_layout_tag!):
  static_assert(std::is_same<Layout,row_major>::value
    || std::is_same<Layout,col_major>::value, "invalid layout");

  public:

    typedef matrix<Element,
	    fixed<Rows,Cols>, BasisOrient, Layout>	matrix_type;
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
    static const int array_rows = Rows;

    /** Constant containing the number of columns. */
    static const int array_cols = Cols;

    /** Constant containing the matrix basis enumeration value. */
    static const basis_kind matrix_basis = basis_tag::value;

    /** Constant containing the array layout enumeration value. */
    static const layout_kind array_layout = layout_tag::value;


  public:

    /** Compiler-default constructor.
     *
     * @note The matrix elements are uninitialized.
     */
    matrix() = default;

    /** Compiler-default destructor. */
    ~matrix() = default;

    /** Compiler-default copy constructor. */
    matrix(const matrix_type& other) = default;

#ifdef CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
    /** Compiler-default move constructor. */
    matrix(matrix_type&& other) = default;
#endif

    /** Construct from a readable_matrix. */
    template<class Sub> matrix(const readable_matrix<Sub>& sub);

    /** Construct from at least 1 value.
     *
     * @note This overload is enabled only if all of the arguments are
     * convertible to value_type.
     */
    template<class E0, class... Elements,
      typename std::enable_if<
	cml::are_convertible<
	typename matrix_traits<
	  matrix<Element,fixed<Rows,Cols>,BasisOrient,Layout>>::value_type
	  , E0, Elements...>::value>::type* = nullptr
	>
      matrix(const E0& e0, const Elements&... eN);

    /** Construct from an array type. */
    template<class Array> matrix(
      const Array& array, cml::enable_if_array_t<Array>* = 0);

    /** Construct from a C-array type. */
    template<class Other, int Rows2, int Cols2>
      matrix(Other const (&array)[Rows2][Cols2]);

    /** Construct from std::initializer_list. */
    template<class Other> matrix(std::initializer_list<Other> l);


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

    /** The matrix data type, depending upon the layout. */
    typedef if_t<array_layout == row_major_c
      , value_type[Rows][Cols]
      , value_type[Cols][Rows]>				matrix_data_type;

    /** Fixed-size array, based on the layout. */
    matrix_data_type		m_data;
};

} // namespace cml

#define __CML_MATRIX_FIXED_TPP
#include <cml/matrix/fixed.tpp>
#undef __CML_MATRIX_FIXED_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
