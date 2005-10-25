/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  @todo Collapse duplicated dynamic_1D code into a single base class,
 *  derive the fixed- and dynamic-sized arrays from that.
 */

#ifndef dynamic_1D_h
#define dynamic_1D_h

#include <vector>
#include <cml/common.h>

namespace cml {

/* Forward declare the dynamic array wrapepr.  This has partial
 * specializations below for the case of dynamic- and fixed-size arrays:
 */
template<typename Element, int Size = 0,
    class Alloc = std::allocator<Element> > class dynamic_1D;

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
class dynamic_1D<Element,0,Alloc>
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

    /* For matching by memory type: */
    typedef dynamic_memory_tag  memory_tag;

    /* For matching by size type: */
    typedef dynamic_size_tag    size_tag;


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


  protected:

    /** Set the array size to the given value.
     *
     * @warning This is not guaranteed to preserve the original data.
     */
    void resize(size_t s) { this->m_data.resize(s); }


  protected:

    array_impl                  m_data;
};


/** Fixed-size, dynamically allocated 1D array.
 *
 * @sa cml::dynamic
 *
 * @note The allocator should be an STL-compatible allocator.
 *
 * @note This is much slower than fixed_1D<> for the same fixed size, but
 * allows for a custom memory allocator (e.g. a placement new() allocator to
 * implement external arrays).
 *
 * @todo This uses a std::vector<> to implement the dynamic array, which
 * really is overkill, but has the proper copy semantics (this is the only
 * reason it is used).  It is not too hard to implement a simpler dynamic
 * array to replace std::vector<>, and should be done.
 */
template<typename Element, int Size, class Alloc>
class dynamic_1D
{
  public:

    /* Array implementation: */
    typedef std::vector<Element,Alloc> array_impl;

    /* Standard: */
    typedef typename array_impl::value_type value_type;
    typedef typename array_impl::reference reference; 
    typedef typename array_impl::const_reference const_reference; 

    /* Record the allocator type: */
    typedef Alloc               allocator_type;

    /* For matching by memory type: */
    typedef dynamic_memory_tag  memory_tag;

    /* For matching by size type: */
    typedef fixed_size_tag      size_tag;


  public:

    /** The length as an enumerated value. */
    enum { array_size = Size };


  public:

    /** Construct a dynamic array with the given (fixed) size.
     *
     * @throws only if the allocator throws during an allocation.
     */
    dynamic_1D() : m_data(array_size) {}


  public:

    /** Return the number of elements in the array. */
    size_t size() const { return size_t(array_size); }

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


  protected:

    /** This is a no-op, because the size is fixed. */
    void resize(size_t) const {}


  protected:

    array_impl                  m_data;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
