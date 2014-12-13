/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_vector_product_h
#define	cml_vector_vector_product_h

#include <cml/common/scalar_promotion.h>
#include <cml/common/storage_tags.h>
#include <cml/vector/dot.h>
#include <cml/vector/vector.h>
#include <cml/matrix/array_size_of.h>
#include <cml/matrix/type_util.h>

namespace cml {

/** Deduce the temporary type required to hold the result of matrix-vector
 * multiplication.
 */
template<class Sub1, class Sub2>
struct matrix_vector_product_temporary {
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;

  /* Determine the element type: */
  typedef dot_promote_t<left_type, right_type>		element_type;

  /* Determine the storage type: */
  static const int array_rows = array_rows_of_c<left_type>::value;
  static const int array_cols = array_cols_of_c<right_type>::value;
  static const int array_size
    = (array_rows > array_cols) ? array_rows : array_cols;
  typedef cml::if_t<array_rows == -1 || array_cols == -1,
	  cml::dynamic<>, cml::fixed<array_size>>	storage_type;

  /* Build the vector type: */
  typedef vector<element_type, storage_type>		type;
};

template<class Sub1, class Sub2> using matrix_vector_product_temporary_t
= typename matrix_vector_product_temporary<Sub1,Sub2>::type;


/** Multiply a vector by a matrix, and return the vector result as a
 * temporary.
 */
template<class Sub1, class Sub2,
  cml::enable_if_matrix_t<Sub1>* = nullptr,
  cml::enable_if_vector_t<Sub2>* = nullptr>
inline auto operator*(Sub1&& sub1, Sub2&& sub2)
-> matrix_vector_product_temporary_t<Sub1, Sub2>;

/** Multiply a matrix by a vector, and return the vector result as a
 * temporary.
 */
template<class Sub1, class Sub2,
  cml::enable_if_vector_t<Sub1>* = nullptr,
  cml::enable_if_matrix_t<Sub2>* = nullptr>
inline auto operator*(Sub1&& sub1, Sub2&& sub2)
-> matrix_vector_product_temporary_t<Sub1, Sub2>;

} // namespace cml

#define __CML_MATRIX_VECTOR_PRODUCT_TPP
#include <cml/matrix/vector_product.tpp>
#undef __CML_MATRIX_VECTOR_PRPDUCT_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
