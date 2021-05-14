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

#endif