/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include "cml_config.h"         // Must be first!

#include <iostream>
#include <cml/fixed.h>          // For cml::fixed<>
#include <cml/vector.h>

using std::cout;
using std::endl;

/* 3-space column vector, fixed length, double coordinates: */
typedef cml::vector< double, cml::fixed<3>, cml::col_vector> vector_d3;

int main()
{
    vector_d3 u,v;
    cout << "dot(u,v) = " << cml::dot(u,v) << endl;
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
