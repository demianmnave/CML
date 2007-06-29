/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

//#undef NO_DEFAULT_EXPR_TRAITS
#include <iostream>
#include <cml/cml.h>

int main()
{
    using namespace cml;
    typedef cml::vector< unsigned, fixed<2> > ivector_2;
    ivector_2 v(1,2);
    v[0] = 1;
    v[1] = 2;
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
