/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

namespace cml {
/** Coordinate system handedness. */
enum AxisOrientation
{
  left_handed,
  right_handed
};

/** For CML1 compatibility. */
using Handedness = AxisOrientation;

/** Perspective clipping type. */
enum ZClip
{
  z_clip_neg_one,
  z_clip_zero
};
} // namespace cml
