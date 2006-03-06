/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Specialization for resizeable, dynamic-memory vector.
 */

#ifndef dynamic_vector_h
#define dynamic_vector_h

#include <cml/core/common.h>
#include <cml/vector/vector_unroller.h>
#include <cml/vector/class_ops.h>
#include <cml/dynamic.h>

namespace cml {

/** Resizeable, dynamic-memory vector. */
template<typename Element, typename Alloc, typename Orient>
class vector<Element, dynamic<Alloc>, Orient>
: public dynamic_1D<Element,Alloc>
{
  public:

    /* Shorthand for the generator: */
    typedef dynamic<Alloc> generator_type;

    /* Shorthand for the array type: */
    typedef dynamic_1D<Element,Alloc> array_type;

    /* Shorthand for the type of this vector: */
    typedef vector<Element,generator_type,Orient> vector_type;

    /* For integration into the expression template code: */
    typedef vector_type expr_type;

    /* Standard: */
    typedef typename array_type::value_type value_type;
    typedef typename array_type::reference reference;
    typedef typename array_type::const_reference const_reference;

    /* For integration into the expression templates code: */
    typedef vector_type& expr_reference;
    typedef const vector_type& expr_const_reference;

    /* For matching by storage type: */
    typedef typename array_type::memory_tag memory_tag;

    /* For matching by orientation: */
    typedef Orient orient_tag;
    /* Note: orientation is propagated up an expression tree and enforced
     * at compile time through the result_type expression trait.
     */

    /* To simplify transpose(): */
    typedef typename select_if<
        same_type<orient_tag,row_vector>::is_true,
        col_vector, row_vector>::result transposed_tag;
    typedef vector<Element,generator_type,transposed_tag> transposed_type;

    /* For matching by size type: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::vector_result_tag result_tag;


  public:

#if defined(CML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT)
    /** Default constructor.
     *
     * Only available if CML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT is
     * defined.
     */
    vector() : array_type() {}
#endif

    /** Construct given array size. */
    vector(size_t N) : array_type(N) {}


  public:

    /* Define common class operators: */
    CML_VEC_ASSIGN_FROM_VECTYPE

    CML_VEC_COPY_FROM_VEC
    CML_VEC_COPY_FROM_VECXPR

    CML_VEC_ASSIGN_FROM_VEC(=, cml::et::OpAssign)
    CML_VEC_ASSIGN_FROM_VEC(+=, cml::et::OpAddAssign)
    CML_VEC_ASSIGN_FROM_VEC(-=, cml::et::OpSubAssign)

    CML_VEC_ASSIGN_FROM_VECXPR(=, cml::et::OpAssign)
    CML_VEC_ASSIGN_FROM_VECXPR(+=, cml::et::OpAddAssign)
    CML_VEC_ASSIGN_FROM_VECXPR(-=, cml::et::OpSubAssign)

    CML_VEC_ASSIGN_FROM_SCALAR(*=, cml::et::OpMulAssign)
    CML_VEC_ASSIGN_FROM_SCALAR(/=, cml::et::OpDivAssign)
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
