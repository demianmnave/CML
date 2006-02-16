/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the various combinations of vector expressions.
 *
 * Create unary and binary operators with macros.  The available combinations
 * are:
 *
 * Unary expressions:
 *
 * op Vector -> Vector
 * op VecXpr -> Vector
 *
 * Binary expressions:
 *
 * Vector op Vector -> Vector
 * VecXpr op Vector -> VecXpr
 * Vector op VecXpr -> VecXpr
 * VecXpr op VecXpr -> VecXpr
 *
 * Vector op Scalar -> Vector
 * Scalar op Vector -> Vector
 * VecXpr op Scalar -> VecXpr
 * Scalar op VecXpr -> VecXpr
 *
 * @todo Allow operators on vectors with different element types, and
 * eventually between vectors of different storage types also.
 */

#ifndef vecop_macros_h
#define vecop_macros_h

#include <cml/et/scalar_ops.h>
#include <cml/et/vector_expr.h>

namespace cml {

/** Declare a unary operator taking a vector operand. */
#define CML_VEC_UNIOP(_op_, _OpT_)                                       \
template<typename E, class AT>                                           \
inline et::VectorXpr<                                                    \
    et::UnaryVectorOp< vector<E,AT>, _OpT_ <E> >                         \
>                                                                        \
                                                                         \
_op_ (const vector<E,AT>& arg)                                           \
{                                                                        \
    typedef et::UnaryVectorOp<                                           \
            vector<E,AT>, _OpT_ <E>                                      \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(arg));                             \
}


/** Declare a unary operator taking a et::VectorXpr operand.
 *
 * The resulting VectorXpr has a UnaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpression of the UnaryVectorOp.
 */
#define CML_VECXPR_UNIOP(_op_, _OpT_)                                    \
template<class XprT>                                                     \
inline et::VectorXpr<                                                    \
    et::UnaryVectorOp< XprT, _OpT_ <typename XprT::value_type> >         \
>                                                                        \
                                                                         \
_op_ (const et::VectorXpr<XprT>& arg)                                    \
{                                                                        \
    typedef et::UnaryVectorOp<                                           \
        XprT, _OpT_ <typename XprT::value_type>                          \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(arg.expression()));                \
}


/** Declare an operator taking two vector operands.
 *
 * The vectors must have the same type (for now).
 */
#define CML_VEC_VEC_BINOP(_op_, _OpT_)                                   \
template<typename E, class AT>                                           \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        vector<E,AT>, vector<E,AT>, _OpT_ <E,E>                          \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const vector<E,AT>& left,                                        \
        const vector<E,AT>& right)                                       \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            vector<E,AT>, vector<E,AT>, _OpT_ <E,E>                      \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right));                      \
}


/** Declare an operator taking a vector and a et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorOp.
 */
#define CML_VEC_VECXPR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, class XprT>                               \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        vector<E,AT>, XprT, _OpT_ <E, typename XprT::value_type>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const vector<E,AT>& left,                                        \
        const et::VectorXpr<XprT>& right)                                \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            vector<E,AT>, XprT,                                          \
            _OpT_ <E, typename XprT::value_type>                         \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right.expression()));         \
}


/** Declare an operator taking a et::VectorXpr and a vector.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the left subexpression of the BinaryVectorOp.
 */
#define CML_VECXPR_VEC_BINOP(_op_, _OpT_)                                \
template<class XprT, typename E, class AT>                               \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        XprT, vector<E,AT>, _OpT_ <typename XprT::value_type, E>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::VectorXpr<XprT>& left,                                 \
        const vector<E,AT>& right)                                       \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            XprT, vector<E,AT>,                                          \
            _OpT_ <typename XprT::value_type, E>                         \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left.expression(),right));         \
}


/** Declare an operator taking two et::VectorXpr operands.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpressions of the BinaryVectorOp.
 */
#define CML_VECXPR_VECXPR_BINOP(_op_, _OpT_)                             \
template<class XprT1, class XprT2>                                       \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        XprT1, XprT2,                                                    \
        _OpT_ <                                                          \
            typename XprT1::value_type,                                  \
            typename XprT2::value_type                                   \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::VectorXpr<XprT1>& left,                                \
        const et::VectorXpr<XprT2>& right)                               \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            XprT1, XprT2,                                                \
            _OpT_ <                                                      \
                typename XprT1::value_type,                              \
                typename XprT2::value_type>                              \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(                                         \
            ExprT(left.expression(),right.expression()));                \
}


/** Declare an operator taking a vector and a scalar. */
#define CML_VEC_SCALAR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, typename ScalarT>                         \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        vector<E,AT>, ScalarT, _OpT_ <E,ScalarT>                         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const vector<E,AT>& left,                                        \
        const ScalarT& right)                                            \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            vector<E,AT>, ScalarT, _OpT_ <E,ScalarT>                     \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right));                      \
}


/** Declare an operator taking a scalar and a vector. */
#define CML_SCALAR_VEC_BINOP(_op_, _OpT_)                                \
template<typename ScalarT, typename E, class AT>                         \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        ScalarT, vector<E,AT>, _OpT_ <ScalarT,E>                         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const ScalarT& left,                                             \
        const vector<E,AT>& right)                                       \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            ScalarT, vector<E,AT>,                                       \
            _OpT_ <ScalarT,E>                                            \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right));                      \
}


/** Declare an operator taking a et::VectorXpr and a scalar.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression. The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the left subexpression of the BinaryVectorOp.
 */
#define CML_VECXPR_SCALAR_BINOP(_op_, _OpT_)                             \
template<class XprT, typename ScalarT>                                   \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::VectorXpr<XprT>& left,                                 \
        const ScalarT& right)                                            \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>     \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left.expression(),right));         \
}


/** Declare an operator taking a scalar and a et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression. The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorOp.
 */
#define CML_SCALAR_VECXPR_BINOP(_op_, _OpT_)                             \
template<typename ScalarT, class XprT>                                   \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        ScalarT, XprT, _OpT_ <ScalarT, typename XprT::value_type>        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const ScalarT& left,                                             \
        const et::VectorXpr<XprT>& right)                                \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            ScalarT, XprT,                                               \
            _OpT_ <ScalarT, typename XprT::value_type>                   \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right.expression()));         \
}


} // cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
