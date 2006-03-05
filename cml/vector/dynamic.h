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

/* This sets up the environment for oriented or unoriented vector copies: */
#if defined(CML_ENFORCE_VECTOR_ORIENTATION_ON_COPY)
  #define ORIENT_MACRO         Orient
  #define COPY_TEMPLATE_PARAMS template<typename E, class AT>
#else
  #define ORIENT_MACRO         O
  #define COPY_TEMPLATE_PARAMS template<typename E, class AT, typename O>
#endif

namespace cml {

/** Resizeable, dynamic-memory vector. */
template<typename Element, typename Alloc, typename Orient>
class vector<Element, dynamic<Alloc>, Orient>
: public dynamic_1D<Element,Alloc>
, public detail::vector::class_ops<Element, dynamic<Alloc>, Orient>
{
  public:

    /* Shorthand for the array type: */
    typedef dynamic_1D<Element,Alloc> array_type;

    /* Shorthand for the type of this vector: */
    typedef vector<Element,dynamic<Alloc>,Orient> vector_type;

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
    typedef vector<Element,dynamic<Alloc>,transposed_tag> transposed_type;

    /* For matching by size type: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::vector_result_tag result_tag;


  public:

    vector() : array_type() {}

    vector(size_t N) : array_type(N) {}

    /** Construct from a vector of the same type.
     *
     * @param v the vector to copy from.
     */
    vector(const vector_type& m) : array_type() {
        typedef et::OpAssign<Element,Element> OpT;
        et::UnrollAssignment<OpT>(*this,m);
    }

    /** Construct from another vector.
     *
     * @param v the vector to copy from.
     */
    COPY_TEMPLATE_PARAMS
    vector(const vector<E,AT,ORIENT_MACRO>& m) {
        typedef et::OpAssign<Element,E> OpT;
        et::UnrollAssignment<OpT>(*this,m);
    }

    /** Construct from a vector expression.
     *
     * @param expr the expression to copy from.
     */
    template<class XprT> vector(const et::VectorXpr<XprT>& expr) {
        /* Verify that a promotion exists at compile time: */
        typedef typename et::VectorPromote<
            vector_type, typename XprT::result_type>::type result_type;
        typedef typename XprT::value_type src_value_type;
        typedef et::OpAssign<Element,src_value_type> OpT;
        et::UnrollAssignment<OpT>(*this,expr);
    }
};

} // namespace cml

/* Clean up: */
#undef ORIENT_MACRO
#undef COPY_TEMPLATE_PARAMS

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
