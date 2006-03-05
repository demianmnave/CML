/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>
#include <cml/dynamic.h>
#include <cml/vector.h>

/* For convenience: */
using std::cerr;
using std::endl;
using cml::dynamic;
using namespace cml::vector_ops;

/* Define the vector orientation to assume: */
typedef cml::col_vector vector_orient;

typedef cml::vector< double, dynamic<>, vector_orient> vector_d4;
#define VECINIT(_v_) _v_(4)

#include "print_vector.cpp"
#include "vector_algebra2.cpp"
#include "vector_main2.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
