/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines matrix operators.
 */
#ifndef matrix_ops_h
#define matrix_ops_h

#include <cml/et/scalar_ops.h>
#include <cml/matrix/matrix_expr.h>
#include <cml/matrix/matop_macros.h>

#if defined(CML_MATRIX_OPERATORS_REQUIRE_INLINE)
#define inline_         inline
#else
#define inline_
#endif

namespace cml {

CML_MAT_UNIOP(    operator+, et::OpPos)
CML_MATXPR_UNIOP( operator+, et::OpPos)

CML_MAT_UNIOP(    operator-, et::OpNeg)
CML_MATXPR_UNIOP( operator-, et::OpNeg)

CML_MAT_MAT_BINOP(       operator+, et::OpAdd)
CML_MATXPR_MAT_BINOP(    operator+, et::OpAdd)
CML_MAT_MATXPR_BINOP(    operator+, et::OpAdd)
CML_MATXPR_MATXPR_BINOP( operator+, et::OpAdd)

CML_MAT_MAT_BINOP(       operator-, et::OpSub)
CML_MATXPR_MAT_BINOP(    operator-, et::OpSub)
CML_MAT_MATXPR_BINOP(    operator-, et::OpSub)
CML_MATXPR_MATXPR_BINOP( operator-, et::OpSub)

CML_MAT_SCALAR_BINOP(    operator*, et::OpMul)
CML_SCALAR_MAT_BINOP(    operator*, et::OpMul)
CML_MATXPR_SCALAR_BINOP( operator*, et::OpMul)
CML_SCALAR_MATXPR_BINOP( operator*, et::OpMul)

CML_MAT_SCALAR_BINOP(    operator/, et::OpDiv)
CML_MATXPR_SCALAR_BINOP( operator/, et::OpDiv)

} // namespace cml

/* Cleanup: */
#undef inline_

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
