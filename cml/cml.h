/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Bring CML public namespaces into namespace CML.
 *
 * @todo Finish tests for mat-vec multiply, and enable inlining as
 * necessary.
 *
 * @todo Differentiate between references used for function arguments, and
 * those used for variable types.  In particular, GCC 3.4 requires const T &
 * function arguments to ensure complete unrolling/inlining of expressions.
 *
 * @todo Specialize matrix multiplication based upon the size type (fixed or
 * dynamic).  This makes a difference for at least GCC 3.4.
 *
 * @todo operator*=() for matrices (right-hand side needs to be expression
 * with same size as target matrix).
 *
 * @todo verify on Windows
 *
 * @todo need a build system for the tests/ and examples/ directories.
 *
 * @todo clean up the testing infrastructure, and make it easier to add new
 * tests
 *
 * @todo figure out if scalars should be passed by value or reference, or
 * if it should be determined by traits
 *
 * @todo does it make sense to allow vector<> to look like matrix<> in
 * expressions?  e.g. by assigning array_rows and array_cols based upon
 * orientation, and by putting rows() and cols() methods into vector<> and
 * ExprTraits< vector<> >?
 *
 * @todo change use of typename, class to be like Alexandrescu book
 *
 * @todo figure out if it makes sense to unroll assignment if either the
 * source expression or the target vector/matrix has a fixed size (right
 * now, unrolling happens only if the target has a fixed size)
 *
 * @todo need intutive identity() function that doesn't cause already
 * allocated dynamic vectors to be resized.
 *
 * @todo fix/streamline header inclusion
 *
 * @todo how should derivation from vector<> and matrix<> be supported?  or
 * can it be supported at all in the current design?
 */

#ifndef cml_h
#define cml_h

#include <cml/vector.h>
#include <cml/matrix.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
