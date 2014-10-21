/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_UNARY_OPS_TPP
#error "vector/unary_ops.tpp not included correctly"
#endif

namespace cml {

template<class Readable> inline auto
operator-(const readable_vector<Readable>& sub)
-> vector_unary_node<
	Readable, op::unary_minus<typename Readable::value_type>>
{
  return vector_unary_node<
    Readable, op::unary_minus<typename Readable::value_type>>(sub);
}

template<class Readable> inline auto
operator+(const readable_vector<Readable>& sub)
-> vector_unary_node<
	Readable, op::unary_plus<typename Readable::value_type>>
{
  return vector_unary_node<
    Readable, op::unary_plus<typename Readable::value_type>>(sub);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
