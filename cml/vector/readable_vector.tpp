/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_READABLE_VECTOR_TPP
#error "vector/readable_vector.tpp not included correctly"
#endif

namespace cml {

/* Public methods: */

template<class DT>
readable_vector<DT>::operator const DT& () const
{
  return actual();
}

template<class DT> auto
readable_vector<DT>::operator[](int i) const -> immutable_value
{
  return actual().get(i);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
