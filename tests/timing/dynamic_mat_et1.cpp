/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#define CML_ENABLE_MATRIX_BRACES // for operator[][] to load/print a matrix

#include <iostream>
#include <cml/cml.h>

using namespace cml;

/* For convenience: */
using std::cerr;
using std::endl;

typedef matrix<double, dynamic<>, cml::col_basis> matrix_d44;
#define MATINIT(_m_) _m_(4,4)

#include "print_matrix.cpp"
#include "matrix_algebra1.cpp"
#include "matrix_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
