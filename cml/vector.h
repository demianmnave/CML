/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  The configurable vector<> class.
 */

#ifndef vector_h
#define vector_h

#include <cstddef>              // for size_t
#include <cml/core/common.h>
#include <cml/et/vector_unroller.h>
#include <cml/vector_ops.h>
#include <cml/vector_dot.h>

namespace cml {

/** A configurable vector type.
 *
 * This class encapsulates the notion of a vector.  The ArrayType template
 * argument can be used to select the type of array to be used as internal
 * storage for a list of type Element.  The vector orientation determines
 * how vectors are used arithmetically in expressions; i.e. a*b, when a is
 * a row vector and b is a column vector, is the dot (inner) product, while
 * a*b, when a is a column vector and b is a row vector, is the matrix
 * (outer) product of a and b.
 *
 * @warning Currently, vectors with different types (Element and/or
 * ArrayType) can't be used in the same expression.
 *
 * @sa cml::core::fixed
 * @sa cml::core::dynamic
 *
 * @internal This "rebind" method avoids a lot of duplication compared to
 * the alternative of specializing vector<> for each storage type, since
 * e.g. vector class ops are consolidated here.  However, the tradeoff is
 * that vector<> must contain a compatible constructor for each type.  Also
 * note that a templated constructor leads to ambiguities, so removing this
 * constructor requirement doesn't seem to be straightforward.
 *
 * @internal All assignments to the vector should go through
 * et::UnrollAssignment, which verifies that the source expression and the
 * destination vector have the same size.  This is particularly important
 * for dynamically-sized vectors.
 */
template<typename Element, class ArrayType, class Orient>
class vector

/* Figure out (and inherit from) the selected base array type: */
: public ArrayType::template rebind<Element>::other
{
  public:

    /* Record incoming array type: */
    typedef ArrayType base_array_type;

    /* Shorthand for the array type: */
    typedef typename ArrayType::template rebind<Element>::other array_type;

    /* Shorthand for the type of this vector: */
    typedef vector<Element, ArrayType, Orient> vector_type;

    /* For integration into the expression template code: */
    typedef vector_type expr_type;

    /* Standard: */
    typedef typename array_type::value_type value_type;
    typedef typename array_type::reference reference;
    typedef typename array_type::const_reference const_reference;

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
    typedef vector<Element,ArrayType,transposed_tag> transposed_type;

    /* For matching by size type: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::vector_result_tag result_tag;


  public:

    /** Default constructor for dynamic arrays.
     *
     * @throws same as the ArrayType constructor.
     */
    vector() : array_type() {}

    /** Constructor for dynamic arrays.
     *
     * @param size specify the size of the array.
     *
     * @throws same as the ArrayType constructor.
     */
    explicit vector(size_t size) : array_type(size) {}

    /** Constructor for external arrays.
     *
     * @param size specify the size of the array.
     * @param ptr specify an external array pointer.
     *
     * @throws same as the ArrayType constructor.
     */
    explicit vector(size_t size, value_type* ptr) : array_type(size,ptr) {}


  public:

    /** Construct from a vector of the same type.
     *
     * @param v the vector to copy from.
     */
    vector(const vector_type& v) {
        typedef et::OpAssign<Element,Element> OpT;
        et::UnrollAssignment<OpT,expr_const_reference>(*this,v);
    }

    /** Construct from a vector expression.
     *
     * @param expr the expression to copy from.
     *
     * @bug The number of elements in the expression needs to be checked
     * against the size of the vector, especially for dynamic vectors.
     */
    template<class XprT> vector(const et::VectorXpr<XprT>& expr) {
        /* Verify that a promotion exists at compile time: */
        typedef typename et::VectorPromote<
            vector_type, typename XprT::result_type>::type result_type;
        typedef typename XprT::value_type src_value_type;
        typedef et::OpAssign<Element,src_value_type> OpT;
        et::UnrollAssignment<OpT>(*this,expr);
    }


  public:

    /** Assign this vector from another of the same type, with an operator.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     */
#define CML_ASSIGN_FROM_VEC(_op_, _op_name_)                            \
    vector_type& operator _op_ (const vector_type& v) {                 \
        typedef _op_name_ <Element,Element> OpT;                        \
        et::UnrollAssignment<OpT>(*this,v);                             \
        return *this;                                                   \
    }

    CML_ASSIGN_FROM_VEC(=, et::OpAssign)
    CML_ASSIGN_FROM_VEC(+=, et::OpAddAssign)
    CML_ASSIGN_FROM_VEC(-=, et::OpSubAssign)

#undef CML_ASSIGN_FROM_VEC


    /** Declare a function to assign this vector from a vector expression.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     */
#define CML_ASSIGN_FROM_VECXPR(_op_, _op_name_)                         \
    template<class XprT> vector_type&                                   \
    operator _op_ (const et::VectorXpr<XprT>& expr) {                   \
        /* Verify that a promotion exists at compile time: */           \
        typedef typename et::VectorPromote<                             \
            vector_type, typename XprT::result_type>::type result_type; \
        typedef typename XprT::value_type src_value_type;               \
        typedef _op_name_ <Element,src_value_type> OpT;                 \
        et::UnrollAssignment<OpT>(*this,expr);                          \
        return *this;                                                   \
    }

    CML_ASSIGN_FROM_VECXPR(=, et::OpAssign)
    CML_ASSIGN_FROM_VECXPR(+=, et::OpAddAssign)
    CML_ASSIGN_FROM_VECXPR(-=, et::OpSubAssign)

#undef CML_ASSIGN_FROM_VECXPR


    /** Declare a function to assign this vector from a scalar.
     *
     * @param _op_ the operator (e.g. *=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     *
     * @internal This shouldn't be used for ops, like +=, which aren't
     * defined in vector algebra.
     */
#define CML_ASSIGN_FROM_SCALAR(_op_, _op_name_)                         \
    vector_type& operator _op_ (const value_type& s) {                  \
        typedef _op_name_ <Element,value_type> OpT;                     \
        et::UnrollAssignment<OpT>(*this,s);                             \
        return *this;                                                   \
    }

    CML_ASSIGN_FROM_SCALAR(*=, et::OpMulAssign)
    CML_ASSIGN_FROM_SCALAR(/=, et::OpDivAssign)

#undef CML_ASSIGN_FROM_SCALAR
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
