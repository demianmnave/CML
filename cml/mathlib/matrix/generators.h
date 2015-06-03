/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
 /** @file
   */

#pragma once

#ifndef	cml_mathlib_matrix_generators_h
#define	cml_mathlib_matrix_generators_h

#include <cml/matrix/fixed_compiled.h>

   /** @defgroup mathlib_vector_generators Vector Generator Functions */

namespace cml {

	/** @addtogroup mathlib_vector_generators */
	/*@{*/

	/** @defgroup mathlib_vector_generators_basic Basic Vector Generators */
	/*@{*/

	/** Return an double-precision N-d zero vector. */
	template<int Rows, int Cols>
	inline matrix< double, compiled<Rows, Cols> > zero()
	{
		return matrix<double, compiled<Rows, Cols> >().zero();
	}

	/** Return a double-precision N-d cardinal axis by index. */
	template<int Rows, int Cols>
	inline matrix< double, compiled<Rows, Cols> > identity()
	{
		return matrix<double, compiled<Rows, Cols>>().identity();
	}

	//////////////////////////////////////////////////////////////////////////////
	// Zero matrix
	//////////////////////////////////////////////////////////////////////////////

	/** Return the 2x2 zero matrix */
	inline auto zero_2x2() -> decltype(zero<2, 2>()) {
		return identity<2, 2>();
	}

	/** Return the 3x3 zero matrix */
	inline auto zero_3x3() -> decltype(zero<3, 3>()) {
		return zero<3, 3>();
	}

	/** Return the 4x4 zero matrix */
	inline auto zero_4x4() -> decltype(zero<4, 4>()) {
		return zero<4, 4>();
	}

	//////////////////////////////////////////////////////////////////////////////
	// Identity matrix
	//////////////////////////////////////////////////////////////////////////////

	/** Return the 2x2 identity matrix */
	inline auto identity_2x2() -> decltype(identity<2,2>()) { 
		return identity<2, 2>(); 
	}

	/** Return the 3x3 identity matrix */
	inline auto identity_3x3() -> decltype(identity<3, 3>()) {
		return identity<3, 3>();
	}

	/** Return the 4x4 identity matrix */
	inline auto identity_4x4() -> decltype(identity<4, 4>()) {
		return identity<4, 4>();
	}

	/*@}*/

	/*@}*/

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2


