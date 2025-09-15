/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/vector/writable_vector.h>

namespace cml::detail {
/** No-op for non-resizable vector. */
template<class Sub>
void
resize(readable_vector<Sub>&, int)
{
}

/** Resize vectors that implement resize(). */
template<class Sub>
auto
resize(writable_vector<Sub>& sub, int size)
  -> decltype(sub.actual().resize(0), void())
{
  sub.actual().resize(size);
}
}
