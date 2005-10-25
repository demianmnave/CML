/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef fixed_2D_h
#define fixed_2D_h

#include <cml/common.h>

namespace cml {
namespace detail {

/* Forward declare the fixed_array_impl signature: */
template<typename E, int Rows, int Cols, typename O> struct fixed_array_impl;

/** Row-major fixed array. */
template<typename E, int Rows, int Cols>
struct fixed_array_impl<E,Rows,Cols,row_major>
{
    /** Linear access to C array data. */
    E& operator()(size_t i) {
        return ((E*)m_data)[i];
    }

    /** Const linear access to C array data. */
    const E& operator()(size_t i) const {
        return ((E*)m_data)[i];
    }

    /** Access element at (i,j). */
    E& operator()(size_t row, size_t col) {
        return m_data[row][col];
    }

    /** Const access element at (i,j). */
    const E& operator()(size_t row, size_t col) const {
        return m_data[row][col];
    }

    /* XXX Can use a union here with Element m_linear[Rows*Cols] */
    E m_data[Rows][Cols];
};

/** Col-major fixed array. */
template<typename E, int Rows, int Cols>
struct fixed_array_impl<E,Rows,Cols,col_major>
{
    /** Linear access to C array data. */
    E& operator()(size_t i) {
        return ((E*)m_data)[i];
    }

    /** Const linear access to C array data. */
    const E& operator()(size_t i) const {
        return ((E*)m_data)[i];
    }

    /** Access element at (i,j). */
    E& operator()(size_t row, size_t col) {
        return m_data[col][row];
    }

    /** Const access element at (i,j). */
    const E& operator()(size_t row, size_t col) const {
        return m_data[col][row];
    }

    /* XXX Can use a union here with E m_linear[Rows*Cols] */
    E m_data[Cols][Rows];
};

} // namespace detail


/** The internal statically-allocated 2D-array implementation class.
 *
 * This uses an internal class to setup the data matrix with the proper
 * orientation.  The alternative is to use a 1D array with size Rows*Cols and
 * a multiplication to dereference an element, but it seems that compilers
 * better optimize 2D array dereferences.  This is different from
 * dynamic_2D<>, which must use the 1D array method.
 *
 * @sa cml::core::fixed
 *
 * @note This class is designed to have the same size as a C array with the
 * same dimensions.  It's therefore possible (but not recommended!) to coerce
 * a normal C array into a fixed_2D<> like this:
 *
 * typedef fixed_2D<double,10,10,row_major> array;
 * double c_array[10][10];
 * array& array_object = *((array*)&c_array);
 * double e11 = array_object[1][1];
 *
 * It's also possible to do this with a pointer to an array of values (e.g. a
 * double*), whether or not it was actually declared as a fixed C array.  This
 * is HIGHLY DISCOURAGED, though, since it's relatively straightforward to
 * implement a separate class to take a C array (or pointer) and turn it into
 * an array object.
 *
 * @todo Implement external_fixed_2D<> to wrap up externally-defined
 * fixed-size arrays into a C++ object.
 *
 * @internal Do <em>not</em> add the empty constructor and destructor; at
 * least one compiler (Intel C++ 9.0) fails to optimize them away, and they
 * aren't needed anyway here.
 */
template<typename Element, int Rows, int Cols, typename Orient>
class fixed_2D
{
  public:

    /* Standard: */
    typedef Element             value_type;
    typedef Element&            reference;
    typedef const Element&      const_reference;

    /* Use fixed_array_impl to get the array type by orientation: */
    typedef detail::fixed_array_impl<Element,Rows,Cols,Orient> array_impl;

    /* For matching by memory layout: */
    typedef Orient              orientation;

    /* For matching by memory type: */
    typedef fixed_memory_tag    memory_tag;

    /* For matching by size type: */
    typedef fixed_size_tag      size_tag;


  public:

    enum { array_rows = Rows, array_cols = Cols };


  public:

    /** Return the total number of elements in the array. */
    size_t size() const { return this->rows()*this->cols(); }

    /** Return the number of rows in the array. */
    size_t rows() const { return size_t(array_rows); }

    /** Return the number of cols in the array. */
    size_t cols() const { return size_t(array_cols); }


  public:

    /** Linear access to the given element of the matrix.
     *
     * @param i position (in memory) of element to access.
     * @returns mutable reference.
     *
     * @warning This returns the i'th element from the start of the data,
     * not the i'th logical element from M(0,0) (i.e. M(i/Rows,i%Rows)).
     *
     * @note This function does not range-check the argument.
     */
    reference operator()(size_t i) { return m_data(i); }

    /** Linear access to the given element of the matrix.
     *
     * @param i position (in memory) of element to access.
     * @returns const reference to element i of the matrix.
     *
     * @warning This returns the i'th element from the start of the data,
     * not the i'th logical element from M(0,0) (i.e. M(i/Rows,i%Rows)).
     *
     * @note This function does not range-check the argument.
     */
    const_reference operator()(size_t i) const { return m_data(i); }

    /** Access element (row,col) of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns mutable reference.
     *
     * @note This function does not range-check the arguments.
     */
    reference operator()(size_t row, size_t col) {
        return m_data(row,col);
    }

    /** Const access element (row,col) of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns const reference.
     *
     * @note This function does not range-check the arguments.
     */
    const_reference operator()(size_t row, size_t col) const {
        return m_data(row,col);
    }


  protected:

    /** Resize the array.
     *
     * This is a no-op for fixed-size arrays.
     */
    void resize(size_t,size_t) const {}


  protected:

    array_impl          m_data;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
