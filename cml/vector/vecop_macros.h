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
 * All of the generator functions compress the expression tree by hoisting
 * subexpressions into the containing expression.  This has the effect of
 * forcing only the root node of the expression tree to be a VectorXpr.
 * Every other node is a Unary or BinaryVectorOp.
 *
 * @todo Should ScalarT in expressions be passed by reference or by value?
 */

#ifndef vecop_macros_h
#define vecop_macros_h

#include <cml/et/scalar_ops.h>
#include <cml/vector/vector_expr.h>

/** Declare a unary operator taking a vector operand. */
#define CML_VEC_UNIOP(_op_, _OpT_)                                       \
template<typename E, class AT, class O>                                  \
inline et::VectorXpr<                                                    \
    et::UnaryVectorOp< vector<E,AT,O>, _OpT_ <E> >                       \
>                                                                        \
                                                                         \
_op_ (const vector<E,AT,O>& arg)                                         \
{                                                                        \
    typedef et::UnaryVectorOp<                                           \
            vector<E,AT,O>, _OpT_ <E>                                    \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(arg));                             \
}


/** Declare a unary operator taking a et::VectorXpr operand. */
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


/** Declare an operator taking two vector operands. */
#define CML_VEC_VEC_BINOP(_op_, _OpT_)                                   \
template<typename E1, class AT1, typename E2, class AT2, class O>        \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        vector<E1,AT1,O>, vector<E2,AT2,O>, _OpT_ <E1,E2>                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const vector<E1,AT1,O>& left,                                    \
        const vector<E2,AT2,O>& right)                                   \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            vector<E1,AT1,O>, vector<E2,AT2,O>, _OpT_ <E1,E2>            \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right));                      \
}


/** Declare an operator taking a vector and a et::VectorXpr. */
#define CML_VEC_VECXPR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, class O, class XprT>                      \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        vector<E,AT,O>, XprT, _OpT_ <E, typename XprT::value_type>       \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const vector<E,AT,O>& left,                                      \
        const et::VectorXpr<XprT>& right)                                \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            vector<E,AT,O>, XprT,                                        \
            _OpT_ <E, typename XprT::value_type>                         \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right.expression()));         \
}


/** Declare an operator taking an et::VectorXpr and a vector. */
#define CML_VECXPR_VEC_BINOP(_op_, _OpT_)                                \
template<class XprT, typename E, class AT, class O>                      \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        XprT, vector<E,AT,O>, _OpT_ <typename XprT::value_type, E>       \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const et::VectorXpr<XprT>& left,                                 \
        const vector<E,AT,O>& right)                                     \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            XprT, vector<E,AT,O>,                                        \
            _OpT_ <typename XprT::value_type, E>                         \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left.expression(),right));         \
}


/** Declare an operator taking two et::VectorXpr operands. */
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
template<typename E, class AT, class O, typename ScalarT>                \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        vector<E,AT,O>, ScalarT, _OpT_ <E,ScalarT>                       \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const vector<E,AT,O>& left,                                      \
        SCALAR_ARG_TYPE right)                                           \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            vector<E,AT,O>, ScalarT, _OpT_ <E,ScalarT>                   \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right));                      \
}


/** Declare an operator taking a scalar and a vector. */
#define CML_SCALAR_VEC_BINOP(_op_, _OpT_)                                \
template<typename ScalarT, typename E, class AT, class O>                \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        ScalarT, vector<E,AT,O>, _OpT_ <ScalarT,E>                       \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        SCALAR_ARG_TYPE left,                                            \
        const vector<E,AT,O>& right)                                     \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            ScalarT, vector<E,AT,O>, _OpT_ <ScalarT,E>                   \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right));                      \
}


/** Declare an operator taking a et::VectorXpr and a scalar. */
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
        SCALAR_ARG_TYPE right)                                           \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>     \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left.expression(),right));         \
}


/** Declare an operator taking a scalar and a et::VectorXpr. */
#define CML_SCALAR_VECXPR_BINOP(_op_, _OpT_)                             \
template<typename ScalarT, class XprT>                                   \
inline et::VectorXpr<                                                    \
    et::BinaryVectorOp<                                                  \
        ScalarT, XprT, _OpT_ <ScalarT, typename XprT::value_type>        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        SCALAR_ARG_TYPE left,                                            \
        const et::VectorXpr<XprT>& right)                                \
{                                                                        \
    typedef et::BinaryVectorOp<                                          \
            ScalarT, XprT,                                               \
            _OpT_ <ScalarT, typename XprT::value_type>                   \
        > ExprT;                                                         \
    return et::VectorXpr<ExprT>(ExprT(left,right.expression()));         \
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
