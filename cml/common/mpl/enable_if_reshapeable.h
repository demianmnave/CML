/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/common/mpl/is_reshapeable.h>

namespace cml {

/** Wrapper for enable_if to detect if @c T implements resize(m,n), where m
 * and n are convertible from int.
 */
template<class T>
struct enable_if_reshapeable : std::enable_if<is_reshapeable<T>::value>
{};

/** Convenience alias for enable_if_reshapeable. */
template<class T>
using enable_if_reshapeable_t = typename enable_if_reshapeable<T>::type;

}  // namespace cml
