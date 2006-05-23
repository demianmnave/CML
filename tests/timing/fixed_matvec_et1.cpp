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

typedef vector< double, fixed<4> > vector_d4;
#define VECINIT(_v_) _v_

typedef matrix<double, fixed<4,4>, cml::col_basis> matrix_d44;
#define MATINIT(_m_) _m_

#include "print_vector.cpp"
#include "print_matrix.cpp"
#include "matvec_algebra1.cpp"
#include "matvec_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
