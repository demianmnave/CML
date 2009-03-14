/* -*- C++ -*- ------------------------------------------------------------
 
Copyright (c) 2007 Jesse Anders and Demian Nave http://cmldev.net/

The Configurable Math Library (CML) is distributed under the terms of the
Boost Software License, v1.0 (see cml/LICENSE for details).

 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef scalar_promotions_h
#define scalar_promotions_h

#include <complex>
#include <cml/core/cml_meta.h>

namespace cml {
namespace et {

// #define CML_USE_OLD_SCALAR_PROMOTIONS
#if !defined(CML_USE_OLD_SCALAR_PROMOTIONS)

/* The type promotion code below is a slightly modified version of:
 * http://ubiety.uwaterloo.ca/~tveldhui/papers/techniques/techniques01.html
 */
namespace detail {

template<class T>
struct precision_trait {
    enum { precisionRank = 0,
           knowPrecisionRank = 0 };
};

#define DECLARE_PRECISION(T,rank)             \
    template<>                                \
    struct precision_trait< T > {             \
        enum { precisionRank = rank,          \
           knowPrecisionRank = 1 };           \
    };

DECLARE_PRECISION(int,100)
DECLARE_PRECISION(unsigned int,200)
DECLARE_PRECISION(long,300)
DECLARE_PRECISION(unsigned long,400)

DECLARE_PRECISION(long long,425)
DECLARE_PRECISION(unsigned long long,475)

DECLARE_PRECISION(float,500)
DECLARE_PRECISION(double,600)
DECLARE_PRECISION(long double,700)
DECLARE_PRECISION(std::complex<float>,800)
DECLARE_PRECISION(std::complex<double>,900)
DECLARE_PRECISION(std::complex<long double>,1000)

template<class T>
struct autopromote_trait {
    typedef T T_numtype;
};

#define DECLARE_AUTOPROMOTE(T1,T2)        \
    template<>                            \
    struct autopromote_trait<T1> {        \
      typedef T2 T_numtype;               \
    };

// These are the odd cases where small integer types
// are automatically promoted to int or unsigned int for
// arithmetic.
DECLARE_AUTOPROMOTE(bool, int)
DECLARE_AUTOPROMOTE(char, int)
DECLARE_AUTOPROMOTE(unsigned char, int)
DECLARE_AUTOPROMOTE(short int, int)
DECLARE_AUTOPROMOTE(short unsigned int, unsigned int)

template<class T1, class T2, int promoteToT1>
struct promote2 {
    typedef T1 T_promote;
};

template<class T1, class T2>
struct promote2<T1,T2,0> {
    typedef T2 T_promote;
};

template<class T1_orig, class T2_orig>
struct promote_trait {
    // Handle promotion of small integers to int/unsigned int
    typedef typename autopromote_trait<T1_orig>::T_numtype T1;
    typedef typename autopromote_trait<T2_orig>::T_numtype T2;

    // True if T1 is higher ranked
    enum {
      T1IsBetter =
        precision_trait<T1>::precisionRank >
          precision_trait<T2>::precisionRank,

    // True if we know ranks for both T1 and T2
      knowBothRanks =
        precision_trait<T1>::knowPrecisionRank
      && precision_trait<T2>::knowPrecisionRank,

    // True if we know T1 but not T2
      knowT1butNotT2 =  precision_trait<T1>::knowPrecisionRank
        && !(precision_trait<T2>::knowPrecisionRank),

    // True if we know T2 but not T1
      knowT2butNotT1 =  precision_trait<T2>::knowPrecisionRank
        && !(precision_trait<T1>::knowPrecisionRank),

    // True if T1 is bigger than T2
      T1IsLarger = sizeof(T1) >= sizeof(T2),

    // We know T1 but not T2: true
    // We know T2 but not T1: false
    // Otherwise, if T1 is bigger than T2: true
      defaultPromotion = knowT1butNotT2 ? false :
         (knowT2butNotT1 ? true : T1IsLarger)
    };

    // If we have both ranks, then use them.
    // If we have only one rank, then use the unknown type.
    // If we have neither rank, then promote to the larger type.

    enum {
      promoteToT1 = (knowBothRanks ? T1IsBetter : defaultPromotion) 
                        ? 1 : 0
    };

    typedef typename promote2<T1,T2,promoteToT1>::T_promote T_promote;
};

} // namespace detail

/** Defers to detail::promote_trait<>. */
template<class E1, class E2> struct ScalarPromote
{
    typedef typename detail::promote_trait<E1,E2>::T_promote type;
};

#else

namespace detail {

/** @class IntPromote
 *  @brief Helper template to int-promote a type.
 */
template<class T> struct IntPromote
{
    /* Signed -> signed int, unsigned -> unsigned int: */
    typedef typename select_switch<T,
            unsigned char,                       unsigned int,
            unsigned short,                      unsigned int,
            signed char,                         int,
            char,                                int,
            short,                               int,
            T,                                   T
    >::result   result;
};

} // namespace detail

/** @class ScalarPromote
 *  @brief Template for compile-time type promotion via C promotion rules.
 */
template<class E1_in, class E2_in> struct ScalarPromote
{
    /* Integral-promote the types (if possible). */
    typedef typename detail::IntPromote<E1_in>::result  E1;
    typedef typename detail::IntPromote<E2_in>::result  E2;

    /* If sizeof(long) == sizeof(unsigned int), promote to unsigned long.
     * Otherwise, sizeof(long) > sizeof(int), so promote to long.
     */
    typedef typename select_if<sizeof(long) == sizeof(unsigned int),
            unsigned long,
            long
    >::result   uint_promotion;

    /* Do the selection on the promoted types: */
    typedef typename select_switch<
        type_pair<E1,E2>,

#if defined(CML_USE_LONG_DOUBLE)
        type_pair<long double,long double>,       long double,
        type_pair<long double,E2>,                long double,
        type_pair<E1,long double>,                long double,
#endif

        type_pair<double,double>,                 double,
        type_pair<double,E2>,                     double,
        type_pair<E1,double>,                     double,

        type_pair<float,float>,                   float,
        type_pair<float,E2>,                      float,
        type_pair<E1,float>,                      float,

        type_pair<E1,E2>,                         void

    >::result   float_filter;

    /* The promoted integral types really matter here: */
    typedef typename select_switch<
        type_pair<E1,E2>,

        type_pair<unsigned long,unsigned long>,   unsigned long,
        type_pair<unsigned long,E2>,              unsigned long,
        type_pair<E1,unsigned long>,              unsigned long,

        type_pair<long,long>,                     long,
        type_pair<long,unsigned int>,             uint_promotion,
        type_pair<unsigned int,long>,             uint_promotion,

        type_pair<long,E2>,                       long,
        type_pair<E1,long>,                       long,

        type_pair<unsigned int,unsigned int>,     unsigned int,
        type_pair<unsigned int,E2>,               unsigned int,
        type_pair<E1,unsigned int>,               unsigned int,

        type_pair<int,int>,                       int,
        type_pair<int,E2>,                        int,
        type_pair<E1,int>,                        int,

        type_pair<E1,E2>,                         void

    >::result   int_filter;

    /* Deduce the final type: */
    typedef typename select_if<
        same_type<float_filter,void>::is_true,
        int_filter, float_filter>::result         type;
};
#endif

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
