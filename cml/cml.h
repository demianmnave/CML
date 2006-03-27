/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Bring CML public namespaces into namespace CML.
 *
 * @todo switch to ssize_t instead of size_t to avoid having to explicitly
 * deal with wrap-arounds to 2^32-1 when a size_t is subtracted from.
 *
 * @todo Make MatrixXpr<> and VectorXpr<> convertible to temporaries when a
 * value is required, but no left-hand matrix is provided; e.g. in 
 * cout << A+B << endl.
 *
 * @todo Finish tests for mat-vec multiply.
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
 * @todo change use of typename, class to be like Alexandrescu book
 *
 * @todo figure out if it makes sense to unroll assignment if either the
 * source expression or the target vector/matrix has a fixed size (right
 * now, unrolling happens only if the target has a fixed size)
 *
 * @todo need intutive identity() function that doesn't cause already
 * allocated dynamic vectors to be resized.
 *
 * @todo
 * assigning matrices and vectors [still not sure of good way]
 * identity()
 * general cross() for an (N-1)xN matrix
 * general cross() for (N-1) N-length vectors
 * vector<>::normalize()
 * vector<>::unit()
 * vector<>::magnitude2()  [or squared_length(), or whatever]
 * vector<>::magitude() [or length(), or whatever]
 * vector<>:: and matrix<>::fill()
 *
 * @todo Reduce the number of ExprTraits<> instances.  Most have the same
 * base types and methods.
 *
 * @todo Allow addition of new types, a la glommable ETs (but simpler).
 * Can use ideas from "SCOOP" method: Nicolas Burrus, Alexandre Duret-Lutz,
 * Thierry Géraud, David Lesage and Raphaël Poss. A Static C++
 * Object-Oriented Programming (SCOOP) Paradigm Mixing Benefits of
 * Traditional OOP and Generic Programming. In the Proceedings of the
 * Workshop on Multiple Paradigm with OO Languages (MPOOL'03) Anaheim, CA,
 * USA Oct. 2003
 */

#ifndef cml_h
#define cml_h

#include <cml/vector.h>
#include <cml/matrix.h>

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
