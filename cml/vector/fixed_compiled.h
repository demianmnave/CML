/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/compiled_selector.h>
#include <cml/vector/writable_vector.h>
#include <cml/vector/vector.h>

namespace cml {
template<class Element, int Size>
struct vector_traits<vector<Element, fixed<Size>>>
{
  /* Traits and types for the vector element: */
  using element_traits = scalar_traits<Element>;
  using value_type = typename element_traits::value_type;
  using pointer = typename element_traits::pointer;
  using reference = typename element_traits::reference;
  using const_pointer = typename element_traits::const_pointer;
  using const_reference = typename element_traits::const_reference;
  using mutable_value = typename element_traits::mutable_value;
  using immutable_value = typename element_traits::immutable_value;

  /* The vector storage type: */
  using storage_type = rebind_t<compiled<Size>, vector_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, fixed_size_tag>::value,
    "invalid size tag");

  /* Array size (should be positive): */
  static const int array_size = storage_type::array_size;
  static_assert(array_size > 0, "invalid vector size");
};

/** Fixed-length vector. */
template<class Element, int Size>
class vector<Element, fixed<Size>>
  : public writable_vector<vector<Element, fixed<Size>>>
{
  public:
  using vector_type = vector<Element, fixed<Size>>;
  using readable_type = readable_vector<vector_type>;
  using writable_type = writable_vector<vector_type>;
  using traits_type = vector_traits<vector_type>;
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

  public:
  /* Include methods from writable_type: */
  using writable_type::operator[];
  using writable_type::operator=;

  public:
  /** Constant containing the array size. */
  static const int array_size = traits_type::array_size;

  /** The dimension (same as array_size). */
  static const int dimension = array_size;

  public:
  /** Compiler-default constructor.
   *
   * @note The vector elements are uninitialized.
   */
  vector() = default;

  /** Compiler-default destructor. */
  ~vector() = default;

  /** Compiler-default copy constructor. */
  vector(const vector_type& other) = default;

  /** Compiler-default move constructor. */
  vector(vector_type&& other) = default;

  /** Construct from a readable_vector. */
  template<class Sub> vector(const readable_vector<Sub>& sub);

  /** Construct from at least 1 value.
   *
   * @note This overload is enabled only if all of the arguments are
   * convertible to value_type.
   */
  template<class E0, class... Elements,
    enable_if_convertible_t<value_type, E0, Elements...>* = nullptr>
  vector(const E0& e0, const Elements&... eN)
  // XXX Should be in vector/fixed_compiled.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
  {
    this->assign_elements(e0, eN...);
  }

  /** Construct from a readable_vector and at least one
   * additional element.
   *
   * @note This overload is enabled only if the value_type of @c sub and
   * all of the scalar arguments are convertible to value_type.
   */
  template<class Sub, class E0, class... Elements,
    enable_if_convertible_t<value_type, value_type_trait_of_t<Sub>, E0,
      Elements...>* = nullptr>
  vector(const readable_vector<Sub>& sub, const E0& e0, const Elements&... eN)
  // XXX Should be in vector/fixed_compiled.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
  {
    this->assign(sub, e0, eN...);
  }

  /** Construct from an array type. */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  vector(const Array& array);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  vector(const Pointer& array);

  /** Construct from std::initializer_list. */
  template<class Other> vector(std::initializer_list<Other> l);

  public:
  /** Return access to the vector data as a raw pointer. */
  pointer data();

  /** Return const access to the vector data as a raw pointer. */
  const_pointer data() const;

  /** Read-only iterator. */
  const_pointer begin() const;

  /** Read-only iterator. */
  const_pointer end() const;

  public:
  /** Copy assignment. */
  vector_type& operator=(const vector_type& other);

  /** Move assignment. */
  vector_type& operator=(vector_type&& other);

  protected:
  /** @name readable_vector Interface */
  /*@{*/

  friend readable_type;

  /** Return the length of the vector. */
  int i_size() const;

  /** Return vector const element @c i. */
  immutable_value i_get(int i) const;

  /*@}*/


  protected:
  /** @name writable_vector Interface */
  /*@{*/

  friend writable_type;

  /** Return vector element @c i. */
  mutable_value i_get(int i);

  /** Set element @c i. */
  template<class Other> vector_type& i_put(int i, const Other& v) &;

  /** Set element @c i on a temporary. */
  template<class Other> vector_type&& i_put(int i, const Other& v) &&;

  /*@}*/


  protected:
  /** Fixed-length array. */
  value_type m_data[Size];
};
} // namespace cml

template<typename E, int Size>
struct std::tuple_size<cml::vector<E, cml::fixed<Size>>>
{
  static const int value = Size;
};

template<std::size_t I, typename E, int Size>
struct std::tuple_element<I, cml::vector<E, cml::fixed<Size>>>
{
  using type = cml::value_type_of_t<cml::vector<E, cml::fixed<Size>>>;
};

#define __CML_VECTOR_FIXED_COMPILED_TPP
#include <cml/vector/fixed_compiled.tpp>
#undef __CML_VECTOR_FIXED_COMPILED_TPP
