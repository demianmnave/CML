/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_FUNCTIONS_TPP
#error "vector/functions.tpp not included correctly"
#endif

namespace cml {

template<class DT> auto
length_squared(const readable_vector<DT>& v) -> value_type_trait_of_t<DT>
{
  return v.length_squared();
}

template<class DT> auto
length(const readable_vector<DT>& v) -> value_type_trait_of_t<DT>
{
  return v.length();
}

template<class DT> auto normalize(const readable_vector<DT>& v)
-> typename temporary_of<DT>::type
{
  typedef typename temporary_of<DT>::type temporary_type;
  return temporary_type(v).normalize();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
