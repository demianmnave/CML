/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_promotion_h
#define	cml_matrix_promotion_h

#include <cml/common/mpl/array_size_of.h>
#include <cml/common/fixed_selector.h>
#include <cml/common/dynamic_selector.h>
#include <cml/common/promotion.h>
#include <cml/matrix/traits.h>
#include <cml/matrix/matrix.h>

namespace cml {

/** Helper to deduce the matrix temporary type that can be used to store
 * the result of pairwise combining @c Sub1 and @c Sub2, using elements of
 * type @c E.  By default, the temporary storage type will be either
 * fixed<> or dynamic<>, depending upon the types of @c Sub1 and @c Sub2.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub1, class Sub2, class E> struct matrix_temporary_promote {
  typedef cml::unqualified_type_t<Sub1>			left_type;
  typedef cml::unqualified_type_t<Sub2>			right_type;

  /* Determine the row count for the storage type: */
  static const int left_array_rows = array_rows_of_c<left_type>::value;
  static const int right_array_rows = array_rows_of_c<right_type>::value;
  static const int array_rows
    = left_array_rows > right_array_rows ? left_array_rows : right_array_rows;

  /* Determine the column count for the storage type: */
  static const int left_array_cols = array_cols_of_c<left_type>::value;
  static const int right_array_cols = array_cols_of_c<right_type>::value;
  static const int array_cols
    = left_array_cols > right_array_cols ? left_array_cols : right_array_cols;

  /* Determine the storage type: */
  typedef cml::if_t<array_rows == -1 || array_cols == -1,
	  cml::dynamic<>, cml::fixed<array_rows, array_cols>> storage_type;

  /* Build the matrix type: */
  typedef matrix<
    E,
    storage_type,
    matrix_basis_tag_promote_t<Sub1,Sub2>,
    matrix_layout_tag_promote_t<Sub1,Sub2>>			type;
};

/** Convenience alias to create a fixed<> or dynamic<> matrix temporary
 * type that can hold values from either of two matrix expression types.
 */
template<class Sub1, class Sub2, class E> using matrix_temporary_promote_t
  = typename matrix_temporary_promote<Sub1,Sub2,E>::type;

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
