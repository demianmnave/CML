/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_binary_ops_h
#define	cml_vector_binary_ops_h

#include <cml/common/scalar_binary_ops.h>
#include <cml/vector/binary_node.h>

namespace cml {

/** Return an expression node for binary minus (pairwise subtraction) over
 * the elements of the sub-expressions @c sub1 and @c sub2.
 */
template<class Sub1, class Sub2> auto
operator-(
  const readable_vector<Sub1>& sub1,
  const readable_vector<Sub2>& sub2
  )
-> vector_binary_node<Sub1, Sub2,
  op::binary_minus<typename Sub1::value_type, typename Sub2::value_type>>;

/** Return an expression node for binary plus (pairwise addition) over the
 * elements of the sub-expressions @c sub1 and @c sub2.
 */
template<class Sub1, class Sub2> auto
operator+(
  const readable_vector<Sub1>& sub1,
  const readable_vector<Sub2>& sub2
  )
-> vector_binary_node<Sub1, Sub2,
  op::binary_plus<typename Sub1::value_type, typename Sub2::value_type>>;

} // namespace cml

#define __CML_VECTOR_BINARY_OPS_TPP
#include <cml/vector/binary_ops.tpp>
#undef __CML_VECTOR_BINARY_OPS_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
