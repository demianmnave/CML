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
using cml::fixed;
using namespace cml::vector_ops;

/* Define the vector orientation to assume: */
typedef cml::col_vector vector_orient;

typedef cml::vector< double, fixed<4>, vector_orient> vector_d4;
#define VECINIT(_v_) _v_

#include "print_vector.cpp"
#include "vector_algebra2.cpp"
#include "vector_main2.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
