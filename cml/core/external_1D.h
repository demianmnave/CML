/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef external_1D_h
#define external_1D_h

#include <cml/core/common.h>
#include <cml/fixed.h>

namespace cml {

/* Forward declare to record the external_1D generator type: */
template<int Dim1, int Dim2> struct external;

template<typename Element, int Size>
class external_1D
{
  public:

    /* Record the generator: */
    typedef external<Size,-1> generator_type;

    /* Standard: */
    typedef Element value_type;
    typedef Element& reference;
    typedef const Element& const_reference;

    /* Array implementation: */
    typedef value_type array_impl[Size];

    /* For matching by memory type: */
    typedef external_memory_tag memory_tag;

    /* For matching by size type: */
    typedef fixed_size_tag size_tag;

    /* For matching by dimensions: */
    typedef oned_tag dimension_tag;


  public:

    /** The length as an enumerated value. */
    enum { array_size = Size };


  public:

    external_1D(value_type* const ptr)
        : m_data(ptr) {}


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
    reference operator[](size_t i) { return m_data[i]; }

    /** Const access to the data as a C array.
     *
     * @param i a size_t index into the array.
     * @return a const reference to the array value at i.
     *
     * @note This function does not range-check the argument.
     */
    const_reference operator[](size_t i) const { return m_data[i]; }


  protected:

    value_type* const           m_data;


  protected:

    /* Initialization without an argument isn't allowed: */
    external_1D();
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
