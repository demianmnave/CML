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
typedef cml::vector< double, dynamic<4> > vector_d4;
#define VECINIT(_v_) _v_

#include "print_vector.cpp"
#include "vector_algebra1.cpp"
#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
