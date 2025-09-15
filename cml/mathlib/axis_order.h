/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <tuple>
#include <cml/mathlib/euler_order.h>

namespace cml {
/** Specify 3D axis ordering. */
enum axis_order
{
  axis_order_xyz = euler_order_xyz, // 0x00 [0000]
  axis_order_xzy = euler_order_xzy, // 0x02 [0010]
  axis_order_yzx = euler_order_yzx, // 0x04 [0100]
  axis_order_yxz = euler_order_yxz, // 0x06 [0110]
  axis_order_zxy = euler_order_zxy, // 0x08 [1000]
  axis_order_zyx = euler_order_zyx  // 0x0A [1010]
};

/** Specify 2D axis ordering. */
enum axis_order2D
{
  axis_order_xy = axis_order_xyz, // 0x00 [0000]
  axis_order_yx = axis_order_yxz, // 0x06 [0110]
};

/** For CML1 compatibility. */
using AxisOrder = axis_order;
using AxisOrder2D = axis_order2D;

constexpr std::tuple<int, int, int, bool>
unpack_axis_order(axis_order order)
{
  constexpr auto ODD = 0x02;
  constexpr auto AXIS = 0x0C;

  auto odd = ((order & ODD) == ODD);
  auto offset = odd;
  auto i = (order & AXIS) % 3;
  auto j = (i + 1 + offset) % 3;
  auto k = (i + 2 - offset) % 3;
  return {i, j, k, odd};
}

inline void
unpack_axis_order(axis_order order, int& i, int& j, int& k, bool& odd)
{
  std::tie(i, j, k, odd) = unpack_axis_order(order);
}

constexpr std::tuple<int, int, bool>
unpack_axis_order2D(axis_order2D order)
{
  constexpr auto ODD = 0x02;
  constexpr auto AXIS = 0x0C;

  auto odd = ((order & ODD) == ODD);
  auto offset = odd;
  auto i = (order & AXIS) % 3;
  auto j = (i + 1 + offset) % 3;
  return {i, j, odd};
}

inline void
unpack_axis_order2D(axis_order2D order, int& i, int& j, bool& odd)
{
  std::tie(i, j, odd) = unpack_axis_order2D(order);
}

constexpr axis_order
pack_axis_order(int i, bool odd)
{
  return static_cast<axis_order>((i << 2) | (static_cast<int>(odd) << 1));
}

constexpr axis_order
swap_axis_order(axis_order order)
{
  auto [i, j, k, odd] = unpack_axis_order(order);
  return pack_axis_order(j, !odd);
}
} // namespace cml
