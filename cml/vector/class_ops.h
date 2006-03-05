/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Base class defining vector class operators.
 */

#ifndef vector_class_ops_h
#define vector_class_ops_h

#include <cml/core/common.h>
#include <cml/core/cml_meta.h>
#include <cml/et/scalar_ops.h>
#include <cml/vector/vector_expr.h>
#include <cml/vector/vector_unroller.h>

/* This sets up the environment for oriented or unoriented vector copies: */
#if defined(CML_ENFORCE_VECTOR_ORIENTATION_ON_COPY)
  #define ORIENT_MACRO         Orient
  #define COPY_TEMPLATE_PARAMS template<typename E, class AT>
#else
  #define ORIENT_MACRO         O
  #define COPY_TEMPLATE_PARAMS template<typename E, class AT, typename O>
#endif

namespace cml {

/* Forward declare for vector specializations that include this file: */
template<typename E, class AT, typename O> class vector;

/* Put classes that should be visible only to the library into namespace
 * detail:
 */
namespace detail {

/* Put vector-specific classes into namespace vector: */
namespace vector {

/** Base class defining vector class operators.
 *
 * This should be derived from by any vector class that requires assignment
 * operators.
 *
 * @todo This can be refined into several classes to support different
 * sorts of general class operators.
 */
template<typename Element, class ArrayType, typename Orient>
struct class_ops
{
    /* The vector type using this class: */
    typedef cml::vector<Element,ArrayType,Orient> vector_type;

    /* Define the transposed type: */
    typedef typename select_if<
        same_type<Orient,row_vector>::is_true,
        col_vector, row_vector>::result transposed_tag;
    typedef cml::vector<Element,ArrayType,transposed_tag> transposed_type;

    /** Assign this vector from another using the given elementwise op.
     *
     * This allows assignment from arbitrary vector types.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     */
#define CML_ASSIGN_FROM_VEC(_op_, _op_name_)                            \
    COPY_TEMPLATE_PARAMS vector_type&                                   \
    operator _op_ (const cml::vector<E,AT,ORIENT_MACRO>& m) {           \
        typedef _op_name_ <Element,E> OpT;                              \
        cml::et::UnrollAssignment<OpT>(*static_cast<vector_type*>(this),m);  \
        return *static_cast<vector_type*>(this);                        \
    }

    CML_ASSIGN_FROM_VEC(=, cml::et::OpAssign)
    CML_ASSIGN_FROM_VEC(+=, cml::et::OpAddAssign)
    CML_ASSIGN_FROM_VEC(-=, cml::et::OpSubAssign)
#undef CML_ASSIGN_FROM_VEC


    /** Declare a function to assign this vector from a vector expression.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     */
#define CML_ASSIGN_FROM_VECXPR(_op_, _op_name_)                         \
    template<class XprT> vector_type&                                   \
    operator _op_ (const cml::et::VectorXpr<XprT>& e) {                 \
        /* Verify that a promotion exists at compile time: */           \
        typedef typename et::VectorPromote<                             \
            vector_type, typename XprT::result_type>::type result_type; \
        typedef typename XprT::value_type src_value_type;               \
        typedef _op_name_ <Element,src_value_type> OpT;                 \
        cml::et::UnrollAssignment<OpT>(*static_cast<vector_type*>(this),e);  \
        return *static_cast<vector_type*>(this);                        \
    }

    CML_ASSIGN_FROM_VECXPR(=, cml::et::OpAssign)
    CML_ASSIGN_FROM_VECXPR(+=, cml::et::OpAddAssign)
    CML_ASSIGN_FROM_VECXPR(-=, cml::et::OpSubAssign)
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
    vector_type& operator _op_ (const Element& s) {                     \
        typedef _op_name_ <Element,Element> OpT;                        \
        cml::et::UnrollAssignment<OpT>(*static_cast<vector_type*>(this),s);  \
        return *static_cast<vector_type*>(this);                        \
    }

    CML_ASSIGN_FROM_SCALAR(*=, cml::et::OpMulAssign)
    CML_ASSIGN_FROM_SCALAR(/=, cml::et::OpDivAssign)
#undef CML_ASSIGN_FROM_SCALAR
};

} // namespace vector
} // namespace detail
} // namespace cml

/* Clean up: */
#undef ORIENT_MACRO
#undef COPY_TEMPLATE_PARAMS

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
