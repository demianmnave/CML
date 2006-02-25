/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Default values for certain parameters.
 */

#ifndef defaults_h
#define defaults_h

/* The default array layout is the C/C++ row-major array layout: */
#if !defined(CML_DEFAULT_ARRAY_LAYOUT)
#define CML_DEFAULT_ARRAY_LAYOUT cml::row_major
#endif

/* The default memory allocator is std::allocator<void>: */
#if !defined(CML_DEFAULT_ARRAY_ALLOC)
#define CML_DEFAULT_ARRAY_ALLOC std::allocator<void>
#endif

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
