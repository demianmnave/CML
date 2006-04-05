/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Create unary and binary operators with macros.
 *
 * These macros work just like those in cml/quaternion/vecop_macros.h.
 */

#ifndef quatop_macros_h
#define quatop_macros_h

/** Declare a unary operator taking a quaternion operand. */
#define CML_QUAT_UNIOP(_op_, _OpT_)                                      \
template<typename VecT, typename OrderT>                                 \
inline et::QuaternionXpr<                                                \
    et::UnaryQuaternionOp< quaternion<VecT,OrderT>,                      \
    _OpT_ <typename VecT::value_type> >                                  \
>                                                                        \
                                                                         \
_op_ (const quaternion<VecT,OrderT>& arg)                                \
{                                                                        \
    typedef et::UnaryQuaternionOp<                                       \
            quaternion<VecT,OrderT>, _OpT_ <typename VecT::value_type>   \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(arg));                         \
}


/** Declare a unary operator taking a et::QuaternionXpr operand. */
#define CML_QUATXPR_UNIOP(_op_, _OpT_)                                   \
template<class XprT>                                                     \
inline et::QuaternionXpr<                                                \
    et::UnaryQuaternionOp< XprT, _OpT_ <typename XprT::value_type> >     \
>                                                                        \
                                                                         \
_op_ (QUATXPR_ARG_TYPE arg)                                              \
{                                                                        \
    typedef et::UnaryQuaternionOp<                                       \
        XprT, _OpT_ <typename XprT::value_type>                          \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(arg.expression()));            \
}


/** Declare an operator taking two quaternion operands. */
#define CML_QUAT_QUAT_BINOP(_op_, _OpT_)                                 \
template<typename VecT1, typename VecT2, typename OrderT>                \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        quaternion<VecT1,OrderT>, quaternion<VecT2,OrderT>,              \
        _OpT_ <typename VecT1::value_type,typename VecT2::value_type>    \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const quaternion<VecT1,OrderT>& left,                            \
        const quaternion<VecT2,OrderT>& right)                           \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            quaternion<VecT1,OrderT>, quaternion<VecT2,OrderT>,          \
            _OpT_ <typename VecT1::value_type,typename VecT2::value_type>\
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left,right));                  \
}


/** Declare an operator taking a quaternion and a et::QuaternionXpr. */
#define CML_QUAT_QUATXPR_BINOP(_op_, _OpT_)                              \
template<typename VecT, typename OrderT, class XprT>                     \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        quaternion<VecT,OrderT>, XprT,                                   \
        _OpT_ <typename VecT::value_type, typename XprT::value_type>     \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const quaternion<VecT,OrderT>& left,                             \
        QUATXPR_ARG_TYPE right)                                          \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            quaternion<VecT,OrderT>, XprT,                               \
            _OpT_ <typename VecT::value_type, typename XprT::value_type> \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left,right.expression()));     \
}


/** Declare an operator taking an et::QuaternionXpr and a quaternion. */
#define CML_QUATXPR_QUAT_BINOP(_op_, _OpT_)                              \
template<class XprT, typename VecT, typename OrderT>                     \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        XprT, quaternion<VecT,OrderT>,                                   \
        _OpT_ <typename XprT::value_type, typename VecT::value_type>     \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        QUATXPR_ARG_TYPE left,                                           \
        const quaternion<VecT,OrderT>& right)                            \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            XprT, quaternion<VecT,OrderT>,                               \
            _OpT_ <typename XprT::value_type, typename VecT::value_type> \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left.expression(),right));     \
}


/** Declare an operator taking two et::QuaternionXpr operands. */
#define CML_QUATXPR_QUATXPR_BINOP(_op_, _OpT_)                           \
template<class XprT1, class XprT2>                                       \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        XprT1, XprT2,                                                    \
        _OpT_ <                                                          \
            typename XprT1::value_type,                                  \
            typename XprT2::value_type                                   \
        >                                                                \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        QUATXPR_ARG_TYPE_N(1) left,                                      \
        QUATXPR_ARG_TYPE_N(2) right)                                     \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            XprT1, XprT2,                                                \
            _OpT_ <                                                      \
                typename XprT1::value_type,                              \
                typename XprT2::value_type>                              \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(                                     \
            ExprT(left.expression(),right.expression()));                \
}


/** Declare an operator taking a quaternion and a scalar. */
#define CML_QUAT_SCALAR_BINOP(_op_, _OpT_)                               \
template<typename VecT, typename OrderT, typename ScalarT>               \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        quaternion<VecT,OrderT>, ScalarT,                                \
        _OpT_ <typename VecT::value_type,ScalarT>                        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        const quaternion<VecT,OrderT>& left,                             \
        SCALAR_ARG_TYPE right)                                           \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            quaternion<VecT,OrderT>, ScalarT,                            \
           _OpT_ <typename VecT::value_type,ScalarT>                     \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left,right));                  \
}


/** Declare an operator taking a scalar and a quaternion. */
#define CML_SCALAR_QUAT_BINOP(_op_, _OpT_)                               \
template<typename ScalarT, typename VecT, typename OrderT>               \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        ScalarT, quaternion<VecT,OrderT>,                                \
        _OpT_ <ScalarT,typename VecT::value_type>                        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        SCALAR_ARG_TYPE left,                                            \
        const quaternion<VecT,OrderT>& right)                            \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            ScalarT, quaternion<VecT,OrderT>,                            \
        _OpT_ <ScalarT,typename VecT::value_type>                        \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left,right));                  \
}


/** Declare an operator taking a et::QuaternionXpr and a scalar. */
#define CML_QUATXPR_SCALAR_BINOP(_op_, _OpT_)                            \
template<class XprT, typename ScalarT>                                   \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>         \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        QUATXPR_ARG_TYPE left,                                           \
        SCALAR_ARG_TYPE right)                                           \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            XprT, ScalarT, _OpT_ <typename XprT::value_type,ScalarT>     \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left.expression(),right));     \
}


/** Declare an operator taking a scalar and a et::QuaternionXpr. */
#define CML_SCALAR_QUATXPR_BINOP(_op_, _OpT_)                            \
template<typename ScalarT, class XprT>                                   \
inline et::QuaternionXpr<                                                \
    et::BinaryQuaternionOp<                                              \
        ScalarT, XprT, _OpT_ <ScalarT, typename XprT::value_type>        \
    >                                                                    \
>                                                                        \
                                                                         \
_op_ (                                                                   \
        SCALAR_ARG_TYPE left,                                            \
        QUATXPR_ARG_TYPE right)                                          \
{                                                                        \
    typedef et::BinaryQuaternionOp<                                      \
            ScalarT, XprT,                                               \
            _OpT_ <ScalarT, typename XprT::value_type>                   \
        > ExprT;                                                         \
    return et::QuaternionXpr<ExprT>(ExprT(left,right.expression()));     \
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
