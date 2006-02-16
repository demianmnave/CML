/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include "cml_config.h"
#include <iostream>
#include <cml/fixed.h>          // For cml::fixed<>
#include <cml/vector.h>

/* 3-space vector, fixed length, double coordinates: */
typedef cml::vector< double, cml::fixed<3> > vector_d3;

int main()
{
    vector_d3 v;
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
