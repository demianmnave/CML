/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Defines vector operators.
 */

#ifndef vector_ops_h
#define vector_ops_h

#include <cml/et/vecop_macros.h>
#include <cml/et/vector_transpose.h>
#include <cml/vector_dot.h>

namespace cml {

/* Place vector operators into a separate namespace: */
namespace vector_ops {

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

} // namespace vector_ops
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
