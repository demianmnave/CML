/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef cml_common_compiler_h
#define cml_common_compiler_h

/* N2439 move semantics for *this, used, for example, to efficiently return
 * an expression node from a class method. Without this, a temporary is
 * returned instead:
 */
#ifdef __cpp_ref_qualifiers
# define CML_HAS_RVALUE_REFERENCE_FROM_THIS
# define __CML_REF		&
#else
# error "Compiler does not support __cpp_ref_qualifiers."
#endif

/* Compiler (optionally) supports C++17 structured bindings: */
#ifdef __cpp_structured_bindings
# define CML_HAS_STRUCTURED_BINDINGS
#endif

#if defined(__GNUC__) && (__GNUC__ > 4 \
  || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)))

/* Defaulted move constructor supported: */
# define CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR

#elif defined(__clang__)
/* Note: checking for Clang BEFORE checking for Visual Studio, since clang-cl
 * defines _MSC_VER.
 */

/* Defaulted move constructor: */
# if ((__clang_major__ >= 4) \
  || ((__clang_major__ >= 3) && (__clang_minor__ >= 5))) \
  || (__apple_build_version__ >= 7000000)

#  define CML_HAS_DEFAULTED_MOVE_CONSTRUCTOR
# endif

#elif defined(_MSC_VER)

# if(_MSC_VER < 1914)
/* Apparently, VS2015 does not allow a parameter pack expansion to target non-
 * packed parameters.
 */
#  define CML_HAS_MSVC_WONKY_PARAMETER_PACK
# endif

#else
#error "Unsupported compiler."
#endif

#endif