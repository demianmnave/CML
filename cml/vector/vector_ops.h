/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines vector operators.
 */

#ifndef vector_ops_h
#define vector_ops_h

#include <cml/et/scalar_ops.h>
#include <cml/vector/vector_expr.h>
#include <cml/vector/vecop_macros.h>

#if defined(CML_VECTOR_OPERATORS_REQUIRE_INLINE)
#define inline_         inline
#else
#define inline_
#endif

namespace cml {

CML_VEC_UNIOP(    operator+, et::OpPos)
CML_VECXPR_UNIOP( operator+, et::OpPos)

CML_VEC_UNIOP(    operator-, et::OpNeg)
CML_VECXPR_UNIOP( operator-, et::OpNeg)

CML_VEC_VEC_BINOP(       operator+, et::OpAdd)
CML_VECXPR_VEC_BINOP(    operator+, et::OpAdd)
CML_VEC_VECXPR_BINOP(    operator+, et::OpAdd)
CML_VECXPR_VECXPR_BINOP( operator+, et::OpAdd)

CML_VEC_VEC_BINOP(       operator-, et::OpSub)
CML_VECXPR_VEC_BINOP(    operator-, et::OpSub)
CML_VEC_VECXPR_BINOP(    operator-, et::OpSub)
CML_VECXPR_VECXPR_BINOP( operator-, et::OpSub)

CML_VEC_SCALAR_BINOP(    operator*, et::OpMul)
CML_SCALAR_VEC_BINOP(    operator*, et::OpMul)
CML_VECXPR_SCALAR_BINOP( operator*, et::OpMul)
CML_SCALAR_VECXPR_BINOP( operator*, et::OpMul)

CML_VEC_SCALAR_BINOP(    operator/, et::OpDiv)
CML_VECXPR_SCALAR_BINOP( operator/, et::OpDiv)

} // namespace cml

/* Cleanup: */
#undef inline_

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
