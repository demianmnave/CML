/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Bring CML public namespaces into namespace CML.
 */

#ifndef cml_h
#define cml_h

#include <cml/vector.h>
#include <cml/matrix.h>

/* Pull ops namespaces into cml: */
namespace cml {
  using namespace cml::vector_ops;
  using namespace cml::matvec_ops;
  using namespace cml::matrix_ops;
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
