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

using namespace cml;

/* Define the vector orientation to assume: */
typedef col_vector vector_orient;

/* 3-space column vector, fixed length, double coordinates: */
typedef vector< double, fixed<3>, vector_orient> vector_d3;

int main()
{
    vector_d3 u, v;
    cout << "dot(u,v) = " << dot(T(u),v) << endl;
    cout << "dot(u,u) = " << dot(T(u),u) << endl;
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
