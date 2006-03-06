/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Specialization for fixed-size, external-memory vectors.
 *
 *  @note External vectors currently cannot be copy-constructed.  Making
 *  copy construction work properly requires a safe way to transfer
 *  ownership of pointers.
 */

#ifndef external_vector_h
#define external_vector_h

#include <cml/core/common.h>
#include <cml/vector/vector_unroller.h>
#include <cml/vector/class_ops.h>
#include <cml/external.h>

namespace cml {

/** Fixed-size, fixed-memory vector. */
template<typename Element, int Size, typename Orient>
class vector<Element, external<Size>, Orient>
: public external_1D<Element,Size>
{
  public:

    /* Shorthand for the generator: */
    typedef external<Size> generator_type;

    /* Shorthand for the array type: */
    typedef external_1D<Element,Size> array_type;

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
        same_type<Orient,row_vector>::is_true,
        col_vector, row_vector>::result transposed_tag;
    typedef cml::vector<Element,generator_type,transposed_tag> transposed_type;

    /* For matching by size type: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::vector_result_tag result_tag;


  public:

    /** Construct from an array of values. */
    vector(Element* const array) : array_type(array) {}


  public:

    /* Define class operators for external vectors. Note: external vectors
     * cannot be copy-constructed, but they can be assigned to:
     */
    CML_VEC_ASSIGN_FROM_VECTYPE

    /* Only assignment operators can be used to copy from other types: */
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
