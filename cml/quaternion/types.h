/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/storage/selectors.h>
#include <cml/quaternion/quaternion.h>

namespace cml {

/** @defgroup quaternion_types Predefined Quaternion Types */
/*@{*/

// Imaginary first, positive cross:
using quaternionf_ip = quaternion<float, fixed<>, imaginary_first, positive_cross>;
using quaternionf_p = quaternion<float, fixed<>, imaginary_first, positive_cross>;
using quaternionf = quaternion<float>;

using quaterniond_ip = quaternion<double, fixed<>, imaginary_first, positive_cross>;
using quaterniond_p = quaternion<double, fixed<>, imaginary_first, positive_cross>;
using quaterniond = quaternion<double>;


// Imaginary first, negative cross:
using quaternionf_in = quaternion<float, fixed<>, imaginary_first, negative_cross>;
using quaternionf_n = quaternion<float, fixed<>, imaginary_first, negative_cross>;

using quaterniond_in = quaternion<double, fixed<>, imaginary_first, negative_cross>;
using quaterniond_n = quaternion<double, fixed<>, imaginary_first, negative_cross>;


// Real first, positive cross:
using quaternionf_rp = quaternion<float, fixed<>, real_first, positive_cross>;
using quaterniond_rp = quaternion<double, fixed<>, real_first, positive_cross>;


// Real first, negative cross:
using quaternionf_rn = quaternion<float, fixed<>, real_first, negative_cross>;
using quaterniond_rn = quaternion<double, fixed<>, real_first, negative_cross>;

/*@}*/

}  // namespace cml
