/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/hash.h>
#include <cml/vector/vector.h>
#include <cml/vector/traits.h>

/* Need specialization in std: */
namespace std {
template<class Element, class StorageType>
struct hash<cml::vector<Element, StorageType>>
{
  using vector_type = cml::vector<Element, StorageType>;

  std::size_t operator()(const vector_type& v) const
  {
    std::size_t seed = 0;
    std::hash<cml::value_type_of_t<vector_type>> hasher;
    for(int i = 0; i < v.size(); ++i)
      cml::detail::hash_combine(seed, hasher(v.get(i)));
    return seed;
  }
};
} // namespace std
