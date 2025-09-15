/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/external_selector.h>
#include <cml/vector/writable_vector.h>
#include <cml/vector/vector.h>

/* Need const specializations with non-const for proper type trait
 * resolution:
 */
#include <cml/vector/fixed_const_external.h>

namespace cml {
template<class Element, int Size>
struct vector_traits<vector<Element, external<Size>>>
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
  using storage_type = rebind_t<external<Size>, vector_storage_tag>;
  using size_tag = typename storage_type::size_tag;
  static_assert(std::is_same<size_tag, fixed_size_tag>::value,
    "invalid size tag");

  /* Array size (should be positive): */
  static const int array_size = storage_type::array_size;
  static_assert(array_size > 0, "invalid vector size");
};

/** Fixed-length wrapped array pointer as a vector. */
template<class Element, int Size>
class vector<Element, external<Size>>
  : public writable_vector<vector<Element, external<Size>>>
{
  public:
  using vector_type = vector<Element, external<Size>>;
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
  /** Default construct with a null pointer. */
  vector();

  /** Construct from the wrapped pointer. */
  explicit vector(pointer data);

  /** Copy constructor.
   *
   * @warning This copy has the semantics of a raw pointer, and can lead
   * to memory leaks if not used correctly.
   */
  vector(const vector_type& other);

  /** Move constructor. */
  vector(vector_type&& other);

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
  /** Copy assignment.
   *
   * @warning This assignment has the semantics of a raw pointer, and can
   * lead to memory leaks if not used correctly.
   */
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
  /** Wrapped pointer. */
  pointer m_data;
};
} // namespace cml

template<typename E, int Size>
struct std::tuple_size<cml::vector<E, cml::external<Size>>>
{
  static const int value = Size;
};

template<std::size_t I, typename E, int Size>
struct std::tuple_element<I, cml::vector<E, cml::external<Size>>>
{
  using type = cml::value_type_of_t<cml::vector<E, cml::external<Size>>>;
};

#define __CML_VECTOR_FIXED_EXTERNAL_TPP
#include <cml/vector/fixed_external.tpp>
#undef __CML_VECTOR_FIXED_EXTERNAL_TPP
