/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef cml_common_compiler_h
#define cml_common_compiler_h

#if defined(__GNUC__) && ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9))
/* g++ support for C++11 features used by CML: */

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

#elif defined(_MSC_VER)
/* VC++ support for C++11 features used by CML: */

# if _MSC_VER < 1900
/* VC++ (at least VS12) does not support move from *this, so no need to
 * disambiguate:
 */
#  define __CML_REF

/* VC++ (at least VS12) has brain-dead operator= overload resolution: */
#  define CML_HAS_MSVC_BRAIN_DEAD_ASSIGNMENT_OVERLOADS

# else

/* N2439 move semantics for *this, used, for example, to efficiently return
 * an expression node from a class method. Without this, a temporary is
 * returned instead:
 */
#  define CML_HAS_RVALUE_REFERENCE_FROM_THIS

/* Trailing method type for ref from *this (to disambiguate overloads using
 * rvalue reference from this):
 */
#  define __CML_REF		&

/* Defaulted move constructor supported: */
#  define CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR

# endif

#elif defined(__clang__) && ((__clang_major__ >= 3) && (__clang_minor__ >= 5))
/* clang support for C++11 features used by CML: */

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

#elif defined(__apple_build_version__) && (__apple_build_version__ >= 7000000)
/* AppleClang support for C++11 features used by CML: */

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

#else
#warning "Unrecognized compiler; using safe defaults"

/* Assume no default move constructors: */
// # define CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR

/* Assume no rvalue reference from this: */
// # define CML_HAS_RVALUE_REFERENCE_FROM_THIS

/* Assume no disambiguation needed: */
# define __CML_REF

#endif

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
