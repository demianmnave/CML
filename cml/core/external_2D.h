/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * @todo Would casting get better performance in the external_2D<> element
 * access methods?
 *
 * @bug The row and col array types probably need to be changed from
 * external_1D<> to fixed_1D<>.
 */

#ifndef external_2D_h
#define external_2D_h

#include <cml/core/fwd.h>
#include <cml/core/common.h>
#include <cml/core/external_1D.h>

namespace cml {

template<typename Element, int Rows, int Cols, typename Layout>
class external_2D
{
  public:

    /* Require Rows > 0, Cols > 0: */
    CML_STATIC_REQUIRE((Rows > 0) && (Cols > 0));

    /* Record the generator: */
    typedef external<Rows,Cols> generator_type;

    /* Standard: */
    typedef Element value_type;
    typedef Element& reference;
    typedef const Element& const_reference;

    /* For matching by memory layout: */
    typedef Layout layout;

    /* For matching by memory type: */
    typedef external_memory_tag memory_tag;

    /* For matching by size type: */
    typedef fixed_size_tag size_tag;

    /* For matching by dimensions: */
    typedef twod_tag dimension_tag;

    /* To simplify the matrix transpose operator: */
    typedef external_2D<Element,Cols,Rows,Layout> transposed_type;

    /* To simplify the matrix row and column operators: */
    typedef external_1D<Element,Rows> row_array_type;
    typedef external_1D<Element,Cols> col_array_type;
    /* XXX This will probably need to be changed to fixed_1D<>. */


  public:

    enum { array_rows = Rows, array_cols = Cols };


  public:

    /** Construct an external array with no size. */
    external_2D(value_type* ptr) : m_data(ptr) {}


  public:

    /** Return the number of rows in the array. */
    size_t rows() const { return size_t(array_rows); }

    /** Return the number of cols in the array. */
    size_t cols() const { return size_t(array_cols); }


  public:

    /** Access element (row,col) of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns mutable reference.
     *
     * @note This function does not range-check the arguments.
     */
    reference operator()(size_t row, size_t col) {
        /* Dispatch to the right function based on layout: */
        return get_element(row,col,layout());
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
        /* Dispatch to the right function based on layout: */
        return get_element(row,col,layout());
    }


  protected:

    /* XXX May be able to cast to get better performance? */
    reference get_element(size_t row, size_t col, row_major) {
        return m_data[row*Cols + col];
    }

    const_reference get_element(size_t row, size_t col, row_major) const {
        return m_data[row*Cols + col];
    }

    reference get_element(size_t row, size_t col, col_major) {
        return m_data[col*Rows + row];
    }

    const_reference get_element(size_t row, size_t col, col_major) const {
        return m_data[col*Rows + row];
    }


  protected:

    /* Declare the data array: */
    value_type* const           m_data;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
