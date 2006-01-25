/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the various combinations of vector expressions.
 *
 * @note Operator performance relies heavily upon the compiler's ability to
 * optimize away temporaries and to inline function calls.
 *
 * @todo Allow operators on vectors with different element types, and
 * eventually between vectors of different storage types also.
 */

#ifndef vector_ops_h
#define vector_ops_h

#include <cml/et/scalar_ops.h>
#include <cml/et/vector_expr.h>

namespace cml {
namespace vector_ops {

/** Declare a unary operator taking a cml::vector operand.
 *
 * @note cml::et::ExprTraits must be defined for the vector's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_VEC_UNIOP(_op_, _OpT_)                                       \
template<typename E, class AT>                                           \
inline cml::et::VectorXpr<                                               \
    cml::et::UnaryVectorOp<                                              \
        cml::vector<E,AT>,                                               \
        cml::et:: _OpT_<typename cml::et::ExprTraits<E>::value_type>     \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (const cml::vector<E,AT>& arg)                                      \
{                                                                        \
    typedef cml::et::UnaryVectorOp<                                      \
            cml::vector<E,AT>,                                           \
            cml::et:: _OpT_<typename cml::et::ExprTraits<E>::value_type> \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(arg));                        \
}

/** Declare a unary operator taking a cml::et::VectorXpr operand.
 *
 * The resulting VectorXpr has a UnaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpression of the UnaryVectorOp.
 */
#define CML_VECXPR_UNIOP(_op_, _OpT_)                                    \
template<class XprT>                                                     \
inline cml::et::VectorXpr<                                               \
    cml::et::UnaryVectorOp<                                              \
        XprT, cml::et:: _OpT_<typename XprT::value_type>                 \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (const cml::et::VectorXpr<XprT>& arg)                               \
{                                                                        \
    typedef cml::et::UnaryVectorOp<                                      \
        XprT, cml::et:: _OpT_<typename XprT::value_type>                 \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(arg.expression()));           \
}

/** Declare an operator taking two cml::vector operands.
 *
 * The vectors must have the same type (for now).
 *
 * @note cml::et::ExprTraits must be defined for the vector's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_VEC_VEC_BINOP(_op_, _OpT_)                                   \
template<typename E, class AT>                                           \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        cml::vector<E,AT>, cml::vector<E,AT>,                            \
        cml::et:: _OpT_<                                                 \
            typename cml::et::ExprTraits<E>::value_type,                 \
            typename cml::et::ExprTraits<E>::value_type                  \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            cml::vector<E,AT>, cml::vector<E,AT>,                        \
            cml::et:: _OpT_<                                             \
                typename cml::et::ExprTraits<E>::value_type,             \
                typename cml::et::ExprTraits<E>::value_type>             \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}

/** Declare an operator taking a cml::et::VectorXpr and a cml::vector.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the left subexpression of the BinaryVectorOp.
 *
 * @note cml::et::ExprTraits must be defined for the vector's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_VECXPR_VEC_BINOP(_op_, _OpT_)                                \
template<class XprT, typename E, class AT>                               \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        XprT, cml::vector<E,AT>,                                         \
        cml::et:: _OpT_ <                                                \
            typename XprT::value_type,                                   \
            typename cml::et::ExprTraits<E>::value_type                  \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT>& left,                            \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            XprT, cml::vector<E,AT>,                                     \
            cml::et:: _OpT_ <                                            \
                typename XprT::value_type,                               \
                typename cml::et::ExprTraits<E>::value_type>             \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left.expression(),right));    \
}

/** Declare an operator taking a cml::vector and a cml::et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorOp.
 *
 * @note cml::et::ExprTraits must be defined for the vector's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_VEC_VECXPR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, class XprT>                               \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        cml::vector<E,AT>, XprT,                                         \
        cml::et:: _OpT_ <                                                \
            typename cml::et::ExprTraits<E>::value_type,                 \
            typename XprT::value_type                                    \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::et::VectorXpr<XprT>& right)                           \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            cml::vector<E,AT>, XprT,                                     \
            cml::et:: _OpT_ <                                            \
                typename cml::et::ExprTraits<E>::value_type,             \
                typename XprT::value_type>                               \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right.expression()));    \
}

/** Declare an operator taking two cml::et::VectorXpr operands.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpressions of the BinaryVectorOp.
 */
#define CML_VECXPR_VECXPR_BINOP(_op_, _OpT_)                             \
template<class XprT1, class XprT2>                                       \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        XprT1, XprT2,                                                    \
        cml::et:: _OpT_ <                                                \
            typename XprT1::value_type,                                  \
            typename XprT2::value_type                                   \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT1>& left,                           \
        const cml::et::VectorXpr<XprT2>& right)                          \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            XprT1, XprT2,                                                \
            cml::et:: _OpT_ <                                            \
                typename XprT1::value_type,                              \
                typename XprT2::value_type>                              \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(                                    \
            ExprT(left.expression(),right.expression()));                \
}


/** Declare an operator taking a cml::vector and a "literal".
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 *
 * @internal This may require a separate "Scalar" class to prevent odd
 * errors...
 */
#define CML_VEC_LIT_BINOP(_op_, _OpT_)                                   \
template<typename E, class AT, typename LitT>                            \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        cml::vector<E,AT>, LitT,                                         \
        cml::et:: _OpT_<                                                 \
            typename cml::et::ExprTraits<E>::value_type,                 \
            typename cml::et::ExprTraits<LitT>::value_type>              \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const LitT& right)                                               \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            cml::vector<E,AT>, LitT,                                     \
            cml::et:: _OpT_ <                                            \
                typename cml::et::ExprTraits<E>::value_type,             \
                typename cml::et::ExprTraits<LitT>::value_type>          \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}

/** Declare an operator taking a "literal" and a cml::vector.
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 *
 * @internal This may require a separate "Scalar" class to prevent odd
 * errors...
 */
#define CML_LIT_VEC_BINOP(_op_, _OpT_)                                   \
template<typename LitT, typename E, class AT>                            \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        LitT, cml::vector<E,AT>,                                         \
        cml::et:: _OpT_<                                                 \
            typename cml::et::ExprTraits<LitT>::value_type,              \
            typename cml::et::ExprTraits<E>::value_type>                 \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const LitT& left,                                                \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            LitT, cml::vector<E,AT>,                                     \
            cml::et:: _OpT_<                                             \
                typename cml::et::ExprTraits<LitT>::value_type,          \
                typename cml::et::ExprTraits<E>::value_type>             \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}

/** Declare an operator taking a cml::et::VectorXpr and a "literal"
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression. The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the left subexpression of the BinaryVectorOp.
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_VECXPR_LIT_BINOP(_op_, _OpT_)                                \
template<class XprT, typename LitT>                                      \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        XprT, LitT,                                                      \
        cml::et:: _OpT_ <                                                \
            typename XprT::value_type,                                   \
            typename cml::et::ExprTraits<LitT>::value_type               \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT>& left,                            \
        const LitT& right)                                               \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            XprT, LitT,                                                  \
            cml::et:: _OpT_ <                                            \
                typename XprT::value_type,                               \
                typename cml::et::ExprTraits<LitT>::value_type>          \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left.expression(),right));    \
}

/** Declare an operator taking a "literal" and a cml::et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression. The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorOp.
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_LIT_VECXPR_BINOP(_op_, _OpT_)                                \
template<typename LitT, class XprT>                                      \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        LitT, XprT,                                                      \
        cml::et:: _OpT_ <                                                \
            typename cml::et::ExprTraits<LitT>::value_type,              \
            typename XprT::value_type                                    \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const LitT& left,                                                \
        const cml::et::VectorXpr<XprT>& right)                           \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            LitT, XprT,                                                  \
            cml::et:: _OpT_ <                                            \
                typename cml::et::ExprTraits<LitT>::value_type,          \
                typename XprT::value_type>                               \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right.expression()));    \
}



/* Now, create the operators.  The combinations are:
 *
 * Unary expressions:
 *
 * op Vector -> Vector
 * op VecXpr -> Vector
 *
 *
 * Binary expressions:
 *
 * Literal op Vector -> Vector
 * Vector op Literal -> Vector
 *
 * Literal op VecXpr -> VecXpr
 * VecXpr op Literal -> VecXpr
 *
 * Vector op VecXpr -> VecXpr
 * VecXpr op Vector -> VecXpr
 *
 * Vector op Vector -> Vector
 * VecXpr op VecXpr -> VecXpr
 */

CML_VEC_UNIOP(operator+, OpPos)
CML_VEC_UNIOP(operator-, OpNeg)

CML_VECXPR_UNIOP(operator+, OpPos)
CML_VECXPR_UNIOP(operator-, OpNeg)

CML_VEC_VEC_BINOP(operator+, OpAdd)
CML_VEC_VEC_BINOP(operator-, OpSub)

CML_VECXPR_VEC_BINOP(operator+, OpAdd)
CML_VECXPR_VEC_BINOP(operator-, OpSub)

CML_VEC_VECXPR_BINOP(operator+, OpAdd)
CML_VEC_VECXPR_BINOP(operator-, OpSub)

CML_VECXPR_VECXPR_BINOP(operator+, OpAdd)
CML_VECXPR_VECXPR_BINOP(operator-, OpSub)

CML_VEC_LIT_BINOP(operator*, OpMul)
CML_VEC_LIT_BINOP(operator/, OpDiv)

CML_LIT_VEC_BINOP(operator*, OpMul)

CML_VECXPR_LIT_BINOP(operator*, OpMul)
CML_VECXPR_LIT_BINOP(operator/, OpDiv)

CML_LIT_VECXPR_BINOP(operator*, OpMul)

} // vector_ops
} // cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
