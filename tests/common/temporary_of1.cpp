/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/common/temporary.h>
#include <cml/scalar/traits.h>

/* Testing headers: */
#define BOOST_TEST_MODULE temporary_of1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(const_temporary1)
{
  typedef cml::temporary_of_t<const double> const_type;
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
