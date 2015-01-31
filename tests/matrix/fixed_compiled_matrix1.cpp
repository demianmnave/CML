/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/matrix/fixed.h>
#include <cml/matrix/types.h>

/* Testing headers: */
#define BOOST_TEST_MODULE fixed_compiled_matrix1
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(typecheck)
{
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::matrix34d::basis_tag,cml::col_basis>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::matrix34d::layout_tag,cml::row_major>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::matrix34d_c::basis_tag,cml::col_basis>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<cml::matrix34d_c::layout_tag,cml::col_major>::value),
    true);
}

BOOST_AUTO_TEST_CASE(array_construct1)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::matrix34d M(aM);

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_construct2)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::matrix34d_c M(aM);

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_temp_construct1)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::matrix34d M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_temp_construct2)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::matrix34d_c M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_assign1)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::matrix34d M;
  M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array_assign2)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  cml::matrix34d_c M;
  M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_construct1)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d M(aM);

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_construct2)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d_c M(aM);

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_temp_construct1)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_temp_construct2)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d_c M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_assign1)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d M;
  M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(array2_assign2)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d_c M;
  M = aM;

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(elements_construct1)
{
  cml::matrix34d M(
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
    );

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(element_construct2)
{
  cml::matrix34d_c M(
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
    );

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(pointer_construct1)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d M(&aM[0][0]);

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(pointer_construct2)
{
  double aM[3][4] = {
    { 1.,  2.,  3.,  4. },
    { 5.,  6.,  7.,  8. },
    { 9.,  0.,  0.,  0. }
  };
  cml::matrix34d_c M(&aM[0][0]);

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_construct1)
{
  cml::matrix34d M {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_construct2)
{
  cml::matrix34d_c M {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_temp_construct1)
{
  cml::matrix34d M = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_temp_construct2)
{
  cml::matrix34d_c M = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_assign1)
{
  cml::matrix34d M;
  M = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(list_assign2)
{
  cml::matrix34d_c M;
  M = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };

  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_CHECK_EQUAL(M.data()[0], 1.);
  BOOST_CHECK_EQUAL(M(0,0), 1.);
  BOOST_CHECK_EQUAL(M(2,0), 9.);
  BOOST_CHECK_EQUAL(M(2,1), 0.);
  BOOST_CHECK_EQUAL(M(2,2), 0.);
  BOOST_CHECK_EQUAL(M(2,3), 0.);
}

BOOST_AUTO_TEST_CASE(size_check1)
{
  cml::matrix34d M;
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_THROW(
    (M = {
     1.,  2.,  3.,  4.,
     5.,  6.,  7.,  8.,
     9.
     }), cml::incompatible_matrix_size_error);
}

BOOST_AUTO_TEST_CASE(size_check2)
{
  cml::matrix34d_c M;
  BOOST_REQUIRE_EQUAL(M.rows(), 3);
  BOOST_REQUIRE_EQUAL(M.cols(), 4);
  BOOST_REQUIRE_THROW(
    (M = {
     1.,  2.,  3.,  4.,
     5.,  6.,  7.,  8.,
     9.
     }), cml::incompatible_matrix_size_error);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
