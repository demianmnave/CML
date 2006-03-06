/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  The configurable matrix<> class.
 */

#ifndef cml_matrix_h
#define cml_matrix_h

#include <cml/matrix/fixed.h>
#include <cml/matrix/dynamic.h>
#include <cml/matrix/external.h>

#include <cml/matrix/matrix_transpose.h>
#include <cml/matrix/matrix_ops.h>
#include <cml/matrix/matrix_mul.h>

namespace cml {

/** A configurable matrix.
 *
 * This class encapsulates the notion of a matrix.  The ArrayType template
 * argument can be used to select the type of array to be used as internal
 * storage for a 2D arrayy of type Element.
 *
 * @internal Unlike the previous version, this uses specializations to better
 * enable varied array and matrix types. For example, with the rebind method,
 * it's difficult to support external<> matrix types that should not be
 * assigned to.
 *
 * @internal All assignments to the matrix should go through UnrollAssignment,
 * which ensures that the source expression and the destination matrix have
 * the same size.  This is particularly important for dynamically-sized
 * matrices.
 */
template<typename Element, class ArrayType,
    typename Layout = CML_DEFAULT_ARRAY_LAYOUT> class matrix;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
