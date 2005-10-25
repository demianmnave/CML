/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the various combinations of matrix expressions.
 *
 * @note Operator performance relies heavily upon the compiler's ability to
 * optimize away temporaries and to inline function calls.
 *
 * @todo Allow operators ASAP between matrices with different element
 * types, and eventually between matrices of different storage types also.
 */

#if !defined(cml_matrix_h)
#error "This should only be included from cml/matrix.h"
#else

#ifndef matrix_ops_h
#define matrix_ops_h

#include <cml/et/matrix_expr.h>
#include <cml/et/scalar_ops.h>

namespace cml {
namespace matrix_ops {

/** Declare a unary operator taking a cml::matrix operand.
 *
 * @note cml::et::ExprTraits must be defined for the matrix's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_MAT_LINEAR_UNIOP(_op_, _OpT_)                                   \
template<typename E, class AT, typename O>                               \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearUnaryMatrixOp<                                        \
        cml::matrix<E,AT,O>,                                             \
        cml::et:: _OpT_<typename cml::et::ExprTraits<E>::value_type>     \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (const cml::matrix<E,AT,O>& arg)                                    \
{                                                                        \
    typedef cml::et::LinearUnaryMatrixOp<                                \
            cml::matrix<E,AT,O>,                                         \
            cml::et:: _OpT_<typename cml::et::ExprTraits<E>::value_type> \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(arg));                        \
}

/** Declare a unary operator taking a cml::et::MatrixXpr operand.
 *
 * The resulting MatrixXpr has a LinearUnaryMatrixOp subexpression.  The
 * parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpression of the LinearUnaryMatrixOp.
 */
#define CML_MATXPR_LINEAR_UNIOP(_op_, _OpT_)                               \
template<class XprT>                                                     \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearUnaryMatrixOp<                                        \
        XprT, cml::et:: _OpT_<typename XprT::value_type>                 \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (const cml::et::MatrixXpr<XprT>& arg)                               \
{                                                                        \
    typedef cml::et::LinearUnaryMatrixOp<                                \
        XprT, cml::et:: _OpT_<typename XprT::value_type>                 \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(arg.expression()));           \
}

/** Declare an operator taking two cml::matrix operands.
 *
 * The matrices must have the same type (for now).
 *
 * @note cml::et::ExprTraits must be defined for the matrix's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_MAT_MAT_LINEAR_BINOP(_op_, _OpT_)                                   \
template<typename E, class AT, typename O>                               \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        cml::matrix<E,AT,O>, cml::matrix<E,AT,O>,                        \
        cml::et:: _OpT_<                                                 \
            typename cml::et::ExprTraits<E>::value_type,                 \
            typename cml::et::ExprTraits<E>::value_type                  \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::matrix<E,AT,O>& left,                                 \
        const cml::matrix<E,AT,O>& right)                                \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            cml::matrix<E,AT,O>, cml::matrix<E,AT,O>,                    \
            cml::et:: _OpT_<                                             \
                typename cml::et::ExprTraits<E>::value_type,             \
                typename cml::et::ExprTraits<E>::value_type>             \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left,right));                 \
}

/** Declare an operator taking a cml::et::MatrixXpr and a cml::matrix.
 *
 * The resulting MatrixXpr has a LinearBinaryMatrixOp subexpression.  The
 * parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the left subexpression of the LinearBinaryMatrixOp.
 *
 * @note cml::et::ExprTraits must be defined for the matrix's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_MATXPR_MAT_LINEAR_BINOP(_op_, _OpT_)                                \
template<class XprT, typename E, class AT, typename O>                   \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        XprT, cml::matrix<E,AT,O>,                                       \
        cml::et:: _OpT_ <                                                \
            typename XprT::value_type,                                   \
            typename cml::et::ExprTraits<E>::value_type                  \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::MatrixXpr<XprT>& left,                            \
        const cml::matrix<E,AT,O>& right)                                \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            XprT, cml::matrix<E,AT,O>,                                   \
            cml::et:: _OpT_ <                                            \
                typename XprT::value_type,                               \
                typename cml::et::ExprTraits<E>::value_type>             \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left.expression(),right));    \
}

/** Declare an operator taking a cml::matrix and a cml::et::MatrixXpr.
 *
 * The resulting MatrixXpr has a LinearBinaryMatrixOp subexpression.  The
 * parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the right subexpression of the LinearBinaryMatrixOp.
 *
 * @note cml::et::ExprTraits must be defined for the matrix's element type
 * if CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_MAT_MATXPR_LINEAR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, typename O, class XprT>                   \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        cml::matrix<E,AT,O>, XprT,                                       \
        cml::et:: _OpT_ <                                                \
            typename cml::et::ExprTraits<E>::value_type,                 \
            typename XprT::value_type                                    \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::matrix<E,AT,O>& left,                                 \
        const cml::et::MatrixXpr<XprT>& right)                           \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            cml::matrix<E,AT,O>, XprT,                                   \
            cml::et:: _OpT_ <                                            \
                typename cml::et::ExprTraits<E>::value_type,             \
                typename XprT::value_type>                               \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left,right.expression()));    \
}

/** Declare an operator taking two cml::et::MatrixXpr operands.
 *
 * The resulting MatrixXpr has a LinearBinaryMatrixOp subexpression.  The
 * parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the subexpressions of the LinearBinaryMatrixOp.
 */
#define CML_MATXPR_MATXPR_LINEAR_BINOP(_op_, _OpT_)                             \
template<class XprT1, class XprT2>                                       \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        XprT1, XprT2,                                                    \
        cml::et:: _OpT_ <                                                \
            typename XprT1::value_type,                                  \
            typename XprT2::value_type                                   \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::MatrixXpr<XprT1>& left,                           \
        const cml::et::MatrixXpr<XprT2>& right)                          \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            XprT1, XprT2,                                                \
            cml::et:: _OpT_ <                                            \
                typename XprT1::value_type,                              \
                typename XprT2::value_type>                              \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(                                    \
            ExprT(left.expression(),right.expression()));                \
}


/** Declare an operator taking a cml::matrix and a "literal".
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_MAT_LIT_LINEAR_BINOP(_op_, _OpT_)                                   \
template<typename E, class AT, typename O, typename LitT>                \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        cml::matrix<E,AT,O>, LitT,                                       \
        cml::et:: _OpT_<                                                 \
            typename cml::et::ExprTraits<E>::value_type,                 \
            typename cml::et::ExprTraits<LitT>::value_type>              \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::matrix<E,AT,O>& left,                                 \
        const LitT& right)                                               \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            cml::matrix<E,AT,O>, LitT,                                   \
            cml::et:: _OpT_ <                                            \
                typename cml::et::ExprTraits<E>::value_type,             \
                typename cml::et::ExprTraits<LitT>::value_type>          \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left,right));                 \
}

/** Declare an operator taking a "literal" and a cml::matrix.
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_LIT_MAT_LINEAR_BINOP(_op_, _OpT_)                                   \
template<typename LitT, typename E, class AT, typename O>                \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        LitT, cml::matrix<E,AT,O>,                                       \
        cml::et:: _OpT_<                                                 \
            typename cml::et::ExprTraits<LitT>::value_type,              \
            typename cml::et::ExprTraits<E>::value_type>                 \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const LitT& left,                                                \
        const cml::matrix<E,AT,O>& right)                                \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            LitT, cml::matrix<E,AT,O>,                                   \
            cml::et:: _OpT_<                                             \
                typename cml::et::ExprTraits<LitT>::value_type,          \
                typename cml::et::ExprTraits<E>::value_type>             \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left,right));                 \
}

/** Declare an operator taking a cml::et::MatrixXpr and a "literal"
 *
 * The resulting MatrixXpr has a LinearBinaryMatrixOp subexpression. The
 * parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the left subexpression of the LinearBinaryMatrixOp.
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_MATXPR_LIT_LINEAR_BINOP(_op_, _OpT_)                                \
template<class XprT, typename LitT>                                      \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
        XprT, LitT,                                                      \
        cml::et:: _OpT_ <                                                \
            typename XprT::value_type,                                   \
            typename cml::et::ExprTraits<LitT>::value_type               \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::MatrixXpr<XprT>& left,                            \
        const LitT& right)                                               \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            XprT, LitT,                                                  \
            cml::et:: _OpT_ <                                            \
                typename XprT::value_type,                               \
                typename cml::et::ExprTraits<LitT>::value_type>          \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left.expression(),right));    \
}

/** Declare an operator taking a "literal" and a cml::et::MatrixXpr.
 *
 * The resulting MatrixXpr has a LinearBinaryMatrixOp subexpression. The
 * parse tree is automatically compressed by hoisting the MatrixXpr's
 * subexpression into the right subexpression of the LinearBinaryMatrixOp.
 *
 * @note cml::et::ExprTraits must be defined for the literal if
 * CML_NO_DEFAULT_EXPR_TRAITS is defined.
 */
#define CML_LIT_MATXPR_LINEAR_BINOP(_op_, _OpT_)                                \
template<typename LitT, class XprT>                                      \
inline cml::et::MatrixXpr<                                               \
    cml::et::LinearBinaryMatrixOp<                                       \
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
        const cml::et::MatrixXpr<XprT>& right)                           \
{                                                                        \
    typedef cml::et::LinearBinaryMatrixOp<                               \
            LitT, XprT,                                                  \
            cml::et:: _OpT_ <                                            \
                typename cml::et::ExprTraits<LitT>::value_type,          \
                typename XprT::value_type>                               \
        > ExprT;                                                         \
    return cml::et::MatrixXpr<ExprT>(ExprT(left,right.expression()));    \
}



/* Now, create the operators.  The combinations are:
 *
 * Linear unary expressions (+,-):
 *
 * op Matrix
 * op MatXpr
 *
 *
 * Linear binary expressions (+,- for Mat/Mat, *,/ for Mat/Lit, * for Lit/Mat):
 *
 * Literal op Matrix
 * Matrix op Literal
 *
 * Literal op MatXpr
 * MatXpr op Literal
 *
 * Matrix op MatXpr
 * MatXpr op Matrix
 *
 * Matrix op Matrix
 * MatXpr op MatXpr
 */

CML_MAT_LINEAR_UNIOP(operator+, OpPos)
CML_MAT_LINEAR_UNIOP(operator-, OpNeg)

CML_MATXPR_LINEAR_UNIOP(operator+, OpPos)
CML_MATXPR_LINEAR_UNIOP(operator-, OpNeg)


CML_MAT_MAT_LINEAR_BINOP(operator+, OpAdd)
CML_MAT_MAT_LINEAR_BINOP(operator-, OpSub)

CML_MATXPR_MAT_LINEAR_BINOP(operator+, OpAdd)
CML_MATXPR_MAT_LINEAR_BINOP(operator-, OpSub)

CML_MAT_MATXPR_LINEAR_BINOP(operator+, OpAdd)
CML_MAT_MATXPR_LINEAR_BINOP(operator-, OpSub)

CML_MATXPR_MATXPR_LINEAR_BINOP(operator+, OpAdd)
CML_MATXPR_MATXPR_LINEAR_BINOP(operator-, OpSub)


CML_MAT_LIT_LINEAR_BINOP(operator*, OpMul)
CML_MAT_LIT_LINEAR_BINOP(operator/, OpDiv)

/* Lit '/' Matrix doesn't make sense, so it's not included here: */
CML_LIT_MAT_LINEAR_BINOP(operator*, OpMul)

CML_MATXPR_LIT_LINEAR_BINOP(operator*, OpMul)
CML_MATXPR_LIT_LINEAR_BINOP(operator/, OpDiv)

CML_LIT_MATXPR_LINEAR_BINOP(operator*, OpMul)

} // matrix_ops
} // cml

#endif
#endif // !defined(cml_matrix_h)

// -------------------------------------------------------------------------
// vim:ft=cpp
