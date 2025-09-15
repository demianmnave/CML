/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

namespace cml {
/** Helper to add two integral constants.
 *
 * @note This also avoids spurious VC14 "integral constant overflow"
 * warnings.
 */
template<int a, int b> struct plus_c
{
  static const int value = a + b;
};
} // namespace cml
