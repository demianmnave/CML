/*------------------------------------------------------------------------- @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/readable_vector.h>
#include <cml/vector/promotion.h>

namespace cml {

template<class Sub> class subvector_node;

/** subvector_node<> traits. */
template<class Sub> struct vector_traits<subvector_node<Sub>>
{
  /* Figure out the basic type of Sub: */
  using vector_type = subvector_node<Sub>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = vector_traits<sub_type>;
  using element_traits = typename sub_traits::element_traits;
  using value_type = typename sub_traits::value_type;
  using immutable_value = typename sub_traits::immutable_value;

  /* Compute the new storage size: */

  private:
  static const int old_array_size = sub_traits::array_size;
  static const int new_array_size = old_array_size - 1;
  static const int N = new_array_size > 0 ? new_array_size : -1;

  public:
  /* Resize the storage type of the subexpression: */
  using resized_type = resize_storage_t<storage_type_of_t<sub_traits>, N>;

  /* Rebind to vector storage: */
  using storage_type = rebind_t<resized_type, vector_storage_tag>;

  /* Traits and types for the new storage: */
  using size_tag = typename storage_type::size_tag;

  /* Array size: */
  static const int array_size = storage_type::array_size;
};

/** Represents an N-1 subvector operation in an expression tree, where N is
 * the length of the wrapped subexpression.
 */
template<class Sub>
class subvector_node : public readable_vector<subvector_node<Sub>>
{
  public:
  using node_type = subvector_node<Sub>;
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
  /** The array size constant depends upon the subexpression size. */
  static const int array_size = traits_type::array_size;


  public:
  /** Construct from the wrapped sub-expression and the element to drop.
     * @c sub must be an lvalue reference or rvalue reference.
     */
  subvector_node(Sub sub, int skip);

  /** Move constructor. */
  subvector_node(node_type&& other);

#ifndef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Copy constructor. */
  subvector_node(const node_type& other);
#endif


  protected:
  /** @name readable_vector Interface */
  /*@{*/

  friend readable_type;

  /** Return the size of the vector expression. */
  int i_size() const;

  /** Apply the operator to element @c i and return the result. */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** The type used to store the subexpression.  The expression is stored
     * as a copy if Sub is an rvalue reference (temporary), or by const
     * reference if Sub is an lvalue reference.
     */
  using wrap_type = cml::if_t<std::is_lvalue_reference<Sub>::value, const sub_type&,
    sub_type>;

  /** The wrapped subexpression. */
  wrap_type m_sub;

  /** The element to skip. */
  int m_skip;


  private:
#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  // Not copy constructible.
  subvector_node(const node_type&);
#endif

  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_VECTOR_SUBVECTOR_NODE_TPP
#include <cml/vector/subvector_node.tpp>
#undef __CML_VECTOR_SUBVECTOR_NODE_TPP
