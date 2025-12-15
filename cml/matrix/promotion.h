/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/promotion.h>
#include <cml/storage/resize.h>
#include <cml/storage/promotion.h>
#include <cml/scalar/promotion.h>
#include <cml/vector/vector.h>
#include <cml/vector/traits.h>
#include <cml/vector/type_util.h>
#include <cml/matrix/type_util.h>
#include <cml/matrix/traits.h>
#include <cml/matrix/matrix.h>

namespace cml {
/** Determine an appropriate storage type to use when combining matrix
 * expressions via a pairwise binary operator.
 *
 * @note This can be specialized to accomodate user-defined storage types.
 */
template<class Storage1, class Storage2> struct matrix_binary_storage_promote
{
  static_assert(
    is_matrix_storage<Storage1>::value && is_matrix_storage<Storage2>::value,
    "expected matrix storage types for binary promotion");

  /* Determine the common unbound storage type: */
  using unbound_type = storage_promote_t<Storage1, Storage2>;

  /* Determine the new row size: */
  static const int array_rows = Storage1::array_rows > Storage2::array_rows
    ? Storage1::array_rows
    : Storage2::array_rows;

  /* Determine the new column size: */
  static const int array_cols = Storage1::array_cols > Storage2::array_cols
    ? Storage1::array_cols
    : Storage2::array_cols;

  /* Resize: */
  using resized_type = reshape_storage_t<unbound_type, array_rows, array_cols>;

  /* Rebind to a matrix storage type: */
  using type = rebind_matrix_storage_t<resized_type>;
};

/** Convenience alias for matrix_binary_storage_promote. */
template<class Storage1, class Storage2>
using matrix_binary_storage_promote_t =
typename matrix_binary_storage_promote<Storage1, Storage2>::type;


/** Specializable class to determine a temporary type that can store the
 * result of matrix/matrix or matrix/vector products.
 */
template<class Sub1, class Sub2, class Enable = void>
struct matrix_inner_product_promote;

/** Determine a matrix temporary type that can hold the result of
 * multiplying two matrix expressions @c Sub1 and @c Sub2.
 */
template<class Sub1, class Sub2>
struct matrix_inner_product_promote<Sub1, Sub2,
    std::enable_if_t<is_matrix<Sub1>::value
      && is_matrix<Sub2>::value>>
{
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = matrix_traits<left_type>;
  using right_traits = matrix_traits<right_type>;
  using left_value_type = value_type_of_t<left_traits>;
  using right_value_type = value_type_of_t<right_traits>;
  using left_storage_type = storage_type_of_t<left_traits>;
  using right_storage_type = storage_type_of_t<right_traits>;

  /* Deduce the element type: */
  using value_type = value_type_trait_promote_t<left_value_type,
    right_value_type>;

  /* Determine the common unbound storage type from the bound proxy types,
   * preferring a dynamic-size type unless the resulting matrix can be
   * fixed-size:
   */
  using left_proxy_type = rebind_matrix_storage_t<proxy_type_of_t<
    left_storage_type>>;
  using right_proxy_type = rebind_matrix_storage_t<proxy_type_of_t<
    right_storage_type>>;
  static const int left_rows = left_proxy_type::array_rows;
  static const int right_cols = right_proxy_type::array_cols;
  static const bool is_fixed = left_rows > 0 && right_cols > 0;
  using unbound_type = storage_promote_t<left_proxy_type, right_proxy_type, !
    is_fixed>;

  /* Determine the new matrix size: */
  static const int array_rows = is_fixed ? left_rows : -1;
  static const int array_cols = is_fixed ? right_cols : -1;

  /* Determine the unbound proxy type: */
  using resized_type = reshape_storage_t<unbound_type, array_rows, array_cols>;
  using proxy_type = proxy_type_of_t<rebind_matrix_storage_t<resized_type>>;

  /* Determine the common basis type: */
  using basis_tag = basis_tag_promote_t<basis_tag_of_t<left_traits>,
    basis_tag_of_t<right_traits>>;

  /* Determine the common layout type: */
  using layout_tag = layout_tag_promote_t<layout_tag_of_t<left_traits>,
    layout_tag_of_t<right_traits>>;

  /* Build the temporary: */
  using type = matrix<value_type, proxy_type, basis_tag, layout_tag>;
};

/** Determine a matrix temporary type that can hold the result of
 * multiplying two matrix expressions @c Sub1 and @c Sub2.
 */
template<class Sub1, class Sub2>
struct matrix_inner_product_promote<Sub1, Sub2,
    std::enable_if_t<(is_vector<Sub1>::value && is_matrix<Sub2>::value)
      || (is_matrix<Sub1>::value && is_vector<Sub2>::value)>>
{
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;

  /* Figure out if pre- or post-multiplying: */
  static const bool left_is_vector = is_vector<left_type>::value;
  static const bool right_is_vector = is_vector<right_type>::value;
  static_assert(left_is_vector ^ right_is_vector, "unexpected expression");

  /* Vector traits and types: */
  using vector_type = cml::if_t<left_is_vector, left_type, right_type>;
  using vector_traits = traits_of_t<vector_type>;
  using vector_value_type = value_type_of_t<vector_traits>;
  using vector_storage_type = storage_type_of_t<vector_traits>;

  /* Matrix traits and types: */
  using matrix_type = cml::if_t<right_is_vector, left_type, right_type>;
  using matrix_traits = traits_of_t<matrix_type>;
  using matrix_value_type = value_type_of_t<matrix_traits>;
  using matrix_storage_type = storage_type_of_t<matrix_traits>;

  /* Deduce the element type: */
  using value_type = value_type_trait_promote_t<vector_value_type,
    matrix_value_type>;

  /* The resulting vector size comes from the bound matrix proxy rows or
   * columns, depending on pre- or post-multiplication:
   */
  using matrix_unbound_type = proxy_type_of_t<matrix_storage_type>;
  using matrix_proxy_type = rebind_matrix_storage_t<matrix_unbound_type>;
  static const int array_size = left_is_vector
    ? matrix_proxy_type::array_cols
    : matrix_proxy_type::array_rows;

  /* Determine the unbound and bound vector proxy types by resizing the
   * original vector storage type:
   */
  using vector_resized_type = rebind_vector_storage_t<
    resize_storage_t<vector_storage_type, array_size>>;
  using vector_unbound_type = proxy_type_of_t<vector_resized_type>;
  using vector_proxy_type = rebind_vector_storage_t<vector_unbound_type>;
  /* Note: two rebinds are needed here, first to get the unbound proxy
   * type, then to get the bound proxy type for sizing.
   */

  /* Determine the common unbound storage type from the bound proxy types,
   * preferring a dynamic-size type unless the resulting vector can be
   * fixed-size:
   */
  static const bool is_fixed = array_size > 0;
  using unbound_type = storage_promote_t<vector_proxy_type, matrix_proxy_type, !
    is_fixed>;
  using resized_type = resize_storage_t<unbound_type, array_size>;

  /* Prefer the unbound vector proxy type when possible: */
  using proxy_type = cml::if_t<
    /**/ (is_fixed && is_fixed_size<vector_proxy_type>::value)
    || (!is_fixed && is_dynamic_size<vector_proxy_type>::value),
    vector_unbound_type, resized_type>;

  /* Build the temporary: */
  using type = vector<value_type, proxy_type>;
};

/** Convenience alias for matrix_inner_product_promote. */
template<class Sub1, class Sub2>
using matrix_inner_product_promote_t =
typename matrix_inner_product_promote<Sub1, Sub2>::type;

template<class Storage1, class Storage2>
struct matrix_outer_product_storage_promote
{
  static_assert(
    is_vector_storage<Storage1>::value && is_vector_storage<Storage2>::value,
    "expected vector storage types for outer product promotion");

  /* Deduce the left matrix storage type from the vector storage: */
  static const int left_size = Storage1::array_size;
  using left_unbound_type = reshape_storage_t<typename Storage1::unbound_type,
    left_size, -1>;
  using left_storage_type = rebind_matrix_storage_t<left_unbound_type>;

  /* Deduce the right matrix storage type from the vector storage: */
  static const int right_size = Storage2::array_size;
  using right_unbound_type = reshape_storage_t<typename Storage2::unbound_type,
    -1, right_size>;
  using right_storage_type = rebind_matrix_storage_t<right_unbound_type>;

  /* Determine the common storage type, based on the storage types of its
   * subexpressions:
   */
  using type = matrix_binary_storage_promote_t<left_storage_type,
    right_storage_type>;
};

/** Convenience alias for matrix_outer_product_promote. */
template<class Storage1, class Storage2>
using matrix_outer_product_storage_promote_t =
typename matrix_outer_product_storage_promote<Storage1, Storage2>::type;


/** Specializable class to determine a temporary type that can store the
 * result of vector outer products.
 */
template<class Sub1, class Sub2, class Basis, class Layout, class Enable = void>
struct matrix_outer_product_promote;

/** Determine a matrix temporary type that can hold the result of the outer
 * product of two vector expressions @c Sub1 and @c Sub2.
 *
 * @note The temporary will
 */
template<class Sub1, class Sub2, class Basis, class Layout>
struct matrix_outer_product_promote<Sub1, Sub2, Basis, Layout,
    std::enable_if_t<(is_vector<Sub1>::value
      && is_vector<Sub2>::value)>>
{
  using left_type = cml::unqualified_type_t<Sub1>;
  using right_type = cml::unqualified_type_t<Sub2>;
  using left_traits = vector_traits<left_type>;
  using right_traits = vector_traits<right_type>;

  /* Deduce the element type: */
  using value_type = value_type_promote_t<left_traits, right_traits>;

  /* Determine the common storage type for the temporary, based on the
   * storage types of its subexpressions:
   */
  using left_storage_type = storage_type_of_t<left_traits>;
  using right_storage_type = storage_type_of_t<right_traits>;
  using storage_type = matrix_outer_product_storage_promote_t<left_storage_type,
    right_storage_type>;
  using proxy_type = proxy_type_of_t<storage_type>;

  /* Build the temporary: */
  using type = matrix<value_type, proxy_type, Basis, Layout>;
};

/** Convenience alias for matrix_outer_product_promote. */
template<class Sub1, class Sub2, class Basis, class Layout>
using matrix_outer_product_promote_t =
typename matrix_outer_product_promote<Sub1, Sub2, Basis, Layout>::type;


/** Determine the row vector temporary type for matrix type @c Sub. */
template<class Sub, class Enable = void> struct row_type_of;

template<class Sub>
struct row_type_of<Sub,
    std::enable_if_t<cml::is_matrix<Sub>::value>>
{
  /* Matrix traits and types: */
  using matrix_type = cml::unqualified_type_t<Sub>;
  using matrix_traits = cml::traits_of_t<matrix_type>;
  using matrix_storage_type = cml::storage_type_of_t<matrix_traits>;
  using value_type = cml::value_type_of_t<matrix_traits>;

  /* The vector proxy type and size comes from the matrix proxy type: */
  using unbound_type = cml::proxy_type_of_t<matrix_storage_type>;
  using proxy_type = cml::rebind_matrix_storage_t<unbound_type>;
  static const int array_size = proxy_type::array_cols;
  using vector_type = cml::resize_storage_t<unbound_type, array_size>;

  /* Build the temporary: */
  using type = cml::vector<value_type, vector_type>;
};

/** Convenience alias for row_type_of. */
template<class Sub> using row_type_of_t = typename row_type_of<Sub>::type;


/** Determine the column vector temporary type for matrix type @c Sub. */
template<class Sub, class Enable = void> struct col_type_of;

template<class Sub>
struct col_type_of<Sub,
    std::enable_if_t<cml::is_matrix<Sub>::value>>
{
  /* Matrix traits and types: */
  using matrix_type = cml::unqualified_type_t<Sub>;
  using matrix_traits = cml::traits_of_t<matrix_type>;
  using matrix_storage_type = cml::storage_type_of_t<matrix_traits>;
  using value_type = cml::value_type_of_t<matrix_traits>;

  /* The vector proxy type and size comes from the matrix proxy type: */
  using unbound_type = cml::proxy_type_of_t<matrix_storage_type>;
  using proxy_type = cml::rebind_matrix_storage_t<unbound_type>;
  static const int array_size = proxy_type::array_rows;
  using vector_type = cml::resize_storage_t<unbound_type, array_size>;

  /* Build the temporary: */
  using type = cml::vector<value_type, vector_type>;
};

/** Convenience alias for col_type_of. */
template<class Sub> using col_type_of_t = typename col_type_of<Sub>::type;
} // namespace cml
