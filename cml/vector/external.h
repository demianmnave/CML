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

#include <cml/core/external_1D.h>
#include <cml/vector/vector_expr.h>
#include <cml/vector/class_ops.h>
#include <cml/vector/vector_unroller.h>

namespace cml {

/** Fixed-size, fixed-memory vector. */
template<typename Element, int Size>
class vector< Element, external<Size> >
: public external_1D<Element,Size>
{
  public:

    /* Shorthand for the generator: */
    typedef external<Size> generator_type;

    /* Shorthand for the array type: */
    typedef external_1D<Element,Size> array_type;

    /* Shorthand for the type of this vector: */
    typedef vector<Element,generator_type> vector_type;

    /* For integration into the expression template code: */
    typedef vector_type expr_type;

    /* For integration into the expression template code: */
    typedef vector< Element,fixed<Size> > temporary_type;
    /* Note: this ensures that an external vector is copied into the proper
     * temporary; external<> temporaries are not allowed.
     */

    /* Standard: */
    typedef typename array_type::value_type value_type;
    typedef typename array_type::reference reference;
    typedef typename array_type::const_reference const_reference;

    /* For integration into the expression templates code: */
    typedef vector_type& expr_reference;
    typedef const vector_type& expr_const_reference;

    /* For matching by storage type: */
    typedef typename array_type::memory_tag memory_tag;

    /* For matching by size type: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::vector_result_tag result_tag;

    /* For matching by assignability: */
    typedef cml::et::assignable_tag assignable_tag;


  public:

    /** Return square of the length. */
    value_type length_squared() const {
        return dot(*this,*this);
    }

    /** Return the length. */
    value_type length() const {
        return std::sqrt(length_squared());
    }

    /** Normalize the vector. */
    vector_type& normalize() {
        return (*this /= length());
    }

    /** Set this vector to [0]. */
    vector_type& zero() {
        typedef cml::et::OpAssign<Element,Element> OpT;
        cml::et::UnrollAssignment<OpT>(*this,Element(0));
        return *this;
    }

    /** Set this vector to a cardinal vector. */
    vector_type& cardinal(size_t i) {
        zero();
        (*this)[i] = Element(1);
        return *this;
    }


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

/** Run-time sized vector. */
template<typename Element>
class vector< Element, external<> >
: public external_1D<Element>
{
  public:

    /* Shorthand for the generator: */
    typedef external<> generator_type;

    /* Shorthand for the array type: */
    typedef external_1D<Element> array_type;

    /* Shorthand for the type of this vector: */
    typedef vector<Element,generator_type> vector_type;

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

    /* For matching by size type: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::vector_result_tag result_tag;


  public:

    /** Construct from an array of values and the size. */
    vector(Element* const array, size_t size)
        : array_type(array, size) {}


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
