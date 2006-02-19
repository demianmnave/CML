/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>
#include <cml/fixed.h>          // For cml::fixed<>
#include <cml/vector.h>

/* For convenience: */
using std::cerr;
using std::endl;
using namespace cml;

typedef vector< double, fixed<4>, col_vector > vector_d4;
#define VECINIT(_v_) _v_

#include "print_vector.cpp"
#include "vector_algebra1.cpp"
#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
