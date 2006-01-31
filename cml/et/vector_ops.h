/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines the various combinations of vector expressions.
 *
 * @todo Allow operators on vectors with different element types, and
 * eventually between vectors of different storage types also.
 */

#ifndef vector_ops_h
#define vector_ops_h

#include <cml/et/scalar_ops.h>
#include <cml/et/scalar_promotions.h>
#include <cml/et/vector_expr.h>

namespace cml {
namespace vector_ops {

/** Declare a unary operator taking a cml::vector operand. */
#define CML_VEC_UNIOP(_op_, _OpT_)                                       \
template<typename E, class AT>                                           \
inline cml::et::VectorXpr<                                               \
    cml::et::UnaryVectorOp< cml::vector<E,AT>, _OpT_ <E> >               \
>                                                                        \
                                                                         \
_op_ (const cml::vector<E,AT>& arg)                                      \
{                                                                        \
    typedef cml::et::UnaryVectorOp<                                      \
            cml::vector<E,AT>, _OpT_ <E>                                 \
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
    cml::et::UnaryVectorOp< XprT, _OpT_ <typename XprT::value_type> >    \
>                                                                        \
                                                                         \
_op_ (const cml::et::VectorXpr<XprT>& arg)                               \
{                                                                        \
    typedef cml::et::UnaryVectorOp<                                      \
        XprT, _OpT_ <typename XprT::value_type>                          \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(arg.expression()));           \
}


/** Declare an operator taking two cml::vector operands.
 *
 * The vectors must have the same type (for now).
 */
#define CML_VEC_VEC_BINOP(_op_, _OpT_)                                   \
template<typename E, class AT>                                           \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        cml::vector<E,AT>, cml::vector<E,AT>, _OpT_ <E,E>                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            cml::vector<E,AT>, cml::vector<E,AT>, _OpT_ <E,E>            \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}


/** Declare an operator taking a cml::vector and a cml::et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorOp.
 */
#define CML_VEC_VECXPR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, class XprT>                               \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        cml::vector<E,AT>, XprT, _OpT_ <E, typename XprT::value_type>    \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::et::VectorXpr<XprT>& right)                           \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            cml::vector<E,AT>, XprT,                                     \
            _OpT_ <E, typename XprT::value_type>                         \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right.expression()));    \
}


/** Declare an operator taking a cml::et::VectorXpr and a cml::vector.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression.  The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the left subexpression of the BinaryVectorOp.
 */
#define CML_VECXPR_VEC_BINOP(_op_, _OpT_)                                \
template<class XprT, typename E, class AT>                               \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        XprT, cml::vector<E,AT>, _OpT_ <typename XprT::value_type, E>    \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT>& left,                            \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            XprT, cml::vector<E,AT>,                                     \
            _OpT_ <typename XprT::value_type, E>                         \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left.expression(),right));    \
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
        _OpT_ <                                                          \
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
            _OpT_ <                                                      \
                typename XprT1::value_type,                              \
                typename XprT2::value_type>                              \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(                                    \
            ExprT(left.expression(),right.expression()));                \
}


/** Declare an operator taking a cml::vector and a scalar. */
#define CML_VEC_SCALAR_BINOP(_op_, _OpT_)                                \
template<typename E, class AT, typename ScalarT>                         \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        cml::vector<E,AT>, ScalarT, _OpT_ <E,ScalarT>                    \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const ScalarT& right)                                            \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            cml::vector<E,AT>, ScalarT, _OpT_ <E,ScalarT>                \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}


/** Declare an operator taking a scalar and a cml::vector. */
#define CML_SCALAR_VEC_BINOP(_op_, _OpT_)                                \
template<typename ScalarT, typename E, class AT>                         \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        ScalarT, cml::vector<E,AT>, _OpT_ <ScalarT,E>                    \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const ScalarT& left,                                             \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            ScalarT, cml::vector<E,AT>,                                  \
            _OpT_ <ScalarT,E>                                            \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}


/** Declare an operator taking a cml::et::VectorXpr and a scalar.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression. The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the left subexpression of the BinaryVectorOp.
 */
#define CML_VECXPR_SCALAR_BINOP(_op_, _OpT_)                             \
template<class XprT, typename ScalarT>                                   \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT>& left,                            \
        const ScalarT& right)                                            \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>     \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left.expression(),right));    \
}


/** Declare an operator taking a scalar and a cml::et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorOp subexpression. The
 * parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorOp.
 */
#define CML_SCALAR_VECXPR_BINOP(_op_, _OpT_)                             \
template<typename ScalarT, class XprT>                                   \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorOp<                                             \
        ScalarT, XprT, _OpT_ <ScalarT, typename XprT::value_type>        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const ScalarT& left,                                             \
        const cml::et::VectorXpr<XprT>& right)                           \
{                                                                        \
    typedef cml::et::BinaryVectorOp<                                     \
            ScalarT, XprT,                                               \
            _OpT_ <ScalarT, typename XprT::value_type>                   \
        > ExprT;                                                         \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right.expression()));    \
}


#if 1
/* XXX These return a value, unlike the ones that return an expression node
 * below.  It's not quite obvious how to allow both, so that e.g. dot() can
 * be used outside of an expression tree...  but, this works for now.
 */

/** Declare a reduction taking two cml::vector operands.
 *
 * The vectors must have the same type (for now).
 */
#define CML_VEC_VEC_BIN_REDOP(_op_, _OpT_, _ReduceT_)                    \
template<typename E, class AT>                                           \
inline typename _ReduceT_<                                               \
            typename _OpT_ <E,E>::value_type,                            \
            typename _OpT_ <E,E>::value_type                             \
        >::value_type                                                    \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef _OpT_ <E,E> OpT;                                             \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
           > ReduceT;                                                    \
    typedef cml::et::BinaryVectorReductionOp<                            \
        cml::vector<E,AT>, cml::vector<E,AT>, OpT, ReduceT               \
    > ExprT;                                                             \
    return ExprT(left,right)();                                          \
}


/** Declare a reduction taking a cml::vector and a cml::et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorReductionOp subexpression.
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorReductionOp.
 */
#define CML_VEC_VECXPR_BIN_REDOP(_op_, _OpT_, _ReduceT_)                 \
template<typename E, class AT, typename XprT>                            \
inline typename _ReduceT_<                                               \
            typename _OpT_ <E, typename XprT::value_type>::value_type,   \
            typename _OpT_ <E, typename XprT::value_type>::value_type    \
        >::value_type                                                    \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::et::VectorXpr<XprT>& right)                           \
{                                                                        \
    typedef _OpT_ <E, typename XprT::value_type> OpT;                    \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
               > ReduceT;                                                \
    typedef cml::et::BinaryVectorReductionOp<                            \
        cml::vector<E,AT>, XprT, OpT, ReduceT                            \
    > ExprT;                                                             \
    return ExprT(left,right.expression())();                             \
}


/** Declare a reduction taking a cml::et::VectorXpr and a cml::vector.
 *
 * The resulting VectorXpr has a BinaryVectorReductionOp subexpression.
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorReductionOp.
 */
#define CML_VECXPR_VEC_BIN_REDOP(_op_, _OpT_, _ReduceT_)                 \
template<typename XprT, typename E, class AT>                            \
inline typename _ReduceT_<                                               \
            typename _OpT_ <typename XprT::value_type,E>::value_type,    \
            typename _OpT_ <typename XprT::value_type,E>::value_type     \
        >::value_type                                                    \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT>& left,                            \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef _OpT_ <E, typename XprT::value_type> OpT;                    \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
               > ReduceT;                                                \
    typedef cml::et::BinaryVectorReductionOp<                            \
        XprT, cml::vector<E,AT>, OpT, ReduceT                            \
    > ExprT;                                                             \
    return ExprT(left.expression(),right)();                             \
}


/** Declare an operator taking two cml::et::VectorXpr operands.
 *
 * The resulting VectorXpr has a BinaryVectorReductionOp subexpression.
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpressions of the BinaryVectorOp.
 */
#define CML_VECXPR_VECXPR_BIN_REDOP(_op_, _OpT_, _ReduceT_)              \
template<class XprT1, class XprT2>                                       \
inline typename _ReduceT_<                                               \
            typename _OpT_ <                                             \
               typename XprT1::value_type,                               \
               typename XprT2::value_type                                \
            >::value_type,                                               \
            typename _OpT_ <                                             \
               typename XprT1::value_type,                               \
               typename XprT2::value_type                                \
            >::value_type                                                \
        >::value_type                                                    \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT1>& left,                           \
        const cml::et::VectorXpr<XprT2>& right)                          \
{                                                                        \
    typedef _OpT_ <                                                      \
                typename XprT1::value_type,                              \
                typename XprT2::value_type                               \
               > OpT;                                                    \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
               > ReduceT;                                                \
    typedef cml::et::BinaryVectorReductionOp<                            \
        XprT1, XprT2, OpT, ReduceT                                       \
    > ExprT;                                                             \
    return ExprT(left.expression(),right.expression())();                \
}

#else
/* XXX These return operator classes, but some reductions (like dot())
 * should be able to be used outside of the expression template
 * infrastructure.
 */
/** Declare a reduction taking two cml::vector operands.
 *
 * The vectors must have the same type (for now).
 */
#define CML_VEC_VEC_BIN_REDOP(_op_, _OpT_, _ReduceT_)                    \
template<typename E, class AT>                                           \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorReductionOp<                                    \
        cml::vector<E,AT>, cml::vector<E,AT>,                            \
        _OpT_ <E,E>,                                                     \
        _ReduceT_<                                                       \
            typename _OpT_ <E,E>::value_type,                            \
            typename _OpT_ <E,E>::value_type                             \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef _OpT_ <E,E> OpT;                                             \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
           > ReduceT;                                                    \
    typedef cml::et::BinaryVectorReductionOp<                            \
        cml::vector<E,AT>, cml::vector<E,AT>, OpT, ReduceT               \
    > ExprT;                                                             \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}


/** Declare a reduction taking a cml::vector and a cml::et::VectorXpr.
 *
 * The resulting VectorXpr has a BinaryVectorReductionOp subexpression.
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorReductionOp.
 */
#define CML_VEC_VECXPR_BIN_REDOP(_op_, _OpT_, _ReduceT_)                 \
template<typename E, class AT, typename XprT>                            \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorReductionOp<                                    \
        cml::vector<E,AT>, XprT,                                         \
        _OpT_ <E, typename XprT::value_type>,                            \
        _ReduceT_<                                                       \
            typename _OpT_ <E, typename XprT::value_type>::value_type,   \
            typename _OpT_ <E, typename XprT::value_type>::value_type    \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::vector<E,AT>& left,                                   \
        const cml::et::VectorXpr<XprT>& right)                           \
{                                                                        \
    typedef _OpT_ <E, typename XprT::value_type> OpT;                    \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
               > ReduceT;                                                \
    typedef cml::et::BinaryVectorReductionOp<                            \
        cml::vector<E,AT>, XprT, OpT, ReduceT                            \
    > ExprT;                                                             \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}


/** Declare a reduction taking a cml::et::VectorXpr and a cml::vector.
 *
 * The resulting VectorXpr has a BinaryVectorReductionOp subexpression.
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the right subexpression of the BinaryVectorReductionOp.
 */
#define CML_VECXPR_VEC_BIN_REDOP(_op_, _OpT_, _ReduceT_)                 \
template<typename XprT, typename E, class AT>                            \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorReductionOp<                                    \
        XprT, cml::vector<E,AT>,                                         \
        _OpT_ <typename XprT::value_type,E>,                             \
        _ReduceT_<                                                       \
            typename _OpT_ <typename XprT::value_type,E>::value_type,    \
            typename _OpT_ <typename XprT::value_type,E>::value_type     \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT>& left,                            \
        const cml::vector<E,AT>& right)                                  \
{                                                                        \
    typedef _OpT_ <E, typename XprT::value_type> OpT;                    \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
               > ReduceT;                                                \
    typedef cml::et::BinaryVectorReductionOp<                            \
        XprT, cml::vector<E,AT>, OpT, ReduceT                            \
    > ExprT;                                                             \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}


/** Declare an operator taking two cml::et::VectorXpr operands.
 *
 * The resulting VectorXpr has a BinaryVectorReductionOp subexpression.
 * The parse tree is automatically compressed by hoisting the VectorXpr's
 * subexpression into the subexpressions of the BinaryVectorOp.
 */
#define CML_VECXPR_VECXPR_BIN_REDOP(_op_, _OpT_, _ReduceT_)              \
template<class XprT1, class XprT2>                                       \
inline cml::et::VectorXpr<                                               \
    cml::et::BinaryVectorReductionOp<                                    \
        XprT1, XprT2,                                                    \
        _OpT_ <                                                          \
            typename XprT1::value_type,                                  \
            typename XprT2::value_type                                   \
        >,                                                               \
        _ReduceT_<                                                       \
            typename _OpT_ <                                             \
               typename XprT1::value_type,                               \
               typename XprT2::value_type                                \
            >::value_type,                                               \
            typename _OpT_ <                                             \
               typename XprT1::value_type,                               \
               typename XprT2::value_type                                \
            >::value_type                                                \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const cml::et::VectorXpr<XprT1>& left,                           \
        const cml::et::VectorXpr<XprT2>& right)                          \
{                                                                        \
    typedef _OpT_ <                                                      \
                typename XprT1::value_type,                              \
                typename XprT2::value_type                               \
               > OpT;                                                    \
    typedef _ReduceT_ <                                                  \
                typename OpT::value_type,                                \
                typename OpT::value_type                                 \
               > ReduceT;                                                \
    typedef cml::et::BinaryVectorReductionOp<                            \
        XprT1, XprT2, OpT, ReduceT                                       \
    > ExprT;                                                             \
    return cml::et::VectorXpr<ExprT>(ExprT(left,right));                 \
}

#endif



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
 * Scalar op Vector -> Vector
 * Vector op Scalar -> Vector
 *
 * Scalar op VecXpr -> VecXpr
 * VecXpr op Scalar -> VecXpr
 *
 * Vector op VecXpr -> VecXpr
 * VecXpr op Vector -> VecXpr
 *
 * Vector op Vector -> Vector
 * VecXpr op VecXpr -> VecXpr
 *
 * Binary reductions:
 *
 * Vector (op,op) Vector -> Scalar
 * VecXpr (op,op) Vector -> Scalar
 * Vector (op,op) VecXpr -> Scalar
 * VecXpr (op,op) VecXpr -> Scalar
 */

CML_VEC_UNIOP(operator+, cml::et::OpPos)
CML_VECXPR_UNIOP(operator+, cml::et::OpPos)

CML_VEC_UNIOP(operator-, cml::et::OpNeg)
CML_VECXPR_UNIOP(operator-, cml::et::OpNeg)

CML_VEC_VEC_BINOP(operator+, cml::et::OpAdd)
CML_VECXPR_VEC_BINOP(operator+, cml::et::OpAdd)
CML_VEC_VECXPR_BINOP(operator+, cml::et::OpAdd)
CML_VECXPR_VECXPR_BINOP(operator+, cml::et::OpAdd)

CML_VEC_VEC_BINOP(operator-, cml::et::OpSub)
CML_VECXPR_VEC_BINOP(operator-, cml::et::OpSub)
CML_VEC_VECXPR_BINOP(operator-, cml::et::OpSub)
CML_VECXPR_VECXPR_BINOP(operator-, cml::et::OpSub)

CML_VEC_SCALAR_BINOP(operator*, cml::et::OpMul)
CML_SCALAR_VEC_BINOP(operator*, cml::et::OpMul)
CML_VECXPR_SCALAR_BINOP(operator*, cml::et::OpMul)
CML_SCALAR_VECXPR_BINOP(operator*, cml::et::OpMul)

CML_VEC_SCALAR_BINOP(operator/, cml::et::OpDiv)
CML_VECXPR_SCALAR_BINOP(operator/, cml::et::OpDiv)

/* Dot-product reduction operator, dot(V1,V2): */
CML_VEC_VEC_BIN_REDOP(dot, cml::et::OpMul, cml::et::OpAdd)
CML_VECXPR_VEC_BIN_REDOP(dot, cml::et::OpMul, cml::et::OpAdd)
CML_VEC_VECXPR_BIN_REDOP(dot, cml::et::OpMul, cml::et::OpAdd)
CML_VECXPR_VECXPR_BIN_REDOP(dot, cml::et::OpMul, cml::et::OpAdd)

#undef CML_VEC_UNIOP
#undef CML_VECXPR_UNIOP
#undef CML_VEC_VEC_BINOP
#undef CML_VECXPR_VEC_BINOP
#undef CML_VEC_VECXPR_BINOP
#undef CML_VECXPR_VECXPR_BINOP
#undef CML_VEC_SCALAR_BINOP
#undef CML_SCALAR_VEC_BINOP
#undef CML_VECXPR_SCALAR_BINOP
#undef CML_SCALAR_VECXPR_BINOP
#undef CML_VEC_VEC_BIN_REDOP
#undef CML_VEC_VECXPR_BIN_REDOP
#undef CML_VECXPR_VEC_BIN_REDOP
#undef CML_VECXPR_VECXPR_BIN_REDOP

} // vector_ops
} // cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
