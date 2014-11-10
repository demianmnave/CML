/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_common_compiler_h
#define	cml_common_compiler_h

#if defined(__GNUC__) && ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9))
/* g++ support for C++11 features used by CML that may not be available to
 * ther compilers:
 */

/* N2439 move semantics for *this, used, for example, to efficiently return
 * an expression node from a class method. Without this, a temporary is
 * returned instead:
 */
# define CML_HAS_RVALUE_REFERENCE_FROM_THIS

/* Trailing method type for ref from *this (to disambiguate overloads using
 * rvalue reference from this):
 */
# define __CML_REF		&

/* Defaulted move constructor supported: */
# define CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR

/* Macro for defaulted move: */
# define __CML_DEFAULT_MOVE	= default


#elif defined(_MSC_VER)
/* VC++ support for C++11 features used by CML that may not be available to
 * ther compilers:
 */

/* VC++ (at least VS12) does not support move from *this, so no need to
 * disambiguate:
 */
#define __CML_REF

/* VC++ (at least VS12) does not support default move constructors: */
# define __CML_DEFAULT_MOVE


#else
#warning "Unrecognized compiler; using safe defaults"

/* Assume no default move constructors: */
// # define CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
// # define __CML_DEFAULT_MOVE

/* Assume no rvalue reference from this: */
// # define CML_HAS_RVALUE_REFERENCE_FROM_THIS

/* Assume no disambiguation needed: */
# define __CML_REF

#endif

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
