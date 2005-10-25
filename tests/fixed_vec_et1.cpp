/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include <iostream>
#include <cml/fixed.h>
#include <cml/vector.h>

/* For convenience: */
using std::cerr;
using std::endl;

/* Pull vector ops into the global namespace: */
using namespace cml::vector_ops;

using cml::fixed;
typedef cml::vector< double, fixed<4> > vector_d4;
#define VECINIT(_v_) _v_

#include "print_vector.cpp"
#include "vector_algebra1.cpp"
#include "vector_main1.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
