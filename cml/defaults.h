/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Default values for certain parameters.
 */

#ifndef defaults_h
#define defaults_h

/* The default unroll limit: */
#if !defined(CML_VECTOR_UNROLL_LIMIT)
#define CML_VECTOR_UNROLL_LIMIT 8
#endif

/* Don't unroll matrix operations by default: */
#if !defined(CML_2D_UNROLLER) && !defined(CML_NO_2D_UNROLLER)
#define CML_NO_2D_UNROLLER
#endif

/* The default array layout is the C/C++ row-major array layout: */
#if !defined(CML_DEFAULT_ARRAY_LAYOUT)
#define CML_DEFAULT_ARRAY_LAYOUT cml::row_major
#endif

/* Always use the default layout in promotions, by default: */
#if !defined(CML_ALWAYS_PROMOTE_TO_DEFAULT_LAYOUT)
#define CML_ALWAYS_PROMOTE_TO_DEFAULT_LAYOUT
#endif

/* The default memory allocator is std::allocator<void>: */
#if !defined(CML_DEFAULT_ARRAY_ALLOC)
#include <memory>               // for std::allocator
#define CML_DEFAULT_ARRAY_ALLOC std::allocator<void>
#endif

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
