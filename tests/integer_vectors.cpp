/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#undef CML_NO_DEFAULT_EXPR_TRAITS
#include <typeinfo>
#include <iostream>
#include <cml/cml.h>

int main()
{
    using namespace cml;
    using cml::et::ScalarPromote;

    typedef cml::vector< unsigned int, fixed<2> > uivector_2;
    typedef cml::vector< int, fixed<2> > sivector_2;
    uivector_2 ui_v(1,2);
    sivector_2 si_w(-3,-2);

    /* The C promotion is to unsigned int, so z will have a big
     * coefficient 0 due to conversion (use ScalarPromote<> to get at the
     * type, just in case):
     */
    cml::vector< ScalarPromote<unsigned int,int>::type, fixed<2> >
        ui_z = ui_v + si_w;
    std::clog << "z (unsigned int) = " << ui_z << std::endl;

    /* This should print the right answer (-2,0): */
    sivector_2 si_v(1,2);
    cml::vector< ScalarPromote<int,int>::type, fixed<2> >
        si_z = si_v + si_w;
    std::clog << "z (int) = " << si_z << std::endl;

    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
