/* -*- C++ -*- ------------------------------------------------------------
 
Copyright (c) 2007 Jesse Anders and Demian Nave http://cmldev.net/

The Configurable Math Library (CML) is distributed under the terms of the
Boost Software License, v1.0 (see cml/LICENSE for details).

 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef epsilon_h
#define epsilon_h

namespace cml {

/* @todo: epsilon and tolerance handling.
 *
 * Note: Handling of epsilons, tolerances, and degenerate and corner cases
 * is currently an unaddressed issue in the CML, but is at the top of the
 * to-do list.
 *
 * Currently, functions for which an epsilon is applicable take an epsilon
 * value as the last argument. For now, this always defaults to the arbitrary
 * placeholder value, but can of course be specified by the user instead.
 *
 * At some point (soon, I hope) the epsilon class will be filled out to
 * provide meaningful and reasonable epsilons for different situations and
 * scalar types. It may also be possible to set the default values for various
 * purposes (e.g. vector normalization, matrix singularity check, and so on).
 */

template < typename Real >
struct epsilon
{
    typedef Real value_type;
    
private:

    /** For convenience */
    typedef value_type T;
    
public:

    static T placeholder() {
        /* Completely arbitrary placeholder value: */
        return T(0.0001);
    }
};

} // namespace cml

#endif