/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_WRITABLE_VECTOR_TPP
#error "vector/writable_vector.tpp not included correctly"
#endif

namespace cml {

/* Public methods: */

template<class DT>
writable_vector<DT>::operator DT& ()
{
  return actual();
}

template<class DT> auto
writable_vector<DT>::operator[](int i) -> mutable_value
{
  return actual().get(i);
}

template<class DT> template<class Other> DT&
writable_vector<DT>::operator=(std::initializer_list<Other> l)
{
  DT& self = actual();
  // cml::require_same_size(self, l);
  int i = 0; for(Other v : l) { self.set(i ++, v); }
  return self;
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
