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
-> cml::vector<value_type_trait_of_t<DT>,
  typename vector_traits<DT>::storage_traits::solid_type>
{
  return cml::vector<value_type_trait_of_t<DT>,
  typename vector_traits<DT>::storage_traits::solid_type>(v).normalize();
}

template<class DT> auto normalize(writable_vector<DT>&& v) -> DT&&
{
  return (DT&&) v.normalize();
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
