/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/readable_vector.h>
#include <cml/quaternion/readable_quaternion.h>

namespace cml {

template<class Sub> class imaginary_node;

/** imaginary_node<> traits. */
template<class Sub> struct vector_traits<imaginary_node<Sub>>
{
  /* Figure out the basic type of Sub: */
  using vector_type = imaginary_node<Sub>;
  using sub_arg_type = Sub;
  using sub_type = cml::unqualified_type_t<Sub>;
  using sub_traits = quaternion_traits<sub_type>;
  using element_traits = typename sub_traits::element_traits;
  using value_type = typename sub_traits::value_type;
  using immutable_value = typename sub_traits::immutable_value;

  /* Resize the *unbound* storage type of the quaternion subexpression to a
   * vector storage type:
   */
  using bound_storage_type = typename sub_traits::storage_type;
  using unbound_storage_type = typename bound_storage_type::unbound_type;
  using resized_type = resize_storage_t<unbound_storage_type, 3>;

  /* Rebind to vector storage: */
  using storage_type = rebind_t<resized_type, vector_storage_tag>;

  /* Traits and types for the new storage: */
  using size_tag = typename storage_type::size_tag;
  static_assert(cml::is_fixed_size<storage_type>::value, "invalid size tag");

  /* Array size: */
  static const int array_size = storage_type::array_size;
  static_assert(array_size == 3, "invalid imaginary vector size");
};

/** Represents the imaginary part of a quaternion subexpression as a
 * 3-element vector expression.
 */
template<class Sub>
class imaginary_node : public readable_vector<imaginary_node<Sub>>
{
  public:
  using node_type = imaginary_node<Sub>;
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
  /** Construct from the wrapped quaternion expression.  @c sub must be
   * an lvalue reference or rvalue reference.
   */
  explicit imaginary_node(Sub sub);

  /** Move constructor. */
  imaginary_node(node_type&& other);

  /** Copy constructor. */
  imaginary_node(const node_type& other);


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
  using wrap_type =
    cml::if_t<std::is_lvalue_reference<Sub>::value, const sub_type&, sub_type>;

  /** The wrapped subexpression. */
  wrap_type m_sub;


  private:
  // Not assignable.
  node_type& operator=(const node_type&);
};

}  // namespace cml

#define __CML_QUATERNION_IMAGINARY_NODE_TPP
#include <cml/quaternion/imaginary_node.tpp>
#undef __CML_QUATERNION_IMAGINARY_NODE_TPP
