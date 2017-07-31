/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef cml_util_vector_hash_h
#define cml_util_vector_hash_h

#include <cstdint>
#include <functional>
#include <cml/vector/vector.h>
#include <cml/vector/traits.h>

namespace cml {
namespace detail {

/* From boost/functional/hash/hash.hpp> */
#if defined(_MSC_VER)
#define _HASH_ROTL32(x, r) _rotl(x,r)
#else
#define _HASH_ROTL32(x, r) ((x << r) | (x >> (32 - r)))
#endif

inline void
hash_combine(std::uint32_t& h1, std::uint32_t k1)
{
  const auto c1 = UINT32_C(0xcc9e2d51);
  const auto c2 = UINT32_C(0x1b873593);

  k1 *= c1;
  k1 = _HASH_ROTL32(k1, 15);
  k1 *= c2;

  h1 ^= k1;
  h1 = _HASH_ROTL32(h1, 13);
  h1 = h1 * 5 + 0xe6546b64;
}

#undef _CML_HASH_ROTL32

inline void
hash_combine(std::uint64_t& h, std::uint64_t k)
{
  const auto m = UINT64_C(0xc6a4a7935bd1e995);
  const auto r = 47;

  k *= m;
  k ^= k >> r;
  k *= m;

  h ^= k;
  h *= m;

  // Completely arbitrary number, to prevent 0's
  // from hashing to 0.
  h += 0xe6546b64;
}

}
}

/* Need specialization in std: */
namespace std {
template<class Element, class StorageType>
struct hash<cml::vector<Element,StorageType>>
{
  typedef cml::vector<Element,StorageType> vector_type;
  inline std::size_t operator()(const vector_type& v) const {
    std::size_t seed = 0;
    std::hash<cml::value_type_of_t<vector_type>> hasher;
    for(int i = 0; i < v.size(); ++ i)
      cml::detail::hash_combine(seed, hasher(v.get(i)));
    return seed;
  }
};
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
