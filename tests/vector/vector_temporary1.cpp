/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <cml/vector.h>

/* Testing headers: */
#include "catch_runner.h"

/* Errors: */

/* temporary_of<> relied upon vector_traits<>, which is not specialized for
 * const types:
 */
CATCH_TEST_CASE("const_temporary1")
{
  using const_type = cml::temporary_of_t<const cml::vector3d>;
}
