/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <cml/quaternion/inverse_node.h>

namespace cml {

/** Return an expression node for the inverse part of @c q.  @c q is
 * stored by const reference in the node.
 */
template<class Sub>
auto inverse(const readable_quaternion<Sub>& q) -> inverse_node<const Sub&>;

/** Return an expression node for inverse part of the temporary
 * subexpression @c q. @c q is stored by value in the node (via std::move).
 */
template<class Sub>
auto inverse(readable_quaternion<Sub>&& q) -> inverse_node<Sub&&>;

}  // namespace cml

#define __CML_QUATERNION_INVERSE_OPS_TPP
#include <cml/quaternion/inverse_ops.tpp>
#undef __CML_QUATERNION_INVERSE_OPS_TPP
