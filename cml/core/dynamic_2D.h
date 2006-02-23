/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_2D_h
#define dynamic_2D_h

#include <vector>
#include <cml/core/common.h>

namespace cml {

/** Dynamically-sized and allocated 2D array.
 *
 * @sa cml::dynamic
 *
 * @note The allocator should be an STL-compatible allocator.
 *
 * @todo This uses a std::vector<> to implement the dynamic array, which
 * really is overkill, but has the proper copy semantics (this is the only
 * reason it is used).  It is not too hard to implement a simpler dynamic
 * array to replace std::vector<>, and should be done.
 *
 * @internal This class does not need a destructor.
 */
template<typename Element, typename Layout, class Alloc>
class dynamic_2D
{
  public:

    /* Array implementation: */
    typedef std::vector<Element,Alloc> array_impl;

    /* Standard: */
    typedef typename array_impl::value_type value_type;
    typedef typename array_impl::reference reference; 
    typedef typename array_impl::const_reference const_reference; 

    /* Record the allocator type: */
    typedef typename array_impl::allocator_type allocator_type;

    /* For matching by memory layout: */
    typedef Layout layout;

    /* For matching by memory type: */
    typedef dynamic_memory_tag memory_tag;

    /* For matching by size type: */
    typedef dynamic_size_tag size_tag;

    /* For matching by dimensions: */
    typedef twod_tag dimension_tag;


  protected:

    /** Construct a dynamic array with no size. */
    dynamic_2D() {}

    /** Construct a dynamic matrix given the dimensions.
     *
     * This constructor is guaranteed to throw only if the allocator throws.
     * If the array implementation guarantees that the array data structure is
     * not modified after an exception, then this constructor is
     * exception-safe.
     *
     * @throws only if the allocator throws during an allocation.
     */
    explicit dynamic_2D(size_t rows, size_t cols) 
        : m_rows(rows), m_cols(cols), m_data(rows*cols) {}


  public:

    enum { array_rows = -1, array_cols = -1 };


  public:

    /** Return the number of rows in the array. */
    size_t rows() const { return m_rows; }

    /** Return the number of cols in the array. */
    size_t cols() const { return m_cols; }


  public:

    /** Access the given element of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns mutable reference.
     */
    reference operator()(size_t row, size_t col) {
        return get_element(row, col, layout());
    }

    /** Access the given element of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns const reference.
     */
    const_reference operator()(size_t row, size_t col) const {
        return get_element(row, col, layout());
    }

    /** Resize the array.
     *
     * @warning This is not guaranteed to preserve the original data.
     */
    void resize(size_t rows, size_t cols) {
        m_data.resize(rows*cols); m_rows = rows; m_cols = cols;
    }


  protected:

    reference get_element(size_t row, size_t col, row_major) {
        return m_data[row*m_cols + col];
    }

    const_reference get_element(size_t row, size_t col, row_major) const {
        return m_data[row*m_cols + col];
    }

    reference get_element(size_t row, size_t col, col_major) {
        return m_data[col*m_rows + row];
    }

    const_reference get_element(size_t row, size_t col, col_major) const {
        return m_data[col*m_rows + row];
    }


  protected:

    size_t                      m_rows, m_cols;
    array_impl                  m_data;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
