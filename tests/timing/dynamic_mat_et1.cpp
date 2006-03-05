/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#define CML_ENABLE_MATRIX_BRACES // for operator[][] to load/print a matrix

#include <iostream>
#include <cml/dynamic.h>
#include <cml/matrix.h>

using namespace cml::matrix_ops;

/* For convenience: */
using std::cerr;
using std::endl;

using cml::dynamic;
typedef cml::matrix< double, dynamic<> > matrix_d44;
#define MATINIT(_m_) _m_(4,4)

#include "print_matrix.cpp"
#include "matrix_algebra1.cpp"
#include "matrix_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
