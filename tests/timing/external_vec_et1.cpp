/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>
#include <cml/cml.h>

/* For convenience: */
using std::cerr;
using std::endl;
using namespace cml;

typedef vector< double, external<4> > vector_d4;

#define VECINIT(_v_) _v_(c_v[c_i++])

#include "print_vector.cpp"
#include "vector_algebra1.cpp"
#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
