/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <cml/common/temporary.h>
#include <cml/scalar/traits.h>

/* Testing headers: */
#include "catch_runner.h"

CATCH_TEST_CASE("const_temporary1")
{
  using const_type = cml::temporary_of_t<const double>;
  CATCH_CHECK(std::is_same_v<const_type, const double>);
}
