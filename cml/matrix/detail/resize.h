/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/matrix/writable_matrix.h>

namespace cml::detail {

/** No-op for non-resizable matrices. */
template<class Sub>
inline void
resize(readable_matrix<Sub>&, int, int)
{}

/** Resize matrices that implement resize(). */
template<class Sub>
inline auto
resize(writable_matrix<Sub>& sub, int rows, int cols)
  -> decltype(sub.actual().resize(0, 0), void())
{
  sub.actual().resize(rows, cols);
}

}
