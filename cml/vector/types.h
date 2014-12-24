/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_types_h
#define	cml_vector_types_h

#include <cml/common/storage_tags.h>
#include <cml/vector/vector.h>

namespace cml {

/** @defgroup vector_types Predefined Vector Types */
/*@{*/

typedef vector<int,    fixed<2>>     vector2i;
typedef vector<int,    fixed<3>>     vector3i;
typedef vector<int,    fixed<4>>     vector4i;
typedef vector<int,    dynamic<>>    vectori;
typedef vector<int,    external<2>>  external2i;
typedef vector<int,    external<3>>  external3i;
typedef vector<int,    external<4>>  external4i;
typedef vector<int,    external<>>   externali;

typedef vector<float,  fixed<2>>     vector2f;
typedef vector<float,  fixed<3>>     vector3f;
typedef vector<float,  fixed<4>>     vector4f;
typedef vector<float,  dynamic<>>    vectorf;
typedef vector<float,  external<2>>  external2f;
typedef vector<float,  external<3>>  external3f;
typedef vector<float,  external<4>>  external4f;
typedef vector<float,  external<>>   externalf;

typedef vector<double, fixed<2>>     vector2d;
typedef vector<double, fixed<3>>     vector3d;
typedef vector<double, fixed<4>>     vector4d;
typedef vector<double, dynamic<>>    vectord;
typedef vector<double, external<2>>  external2d;
typedef vector<double, external<3>>  external3d;
typedef vector<double, external<4>>  external4d;
typedef vector<double, external<>>   externald;

/*@}*/

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
