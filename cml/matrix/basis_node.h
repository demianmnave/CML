/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/type_util.h>
#include <cml/vector/readable_vector.h>
#include <cml/matrix/traits.h>

namespace cml {
template<class Sub, int I> class matrix_basis_node;

/** matrix_basis_node<> traits. */
template<class Sub, int I> struct vector_traits<matrix_basis_node<Sub, I>>
{
  using vector_type = matrix_basis_node<Sub, I>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = matrix_traits<sub_type>;
  using element_traits = typename sub_traits::element_traits;
  using value_type = typename sub_traits::value_type;
  using immutable_value = typename sub_traits::immutable_value;

  /* Propagate the column count from the subexpression: */
  static const int array_size = sub_traits::array_cols;

  /* Deduce the vector storage type: */
  using sub_storage_type = typename sub_traits::storage_type;
  using sub_unbound_type = typename sub_storage_type::unbound_type;
  using resized_type = resize_storage_t<sub_unbound_type, array_size>;
  using storage_type = rebind_vector_storage_t<resized_type>;

  /* Take the size type from the storage type: */
  using size_tag = typename storage_type::size_tag;
};

/** Represents a read-only matrix basis vector, specified at run-time by
 * its index, as a node in an expression tree.
 */
template<class Sub>
class matrix_basis_node<Sub, -1>
  : public readable_vector<matrix_basis_node<Sub, -1>>
{
  public:
  using node_type = matrix_basis_node<Sub, -1>;
  using readable_type = readable_vector<node_type>;
  using traits_type = vector_traits<node_type>;
  using sub_arg_type = typename traits_type::sub_arg_type;
  using sub_type = typename traits_type::sub_type;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;

  public:
  /** Constant containing the number of elements. */
  static const int array_size = traits_type::array_size;

  public:
  /** Construct from the wrapped sub-expression and the basis index.  @c
   * sub must be an lvalue reference or rvalue reference type.
   *
   * @throws std::invalid_argument if @c i < 0.
   */
  explicit matrix_basis_node(Sub sub, int i);

  /** Move constructor. */
  matrix_basis_node(node_type&& other);

  /** Copy constructor. */
  matrix_basis_node(const node_type& other);

  protected:
  /** @name readable_vector Interface */
  /*@{*/

  friend readable_type;

  /** Return the size of the vector expression. */
  int i_size() const;

  /** Return element @c (<basis index>,j) of the matrix. */
  immutable_value i_get(int j) const;

  /*@}*/


  protected:
  /** The type used to store the subexpression.  The expression is stored
   * as a copy if Sub is an rvalue reference (temporary), or by const
   * reference if Sub is an lvalue reference.
   */
  using sub_wrap_type = cml::if_t<std::is_lvalue_reference_v<Sub>, const
    sub_type&,
    sub_type>;

  protected:
  /** The wrapped subexpression. */
  sub_wrap_type m_sub;

  /** The basis index. */
  int m_i;

  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};
} // namespace cml

#define __CML_MATRIX_BASIS_NODE_TPP
#include <cml/matrix/basis_node.tpp>
#undef __CML_MATRIX_BASIS_NODE_TPP
