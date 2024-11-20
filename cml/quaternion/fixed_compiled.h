/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/compiled_selector.h>
#include <cml/quaternion/writable_quaternion.h>
#include <cml/quaternion/quaternion.h>

namespace cml {

template<class Element, class Order, class Cross>
struct quaternion_traits<quaternion<Element, fixed<>, Order, Cross>>
{
  /* Traits and types for the quaternion element: */
  using element_traits = scalar_traits<Element>;
  using value_type = typename element_traits::value_type;
  using pointer = typename element_traits::pointer;
  using reference = typename element_traits::reference;
  using const_pointer = typename element_traits::const_pointer;
  using const_reference = typename element_traits::const_reference;
  using mutable_value = typename element_traits::mutable_value;
  using immutable_value = typename element_traits::immutable_value;

  /* The quaternion storage type: */
  using storage_type = rebind_t<compiled<4>, quaternion_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, fixed_size_tag>::value,
    "invalid size tag");

  /* Array size (should be positive): */
  static const int array_size = storage_type::array_size;
  static_assert(array_size == 4, "invalid quaternion size");

  /** Quaternion order. */
  using order_type = Order;

  /** Quaternion cross type. */
  using cross_type = Cross;
};

/** Fixed-length quaternion. */
template<class Element, class Order, class Cross>
class quaternion<Element, fixed<>, Order, Cross>
: public writable_quaternion<quaternion<Element, fixed<>, Order, Cross>>
{
  public:
  using quaternion_type = quaternion<Element, fixed<>, Order, Cross>;
  using readable_type = readable_quaternion<quaternion_type>;
  using writable_type = writable_quaternion<quaternion_type>;
  using traits_type = quaternion_traits<quaternion_type>;
  using element_traits = typename traits_type::element_traits;
  using value_type = typename traits_type::value_type;
  using pointer = typename traits_type::pointer;
  using reference = typename traits_type::reference;
  using const_pointer = typename traits_type::const_pointer;
  using const_reference = typename traits_type::const_reference;
  using mutable_value = typename traits_type::mutable_value;
  using immutable_value = typename traits_type::immutable_value;
  using storage_type = typename traits_type::storage_type;
  using size_tag = typename traits_type::size_tag;
  using order_type = typename traits_type::order_type;
  using cross_type = typename traits_type::cross_type;


  public:
  /* Include methods from writable_type: */
  using writable_type::W;
  using writable_type::X;
  using writable_type::Y;
  using writable_type::Z;
  using writable_type::operator=;


  public:
  /** Constant containing the array size. */
  static const int array_size = traits_type::array_size;

  /** The dimension (same as array_size). */
  static const int dimension = array_size;


  public:
  /** Compiler-default constructor.
   *
   * @note The quaternion elements are uninitialized.
   */
  quaternion() = default;

  /** Compiler-default destructor. */
  ~quaternion() = default;

  /** Compiler-default copy constructor. */
  quaternion(const quaternion_type& other) = default;

  /** Compiler-default move constructor. */
  quaternion(quaternion_type&& other) = default;

  /** Construct from a readable_quaternion. */
  template<class Sub> quaternion(const readable_quaternion<Sub>& sub);

  /** Construct from 4 values.
   *
   * @note This overload is enabled only if all of the arguments are
   * convertible to value_type.
   */
  template<class E0, class E1, class E2, class E3,
    enable_if_convertible_t<value_type, E0, E1, E2, E3>* = nullptr>
  quaternion(const E0& e0, const E1& e1, const E2& e2, const E3& e3)
  // XXX Should be in quaternion/fixed_compiled.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
  {
    this->assign_elements(e0, e1, e2, e3);
  }

  /** Construct from a 3D readable_vector and one additional element.
   *
   * @note Although the imaginary part is specified first, the proper
   * coefficient order is maintained.
   *
   * @note This overload is enabled only if the value_type of @c sub and
   * the scalar argument are convertible to value_type.
   */
  template<class Sub, class E0,
    enable_if_convertible_t<value_type, value_type_trait_of_t<Sub>, E0>* =
      nullptr>
  quaternion(const readable_vector<Sub>& sub, const E0& e0)
  // XXX Should be in quaternion/fixed_compiled.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
  {
    this->assign(sub, e0);
  }

  /** Construct from one additional element and a 3D readable_vector.
   *
   * @note Although the imaginary part is specified second, the proper
   * coefficient order is maintained.
   *
   * @note This overload is enabled only if the value_type of @c sub and
   * the scalar argument are convertible to value_type.
   */
  template<class E0, class Sub,
    enable_if_convertible_t<value_type, value_type_trait_of_t<Sub>, E0>* =
      nullptr>
  quaternion(const E0& e0, const readable_vector<Sub>& sub)
  // XXX Should be in quaternion/fixed_compiled.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
  {
    this->assign(sub, e0);
  }

  /** Construct from a 3-element array and one additional element.
   *
   * @note Although the imaginary part is specified first, the proper
   * coefficient order is maintained.
   */
  template<class Array, class E1, enable_if_array_t<Array>* = nullptr>
  quaternion(const Array& array, const E1& e1);

  /** Construct from one additional element and a 3-element array.
   *
   * @note Although the imaginary part is specified second, the proper
   * coefficient order is maintained.
   */
  template<class E0, class Array, enable_if_array_t<Array>* = nullptr>
  quaternion(const E0& e0, const Array& array);

  /** Construct from an array type. */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  quaternion(const Array& array);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  quaternion(const Pointer& array);

  /** Construct from std::initializer_list. */
  template<class Other> quaternion(std::initializer_list<Other> l);


  public:
  /** Return the length of the quaternion. */
  int size() const;

  /** Return access to the quaternion data as a raw pointer. */
  pointer data();

  /** Return const access to the quaternion data as a raw pointer. */
  const_pointer data() const;

  /** Read-only iterator. */
  const_pointer begin() const;

  /** Read-only iterator. */
  const_pointer end() const;


  public:
  /** Copy assignment. */
  quaternion_type& operator=(const quaternion_type& other);

  /** Move assignment. */
  quaternion_type& operator=(quaternion_type&& other);


  protected:
  /** @name readable_quaternion Interface */
  /*@{*/

  friend readable_type;

  /** Return quaternion const element @c i. */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** @name writable_quaternion Interface */
  /*@{*/

  friend writable_type;

  /** Return quaternion element @c i. */
  mutable_value i_get(int i);

  /** Set element @c i. */
  template<class Other> quaternion_type& i_put(int i, const Other& v) &;

  /** Set element @c i on a temporary. */
  template<class Other> quaternion_type&& i_put(int i, const Other& v) &&;

  /*@}*/


  protected:
  /** Fixed-length array. */
  value_type m_data[4];
};

}  // namespace cml

#define __CML_QUATERNION_FIXED_COMPILED_TPP
#include <cml/quaternion/fixed_compiled.tpp>
#undef __CML_QUATERNION_FIXED_COMPILED_TPP
