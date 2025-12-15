/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

namespace cml {
/* fixed 'structors: */

template<class E, int R, int C, typename BO, typename L>
template<class Sub>
matrix<E, fixed<R, C>, BO, L>::matrix(const readable_matrix<Sub>& sub)
{
  this->assign(sub);
}

template<class E, int R, int C, typename BO, typename L>
template<class Array, enable_if_array_t<Array>*>
matrix<E, fixed<R, C>, BO, L>::matrix(const Array& array)
{
  this->assign(array);
}

template<class E, int R, int C, typename BO, typename L>
template<class Other, int R2, int C2>
matrix<E, fixed<R, C>, BO, L>::matrix(Other const (&array)[R2][C2])
{
  this->assign(array);
}

template<class E, int R, int C, typename BO, typename L>
template<class Pointer, enable_if_pointer_t<Pointer>*>
matrix<E, fixed<R, C>, BO, L>::matrix(const Pointer& array)
{
  this->assign(array);
}

template<class E, int R, int C, typename BO, typename L>
template<class Other>
matrix<E, fixed<R, C>, BO, L>::matrix(std::initializer_list<Other> l)
{
  this->assign(l);
}

/* Public methods: */

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::data() -> pointer
{
  return &this->m_data[0][0];
}

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::data() const -> const_pointer
{
  return &this->m_data[0][0];
}

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::begin() const -> const_pointer
{
  return &this->m_data[0][0];
}

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::end() const -> const_pointer
{
  return (&this->m_data[0][0]) + R * C;
}

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::operator=(const matrix_type& other)
  -> matrix_type&
{
  return this->assign(other);
}

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::operator=(matrix_type&& other) -> matrix_type&
{
  return this->assign(std::forward<matrix_type>(other));
}

/* Internal methods: */

/* readable_matrix interface: */

template<class E, int R, int C, typename BO, typename L>
int
matrix<E, fixed<R, C>, BO, L>::i_rows() const
{
  return R;
}

template<class E, int R, int C, typename BO, typename L>
int
matrix<E, fixed<R, C>, BO, L>::i_cols() const
{
  return C;
}

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::i_get(int i, int j) const -> immutable_value
{
  return s_access(*this, i, j, layout_tag());
}

/* writable_matrix interface: */

template<class E, int R, int C, typename BO, typename L>
auto
matrix<E, fixed<R, C>, BO, L>::i_get(int i, int j) -> mutable_value
{
  return s_access(*this, i, j, layout_tag());
}

template<class E, int R, int C, typename BO, typename L>
template<class Other>
auto
matrix<E, fixed<R, C>, BO, L>::i_put(int i, int j,
  const Other& v) & -> matrix_type&
{
  s_access(*this, i, j, layout_tag()) = value_type(v);
  return *this;
}

template<class E, int R, int C, typename BO, typename L>
template<class Other>
auto
matrix<E, fixed<R, C>, BO, L>::i_put(int i, int j,
  const Other& v) && -> matrix_type&&
{
  s_access(*this, i, j, layout_tag()) = v;
  return std::move(*this);
}
} // namespace cml
