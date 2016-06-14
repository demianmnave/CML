/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector.h>

/* Testing headers: */
#define BOOST_TEST_MODULE vector_temporary1
#include <boost/test/unit_test.hpp>

/* Errors: */

/* temporary_of<> relied upon vector_traits<>, which is not specialized for
 * const types:
 */
BOOST_AUTO_TEST_CASE(const_temporary1)
{
  typedef cml::temporary_of_t<const cml::vector3d> const_type;
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
