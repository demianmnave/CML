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
 * @sa cml::core::dynamic
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
template<typename Element, typename Orient, class Alloc>
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
    typedef Orient orientation;

    /* For matching by memory type: */
    typedef dynamic_memory_tag memory_tag;

    /* For matching by size type: */
    typedef dynamic_size_tag size_tag;


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

    /** Return the number of elements in the array. */
    size_t size() const { return this->rows()*this->cols(); }

    /** Return the number of rows in the array. */
    size_t rows() const { return this->m_rows; }

    /** Return the number of cols in the array. */
    size_t cols() const { return this->m_cols; }


  public:

    /** Linear access to the given element of the matrix.
     *
     * @param i position (in memory) of element to access.
     * @returns mutable reference.
     */
    reference operator()(size_t i) {
        return this->m_data[i];
    }

    /** Linear access to the given element of the matrix.
     *
     * @param i position (in memory) of element to access.
     * @returns const reference.
     */
    const_reference operator()(size_t i) const {
        return this->m_data[i];
    }

    /** Access the given element of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns mutable reference.
     */
    reference operator()(size_t row, size_t col) {
        return access(row, col, orientation());
    }

    /** Access the given element of the matrix.
     *
     * @param row row of element.
     * @param col column of element.
     * @returns const reference.
     */
    const_reference operator()(size_t row, size_t col) const {
        return access(row, col, orientation());
    }


  protected:

    /** Resize the array.
     *
     * @warning This is not guaranteed to preserve the original data.
     */
    void resize(size_t rows, size_t cols) {
        this->m_data.resize(rows*cols);
        this->m_rows = rows;
        this->m_cols = cols;
    }

    /** Access based on orientation. */
    reference access(size_t row, size_t col, row_major) {
        return this->m_data[row*m_cols + col];
    }

    /** Access based on orientation. */
    reference access(size_t row, size_t col, col_major) {
        return this->m_data[col*m_rows + row];
    }

    /** Access based on orientation. */
    const_reference access(size_t row, size_t col, row_major) const {
        return this->m_data[row*m_cols + col];
    }

    /** Access based on orientation. */
    const_reference access(size_t row, size_t col, col_major) const {
        return this->m_data[col*m_rows + row];
    }


  protected:

    size_t              m_rows, m_cols;
    array_impl          m_data;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
