/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_detail_combined_size_of_h
#define	cml_vector_detail_combined_size_of_h

namespace cml {
namespace detail {

template<class Sub, class... Elements> enable_if_fixed_size_t<Sub,
  cml::int_c<array_size_of_c<Sub>::value + int(sizeof...(Elements))>
  >
combined_size_of(const readable_vector<Sub>&, const Elements&...)
{
  return cml::int_c<array_size_of_c<Sub>::value + int(sizeof...(Elements))>();
}

template<class Sub, class... Elements>
  enable_if_dynamic_size_t<Sub, int>
combined_size_of(const readable_vector<Sub>& sub, const Elements&... eN)
{
  return sub.size() + int(sizeof...(eN));
}

} // namespace detail
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
