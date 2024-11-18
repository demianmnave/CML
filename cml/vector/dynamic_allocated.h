/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/enable_if_t.h>
#include <cml/common/mpl/rebind.h>
#include <cml/storage/allocated_selector.h>
#include <cml/vector/writable_vector.h>
#include <cml/vector/vector.h>

namespace cml {

template<class Element, class Allocator>
struct vector_traits<vector<Element, dynamic<Allocator>>>
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
  using storage_type = rebind_t<allocated<Allocator>, vector_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, dynamic_size_tag>::value,
    "invalid size tag");

  /* Array size (should be -1): */
  static const int array_size = storage_type::array_size;
  static_assert(array_size == -1, "invalid vector size");
};

/** Resizable vector. */
template<class Element, class Allocator>
class vector<Element, dynamic<Allocator>>
: public writable_vector<vector<Element, dynamic<Allocator>>>
{
  protected:
  /** The real allocator type. */
  using allocator_type = cml::rebind_alloc_t<Allocator, Element>;

  /** Allocator traits. */
  using allocator_traits = std::allocator_traits<allocator_type>;

  /** Require a stateless allocator. */
  static_assert(std::is_empty<allocator_type>::value,
    "cannot use a stateful allocator for dynamic<> vectors");


  public:
  using vector_type = vector<Element, dynamic<Allocator>>;
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
#ifndef CML_HAS_MSVC_BRAIN_DEAD_ASSIGNMENT_OVERLOADS
  using writable_type::operator=;
#endif


  public:
  /** Constant containing the array size. */
  static const int array_size = traits_type::array_size;


  public:
  /** Default constructor.
     *
     * @note The vector has no elements.
     */
  vector();

  /** Construct given a size.
     *
     * @throws std::invalid_argument if @c size < 0.
     */
  template<class Int, enable_if_t<std::is_integral<Int>::value>* = nullptr>
  explicit vector(Int size);

  /** Copy constructor. */
  vector(const vector_type& other);

  /** Move constructor. */
  vector(vector_type&& other);

  /** Construct from a readable_vector. */
  template<class Sub> vector(const readable_vector<Sub>& sub);

  /** Construct from at least 1 value.  The vector is resized to
     * accomodate the number of elements passed.
     *
     * @note This overload is enabled only if all of the arguments are
     * convertible to value_type.
     */
  template<class E0, class... Elements,
    enable_if_convertible_t<value_type, E0, Elements...>* = nullptr>
  vector(const E0& e0, const Elements&... eN)
  // XXX Should be in vector/dynamic_allocated.tpp, but VC++12 has
  // brain-dead out-of-line template argument matching...
  : m_data(0)
  , m_size(0)
  {
    this->assign_elements(e0, eN...);
  }

  /** Construct from a readable_vector and at least one
     * additional element.  The vector is resized to accomodate the total
     * number of elements passed.
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
  : m_data(0)
  , m_size(0)
  {
    this->assign(sub, e0, eN...);
  }

  /** Construct from an array type. */
  template<class Array, enable_if_array_t<Array>* = nullptr>
  vector(const Array& array);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  vector(const Pointer& array, int size);

  /** Construct from a pointer to an array. */
  template<class Pointer, enable_if_pointer_t<Pointer>* = nullptr>
  vector(int size, const Pointer& array);

  /** Construct from std::initializer_list. */
  template<class Other> vector(std::initializer_list<Other> l);

  /** Destructor. */
  ~vector();


  public:
  /** Return access to the vector data as a raw pointer. */
  pointer data();

  /** Return const access to the vector data as a raw pointer. */
  const_pointer data() const;

  /** Read-only iterator. */
  const_pointer begin() const;

  /** Read-only iterator. */
  const_pointer end() const;

  /** Resize the vector to the specified size.
     *
     * @note This will reallocate the array and copy existing elements, if
     * any.
     *
     * @throws std::invalid_argument if @c n is negative.
     */
  void resize(int n);

  /** Resize the vector to the specified size without copying the old
     * elements.
     *
     * @throws std::invalid_argument if @c n is negative.
     */
  void resize_fast(int n);


  public:
  /** Copy assignment. */
  vector_type& operator=(const vector_type& other);

  /** Move assignment. */
  vector_type& operator=(vector_type&& other);

#ifdef CML_HAS_MSVC_BRAIN_DEAD_ASSIGNMENT_OVERLOADS
  template<class Other>
  inline vector_type& operator=(const readable_vector<Other>& other)
  {
    return this->assign(other);
  }

  template<class Array, enable_if_array_t<Array>* = nullptr>
  inline vector_type& operator=(const Array& array)
  {
    return this->assign(array);
  }

  template<class Other>
  inline vector_type& operator=(std::initializer_list<Other> l)
  {
    return this->assign(l);
  }
#endif


  protected:
  /** No-op for trivially destructible elements
     * (is_trivially_destructible).
     */
  void destruct(pointer, int, std::true_type);

  /** Invoke non-trivial destructors for @c n elements starting at @c
     * data.
     */
  void destruct(pointer data, int n, std::false_type);


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
  template<class Other> vector_type& i_put(int i, const Other& v) __CML_REF;

#ifdef CML_HAS_RVALUE_REFERENCE_FROM_THIS
  /** Set element @c i on a temporary. */
  template<class Other> vector_type&& i_put(int i, const Other& v) &&;
#endif

  /*@}*/


  protected:
  /** Dynamic storage. */
  pointer m_data;

  /** Size of the vector. */
  int m_size;
};

}  // namespace cml

#define __CML_VECTOR_DYNAMIC_ALLOCATED_TPP
#include <cml/vector/dynamic_allocated.tpp>
#undef __CML_VECTOR_DYNAMIC_ALLOCATED_TPP
