/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines matrix operators.
 */
#ifndef matrix_ops_h
#define matrix_ops_h

#include <cml/matrix/matop_macros.h>
#include <cml/matrix/matrix_transpose.h>
#include <cml/matrix/matrix_rowcol.h>

namespace cml {

/* Place matrix operators into a separate namespace: */
namespace matrix_ops {

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

} // namespace matrix_ops
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
