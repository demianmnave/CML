/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef meta_switch_h
#define meta_switch_h

#include <cml/core/meta/common.h>
#include <cml/core/meta/if.h>

/* The working parts of the meta-switch go into namespace meta: */
namespace meta {

struct NilCase {};      /* For terminating the case list. */
struct Default {};      /* For indicating the default result. */

/* "Interior" case statements: */
template<typename Case, typename Result, typename NextCase = NilCase>
struct select_case
{
    template<typename Find> struct match {
        typedef typename select_if<
            same_type<Find,Case>::is_true,
            Result,
            typename NextCase::template match<Find>::result
        >::result result;
    };
};

/* Default case, returned when no match is found in a previous case: */
template<typename Result, typename NextCase>
struct select_case<Default,Result,NextCase>
{
    template<typename Find> struct match {
        typedef Result result;
    };
};

/* The last case statement (if no match until now, the result is 'void'): */
template<typename Case, typename Result>
struct select_case<Case,Result,NilCase>
{
    template<typename Find> struct match {
        typedef typename select_if<
            same_type<Find,Case>::is_true,
            Result,
            void
        >::result result;
    };
};

} // namespace meta

/** Return the matched type (like a switch/case statement).
 *
 * This is a convenience wrapper to avoid having to explicitly type out
 * select_case for each case in the list of types to match against.
 */
template<typename Find
, typename T1,                 typename R1
, typename T2 = meta::NilCase, typename R2 = void
, typename T3 = meta::NilCase, typename R3 = void
, typename T4 = meta::NilCase, typename R4 = void
, typename T5 = meta::NilCase, typename R5 = void
, typename T6 = meta::NilCase, typename R6 = void
, typename T7 = meta::NilCase, typename R7 = void
, typename T8 = meta::NilCase, typename R8 = void
> struct select_switch
{
    typedef typename
          meta::select_case< T1,R1
        , meta::select_case< T2,R2
        , meta::select_case< T3,R3
        , meta::select_case< T4,R4
        , meta::select_case< T5,R5
        , meta::select_case< T6,R6
        , meta::select_case< T7,R7
        , meta::select_case< T8,R8
        > > > > > > > >::template match<Find>::result result;
};

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
