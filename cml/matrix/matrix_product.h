/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_matrix_product_h
#define	cml_matrix_matrix_product_h

#include <cml/common/scalar_promotion.h>
#include <cml/common/storage_tags.h>
#include <cml/vector/dot.h>
#include <cml/matrix/array_size_of.h>
#include <cml/matrix/type_util.h>
#include <cml/matrix/matrix.h>

namespace cml {

/** Deduce the temporary type required to hold the result of matrix
 * multiplication.
 */
template<class Sub1, class Sub2>
struct matrix_matrix_product_temporary {
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;

  /* Determine the element type: */
  typedef dot_promote_t<left_type, right_type>		element_type;

  /* Determine the storage type: */
  static const int array_rows = array_rows_of_c<left_type>::value;
  static const int array_cols = array_cols_of_c<right_type>::value;
  typedef cml::if_t<array_rows == -1 || array_cols == -1,
	  cml::dynamic<>, cml::fixed<array_rows, array_cols>> storage_type;

  /* Determine the basis and layout types: */
  typedef basis_tag_trait_promote_t<left_type,right_type> basis_tag;
  typedef layout_tag_trait_promote_t<left_type,right_type> layout_tag;

  /* Build the matrix type: */
  typedef matrix<element_type, storage_type, basis_tag, layout_tag> type;
};

template<class Sub1, class Sub2> using matrix_matrix_product_temporary_t
= typename matrix_matrix_product_temporary<Sub1,Sub2>::type;


/** Multiply two matrices, and return the result as a temporary. */
template<class Sub1, class Sub2,
  cml::enable_if_matrix_t<Sub1>* = nullptr,
  cml::enable_if_matrix_t<Sub2>* = nullptr>
inline auto operator*(Sub1&& sub1, Sub2&& sub2)
-> matrix_matrix_product_temporary_t<Sub1, Sub2>;

} // namespace cml

#define __CML_MATRIX_MATRIX_PRODUCT_TPP
#include <cml/matrix/matrix_product.tpp>
#undef __CML_MATRIX_MATRIX_PRPDUCT_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
