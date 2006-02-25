/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>
#include <cml/vector.h>

/* For convenience: */
using std::cerr;
using std::endl;
using cml::external;
using namespace cml::vector_ops;

/* Define the vector orientation to assume: */
typedef cml::col_vector vector_orient;

typedef cml::vector< double, external<4>, vector_orient> vector_d4;

#define VECINIT(_v_) _v_(c_v[c_i++])

#include "print_vector.cpp"
#include "vector_algebra1.cpp"
#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
