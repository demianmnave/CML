/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef scalar_promotions_h
#define scalar_promotions_h

#include <cml/core/cml_meta.h>

namespace cml {
namespace et {

template<class E1, class E2>
struct ScalarPromote
{
    typedef typename select_switch<
        type_pair<E1,E2>,

        /* Note: order is important here, since the first type_pair matched
         * is returned:
         */
        type_pair<long double,long double>,       long double,
        type_pair<long double,E2>,                long double,
        type_pair<E1,long double>,                long double,

        type_pair<double,double>,                 double,
        type_pair<double,E2>,                     double,
        type_pair<E1,double>,                     double,

        type_pair<float,float>,                   float,
        type_pair<float,E2>,                      float,
        type_pair<E1,float>,                      float,

        type_pair<unsigned long,unsigned long>,   unsigned long,
        type_pair<unsigned long,E2>,              unsigned long,
        type_pair<E1,unsigned long>,              unsigned long,

        type_pair<long,long>,                     long,
        type_pair<long,E2>,                       long,
        type_pair<E1,long>,                       long,

        /* Note: this works because a longer type would have been matched
         * already, so the any_type parameter has to be a shorter type.
         *
         * This case matches unsigned int to signed int, signed/unsigned
         * short, and signed/unsigned char:
         */
        type_pair<unsigned int,unsigned int>,     unsigned int,
        type_pair<unsigned int,E2>,               unsigned int,
        type_pair<E1,unsigned int>,               unsigned int,

        /* This case matches signed int to signed int, signed/unsigned
         * short, and signed/unsigned char:
         */
        type_pair<int,int>,                       int,
        type_pair<int,E2>,                        int,
        type_pair<E1,int>,                        int,

        /* This case matches unsigned short to signed/unsigned short, and
         * signed/unsigned char:
         */
        type_pair<unsigned short,unsigned short>, unsigned short,
        type_pair<unsigned short,E2>,             unsigned short,
        type_pair<E1,unsigned short>,             unsigned short,

        /* This case matches signed short to signed short, and
         * signed/unsigned char:
         */
        type_pair<short,short>,                   short,
        type_pair<short,E2>,                      short,
        type_pair<E1,short>,                      short,

        /* This case matches unsigned char to signed/unsigned char:
         */
        type_pair<unsigned char,unsigned char>,   unsigned char,
        type_pair<unsigned char,E2>,              unsigned char,
        type_pair<E1,unsigned char>,              unsigned char,

        /* This case matches signed char to signed char: */
        type_pair<char,char>,                     char,
        type_pair<char,E2>,                       char,
        type_pair<E1,char>,                       char
    >::result type;
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
