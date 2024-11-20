/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/scalar/binary_ops.h>
#include <cml/vector/temporary.h>

namespace cml {

/* Forward declarations: */
template<class Sub, class Scalar, class Op> class vector_scalar_node;
template<class Sub> class subvector_node;

/** Base class for readable vector types.  Readable vectors support const
 * access to its elements.
 *
 * DerivedT must implement:
 *
 * - int i_size() const, returning the number of vector elements (even if
 * static); and
 *
 * - <X> i_get(int i) const, where <X> is the immutable_value type defined
 * by vector_traits<DerivedT>.  Note that immutable_value is not
 * necessarily a reference or const type.
 */
template<class DerivedT> class readable_vector
{
  public:
  using vector_type = DerivedT;
  using traits_type = vector_traits<vector_type>;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using immutable_value = typename traits_type::immutable_value;
  using size_tag = typename traits_type::size_tag;


  public:
  /** @name CML1 Types */
  /*@{*/

  using subvector_type = subvector_of_t<DerivedT>;
  using supervector_type = supervector_of_t<DerivedT>;

  /*@}*/


  public:
  /** Return a const reference to the vector cast as DerivedT. */
  const DerivedT& actual() const;

  /** Return the number of vector elements. */
  int size() const;

  /** Return const element @c i. */
  immutable_value get(int i) const;

  /** Return const element @c i. */
  template<std::size_t I,
    enable_if_fixed_size<vector_traits<DerivedT>>* = nullptr>
  immutable_value get() const;

  /** Return const element @c i. */
  immutable_value operator[](int i) const;


  public:
  /** Return the squared length of the vector. */
  value_type length_squared() const;

  /** Return the length of the vector. */
  value_type length() const;

  /** Return the normalized vector as an expression node. */
  vector_scalar_node<const DerivedT&, value_type,
    op::binary_divide<value_type, value_type>>
  normalize() const&;

  /** Return the normalized vector as an expression node, moving the
     * source into the node.
     */
  vector_scalar_node<DerivedT&&, value_type,
    op::binary_divide<value_type, value_type>>
  normalize() const&&;

  /** Return subvector @c i as an expression node. */
  subvector_node<const DerivedT&> subvector(int i) const&;

  /** Return subvector @c i as an expression node, moving the source
     * into the node.
     */
  subvector_node<DerivedT&&> subvector(int i) const&&;


  protected:
  // Use the compiler-generated default constructor:
  readable_vector() = default;

  // Use the compiler-generated copy constructor:
  readable_vector(const readable_vector&) = default;

  // Use the compiler-generated move constructor:
  readable_vector(readable_vector&&) = default;
};

}  // namespace cml

#define __CML_VECTOR_READABLE_VECTOR_TPP
#include <cml/vector/readable_vector.tpp>
#undef __CML_VECTOR_READABLE_VECTOR_TPP
