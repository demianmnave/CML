/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/int_c.h>
#include <cstdint>

namespace cml::detail {
/* Adapted from boost/functional/hash/hash.hpp> */
#if defined(_MSC_VER)
#  define CML_HASH_ROTL32(x, r) _rotl(x, r)
#else
#  define CML_HASH_ROTL32(x, r) ((x << r) | (x >> (32 - r)))
#endif

template<typename U32>
void
hash_combine_impl(U32& h1, U32 k1, cml::int_c<4>)
{
  constexpr auto c1 = UINT32_C(0xcc'9e'2d'51);
  constexpr auto c2 = UINT32_C(0x1b'87'35'93);

  k1 *= c1;
  k1 = CML_HASH_ROTL32(k1, 15);
  k1 *= c2;

  h1 ^= k1;
  h1 = CML_HASH_ROTL32(h1, 13);
  h1 = h1 * 5 + 0xe6'54'6b'64;
}

#undef CML_HASH_ROTL32

template<typename U64>
void
hash_combine_impl(U64& h, U64 k, cml::int_c<8>)
{
  constexpr auto m = UINT64_C(0xc6'a4'a7'93'5b'd1'e9'95);
  constexpr auto r = 47;

  k *= m;
  k ^= k >> r;
  k *= m;

  h ^= k;
  h *= m;

  // Completely arbitrary number, to prevent 0's
  // from hashing to 0.
  h += UINT64_C(0xe6'54'6b'64);
}

template<typename UInt>
void
hash_combine(UInt& h, UInt k)
{
  hash_combine_impl(h, k, cml::int_c<sizeof(UInt)>());
}

}  // namespace cml::detail
