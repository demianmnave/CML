/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_matrix_promotion_h
#define	cml_matrix_promotion_h

#include <cml/common/fixed_selector.h>
#include <cml/common/dynamic_selector.h>
#include <cml/common/promotion.h>
#include <cml/matrix/traits.h>
#include <cml/matrix/matrix.h>

namespace cml {

/** Templated helper to return the size_tag of a matrix expression using
 * matrix_traits.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub> struct matrix_size_tag_of {
  typedef size_tag_of_t<matrix_traits<cml::unqualified_type_t<Sub>>> type;
};

/** Return the size_tag of a matrix expression using matrix_traits. */
template<class Sub> using matrix_size_tag_of_t
  = typename matrix_size_tag_of<Sub>::type;


/** Deduce the matrix size tag resulting from combining the size_tag types
 * from two matrix expressions.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub1, class Sub2> struct matrix_size_tag_promote {
  typedef size_tag_promote_t<
    matrix_size_tag_of_t<Sub1>, matrix_size_tag_of_t<Sub2>> type;
};

/** Convenience alias for matrix_size_tag_promote. */
template<class Sub1, class Sub2> using matrix_size_tag_promote_t
  = typename matrix_size_tag_promote<Sub1,Sub2>::type;


/** Deduce the fixed<> or dynamic<> storage type that can be used to create
 * a temporary to store the result of combining @c Sub1 and @c Sub2.  The
 * default:
 *
 * - fixed_size_tag with any other tag: fixed<>
 * - otherwise (including any_size_tag): dynamic<>
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub1, class Sub2> struct matrix_storage_promote
{
  /* The promoted size tag: */
  typedef matrix_size_tag_promote_t<Sub1,Sub2>		size_tag;

  /* True if the promoted size is fixed_size_tag: */
  static const bool is_fixed
    = std::is_same<size_tag,fixed_size_tag>::value;

  /* The left array row count (-1 if dynamic_size_tag or any_size_tag): */
  static const int left_array_rows
    = cml::unqualified_type<Sub1>::type::array_rows;

  /* The left array column count (-1 if dynamic_size_tag or any_size_tag): */
  static const int left_array_cols
    = cml::unqualified_type<Sub1>::type::array_cols;

  /* The right array row count (-1 if dynamic_size_tag or any_size_tag): */
  static const int right_array_rows
    = cml::unqualified_type<Sub2>::type::array_rows;

  /* The right array column count (-1 if dynamic_size_tag or any_size_tag): */
  static const int right_array_cols
    = cml::unqualified_type<Sub2>::type::array_cols;

  /* The fixed row count, or -1 if Sub1 and Sub2 are dynamic or any size
   * expressions:
   */
  static const int array_rows
    = left_array_rows > right_array_rows
    ? left_array_rows : right_array_rows;

  /* The fixed column count, or -1 if Sub1 and Sub2 are dynamic or any size
   * expressions:
   */
  static const int array_cols
    = left_array_cols > right_array_cols
    ? left_array_cols : right_array_cols;

  /* The matrix extents have to be both positive for fixed_size_tag, or
   * both negative otherwise:
   */
  static_assert(
    ((array_rows > 0 && array_cols > 0) && is_fixed)
    || ((array_rows < 0 && array_cols < 0) && !is_fixed),
    "invalid matrix extents");

  /* Use fixed<> storage if possible, otherwise use dynamic<>: */
  typedef cml::if_t<
    std::is_same<size_tag, fixed_size_tag>::value,
    fixed<array_rows,array_cols>, dynamic<>>		type;
};

/** Convenience alias for matrix_storage_promote_t<>::type. */
template<class Sub1, class Sub2> using matrix_storage_promote_t
  = typename matrix_storage_promote<Sub1,Sub2>::type;


/** Templated helper to return the layout_tag of a matrix expression using
 * matrix_traits.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub> struct matrix_layout_tag_of {
  typedef layout_tag_of_t<matrix_traits<cml::unqualified_type_t<Sub>>> type;
};

/** Return the layout_tag of a matrix expression using matrix_traits. */
template<class Sub> using matrix_layout_tag_of_t
  = typename matrix_layout_tag_of<Sub>::type;


/** Deduce the default layout tag needed to promote the result of combining
 * two expressions having layout tags @c Tag1 and @c Tag2.  By default:
 *
 * - both row_major, or row_major with any_major: row_major
 * - both col_major, or col_major with any_major: col_major
 * - both any_major: any_major
 * - otherwise, error
 *
 * @note This can be specialized for user-defined layout tags.
 */
template<class Tag1, class Tag2> struct layout_tag_promote
{
  static_assert(cml::is_layout_tag<Tag1>::value, "invalid layout tag");
  static_assert(cml::is_layout_tag<Tag2>::value, "invalid layout tag");

  /* True if the tags are the same: */
  static const bool is_matched = std::is_same<Tag1,Tag2>::value;

  /* True if Tag1 is any_major: */
  static const bool left_is_any = std::is_same<Tag1, any_major>::value;

  /* True if Tag2 is any_major: */
  static const bool right_is_any = std::is_same<Tag2, any_major>::value;

  /* The layouts must be the same, or at least one must be any_major: */
  static_assert(is_matched || left_is_any || right_is_any,
    "promotion of mismatched matrix layouts not supported by default");

  /* True if promoting to row major: */
  static const bool is_row_major
    = (std::is_same<Tag1,row_major>::value && (is_matched || right_is_any))
    || (std::is_same<Tag2,row_major>::value && (is_matched || left_is_any));

  /* True if promoting to column major: */
  static const bool is_col_major
    = (std::is_same<Tag1,col_major>::value && (is_matched || right_is_any))
    || (std::is_same<Tag2,col_major>::value && (is_matched || left_is_any));

  /* True if promoting to any_major: */
  static const bool is_any_major
    = std::is_same<Tag1,any_major>::value
    && std::is_same<Tag2,any_major>::value;
  // Note: for clarity, is_matched isn't used here.

  /* Check: */
  static_assert(is_row_major || is_col_major || is_any_major,
    "unexpected layout tag type");

  /* Promote to the selected tag: */
  typedef cml::if_t<is_row_major, row_major,
	  cml::if_t<is_col_major, col_major, any_major>> type;
};

/** Convenience alias for layout_tag_promote. */
template<class Tag1, class Tag2>
  using layout_tag_promote_t = typename layout_tag_promote<Tag1,Tag2>::type;


/** Deduce the matrix size tag resulting from combining the layout_tag types
 * from two matrix expressions.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub1, class Sub2> struct matrix_layout_tag_promote {
  typedef layout_tag_promote_t<
    matrix_layout_tag_of_t<Sub1>, matrix_layout_tag_of_t<Sub2>> type;
};

/** Convenience alias for matrix_layout_tag_promote. */
template<class Sub1, class Sub2> using matrix_layout_tag_promote_t
  = typename matrix_layout_tag_promote<Sub1,Sub2>::type;


/** Deduce the default basis tag needed to promote the result of combining
 * two expressions having basis tags @c Tag1 and @c Tag2.  By default:
 *
 * - both row_basis: row_basis
 * - both col_basis: col_basis
 * - otherwise, error
 *
 * @note This can be specialized to change the default promotion strategy.
 */
template<class Tag1, class Tag2> struct basis_tag_promote
{
  static_assert(cml::is_basis_tag<Tag1>::value, "invalid basis tag");
  static_assert(cml::is_basis_tag<Tag2>::value, "invalid basis tag");

  /* True if the bases are the same: */
  static const bool is_matched = std::is_same<Tag1,Tag2>::value;

  /* The tags must be the same: */
  static_assert(is_matched,
    "promotion of mismatched matrix bases not supported by default");

  /* Promote to the common orientation: */
  typedef Tag1						type;
};

/** Convenience alias for basis_tag_promote. */
template<class Tag1, class Tag2>
  using basis_tag_promote_t = typename basis_tag_promote<Tag1,Tag2>::type;


/** Templated helper to return the basis_tag of a matrix expression using
 * matrix_traits.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub> struct matrix_basis_tag_of {
  typedef basis_tag_of_t<matrix_traits<cml::unqualified_type_t<Sub>>> type;
};

/** Return the basis_tag of a matrix expression using matrix_traits. */
template<class Sub> using matrix_basis_tag_of_t
  = typename matrix_basis_tag_of<Sub>::type;


/** Deduce the matrix size tag resulting from combining the basis_tag types
 * from two matrix expressions.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub1, class Sub2> struct matrix_basis_tag_promote {
  typedef basis_tag_promote_t<
    matrix_basis_tag_of_t<Sub1>, matrix_basis_tag_of_t<Sub2>> type;
};

/** Convenience alias for matrix_basis_tag_promote. */
template<class Sub1, class Sub2> using matrix_basis_tag_promote_t
  = typename matrix_basis_tag_promote<Sub1,Sub2>::type;


/** Helper to deduce the matrix temporary type that can be used to store
 * the result of combining @c Sub1 and @c Sub2, using elements of type @c
 * E.
 *
 * @note This can be specialized for user-defined matrix types.
 */
template<class Sub1, class Sub2, class E> struct matrix_temporary_promote {
  typedef matrix<
    E,
    matrix_storage_promote_t<Sub1,Sub2>,
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
