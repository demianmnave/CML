/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_dynamic_external_h
#define	cml_vector_dynamic_external_h

namespace cml {

template<class Element>
class vector<Element, external<>>
: public readable_vector< vector<Element, external<>> >
, public writable_vector< vector<Element, external<>> >
{
  public:

    typedef Element					value_type;
    typedef external<>					array_type;
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
