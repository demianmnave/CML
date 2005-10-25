/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef ops_h
#define ops_h

#include <cml/et/traits.h>

namespace cml {
namespace et {

/** Declare a unary scalar operator, like negation. */
#define CML_UNARY_SCALAR_OP(_op_, _name_)                               \
template<typename ArgT> struct _name_ {                                 \
    typedef ExprTraits<ArgT> arg_traits;                                \
    typedef typename arg_traits::const_reference arg_reference;         \
    typedef typename arg_traits::value_type value_type;                 \
    value_type apply(arg_reference arg) const { return _op_ arg; }      \
};

/** Declare a binary scalar operator, like addition, s1+s2.
 *
 * @bug This still needs a proper type promotion to specify value_type as
 * the proper resulting type of applying _op_ to the two argument.  e.g.
 * int + double yields double, but the result is int (LeftT) right now.
 */
#define CML_BINARY_SCALAR_OP(_op_, _name_)                               \
template<typename LeftT, typename RightT> struct _name_ {                \
    typedef ExprTraits<LeftT> left_traits;                               \
    typedef ExprTraits<RightT> right_traits;                             \
    typedef typename left_traits::const_reference left_reference;        \
    typedef typename right_traits::const_reference right_reference;      \
    typedef typename left_traits::value_type value_type;                 \
    value_type apply(left_reference left, right_reference right) const { \
        return left _op_ right; }                                        \
};

/** Declare an op-assignment operator.
 *
 * @note The ExprTraits for both argument types must be defined, LeftT must
 * have an assignment operator, and ExprTraits<LeftT>::reference must specify
 * a type that allows assignment.
 *
 * @bug This still needs a proper type promotion to specify value_type as the
 * proper resulting type of applying _op_ to the two argument.  e.g.  int +=
 * double should yield double, but the result is int (LefT) right now.
 */
#define CML_BINARY_SCALAR_OP_ASSIGN(_op_, _name_)                        \
template<typename LeftT, typename RightT> struct _name_ {                \
    typedef ExprTraits<LeftT> left_traits;                               \
    typedef ExprTraits<RightT> right_traits;                             \
    typedef typename left_traits::reference left_reference;              \
    typedef typename right_traits::const_reference right_reference;      \
    typedef typename left_traits::value_type value_type;                 \
    value_type apply(left_reference left, right_reference right) const { \
        return left _op_ right; }                                        \
};


/* Define the operators: */

/* Unary scalar ops: */
CML_UNARY_SCALAR_OP(-, OpNeg)
CML_UNARY_SCALAR_OP(+, OpPos)

/* Binary scalar ops: */
CML_BINARY_SCALAR_OP(+, OpAdd)
CML_BINARY_SCALAR_OP(-, OpSub)
CML_BINARY_SCALAR_OP(*, OpMul)
CML_BINARY_SCALAR_OP(/, OpDiv)

/* Binary scalar op-assigns: */
CML_BINARY_SCALAR_OP_ASSIGN(=, OpAssign)
CML_BINARY_SCALAR_OP_ASSIGN(+=, OpAddAssign)
CML_BINARY_SCALAR_OP_ASSIGN(-=, OpSubAssign)
CML_BINARY_SCALAR_OP_ASSIGN(*=, OpMulAssign)
CML_BINARY_SCALAR_OP_ASSIGN(/=, OpDivAssign)

#undef CML_UNARY_SCALAR_OP
#undef CML_BINARY_SCALAR_OP
#undef CML_BINARY_SCALAR_OP_ASSIGN

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
