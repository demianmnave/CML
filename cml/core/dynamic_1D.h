/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_1D_h
#define dynamic_1D_h

#include <vector>
#include <cml/core/common.h>

namespace cml {

/** Dynamically-sized and allocated 1D array.
 *
 * @sa cml::dynamic
 *
 * @note The allocator should be an STL-compatible allocator.
 *
 * @todo This uses a std::vector<> to implement the dynamic array, which
 * really is overkill, but has the proper copy semantics (this is the only
 * reason it is used).  It is not too hard to implement a simpler dynamic
 * array to replace std::vector<>, and should be done.
 */
template<typename Element, class Alloc>
class dynamic_1D
{
  public:

    /* Record the allocator type: */
    typedef typename Alloc::template rebind<Element>::other allocator_type;

    /* Record the generator: */
    typedef dynamic<Alloc> generator_type;

    /* Array implementation: */
    typedef std::vector<Element,allocator_type> array_impl;

    /* Standard: */
    typedef typename array_impl::value_type value_type;
    typedef typename array_impl::reference reference; 
    typedef typename array_impl::const_reference const_reference; 

    /* For matching by memory type: */
    typedef dynamic_memory_tag memory_tag;

    /* For matching by size type: */
    typedef dynamic_size_tag size_tag;

    /* For matching by dimensions: */
    typedef oned_tag dimension_tag;


  public:

    /** Dynamic arrays have no fixed size. */
    enum { array_size = -1 };


  public:

    /** Construct a dynamic array with no size. */
    dynamic_1D() {}

    /** Construct a dynamic array given the size. */
    explicit dynamic_1D(size_t size) : m_data(size) {}


  public:

    /** Return the number of elements in the array. */
    size_t size() const { return this->m_data.size(); }

    /** Access to the data as a C array.
     *
     * @param i a size_t index into the array.
     * @return a mutable reference to the array value at i.
     *
     * @note This function does not range-check the argument.
     */
    reference operator[](size_t i) { return this->m_data[i]; }

    /** Const access to the data as a C array.
     *
     * @param i a size_t index into the array.
     * @return a const reference to the array value at i.
     *
     * @note This function does not range-check the argument.
     */
    const_reference operator[](size_t i) const { return this->m_data[i]; }


  public:

    /** Set the array size to the given value.
     *
     * @warning This is not guaranteed to preserve the original data.
     */
    void resize(size_t s) { this->m_data.resize(s); }


  protected:

    array_impl                  m_data;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
