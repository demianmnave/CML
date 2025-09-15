/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#ifndef __CML_MATRIX_TRACE_TPP
#  error "matrix/trace.tpp not included correctly"
#endif

#include <cml/matrix/readable_matrix.h>

namespace cml {
template<class Sub>
auto
trace(const readable_matrix<Sub>& M) -> value_type_trait_of_t<Sub>
{
  return M.trace();
}
} // namespace cml
