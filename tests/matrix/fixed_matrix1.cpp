/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <typeinfo>
#include <cml/matrix/fixed.h>

/* Testing headers: */
#define BOOST_TEST_MODULE fixed_matrix1
#include <boost/test/unit_test.hpp>

// For future reference...
#if 0
  for(int i = 0; i < M.rows(); ++ i) {
    std::clog << "... row " << i << std::endl;
    for(int j = 0; j < M.cols(); ++ j) {
      std::clog << " = " << M(i,j) << std::endl;
    }
  }
#endif

typedef cml::matrix<double, cml::fixed<3,4>> matrix1_t;
typedef cml::matrix<double, cml::fixed<3,4>,
	cml::col_basis, cml::col_major> matrix2_t;

BOOST_AUTO_TEST_CASE(typecheck)
{
  BOOST_CHECK_EQUAL(
    (std::is_same<matrix1_t::basis_tag,cml::col_basis>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<matrix1_t::layout_tag,cml::row_major>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<matrix2_t::basis_tag,cml::col_basis>::value),
    true);
  BOOST_CHECK_EQUAL(
    (std::is_same<matrix2_t::layout_tag,cml::col_major>::value),
    true);
}

BOOST_AUTO_TEST_CASE(array_construct1)
{
  double aM[] = {
    1.,  2.,  3.,  4.,
    5.,  6.,  7.,  8.,
    9.,  0.,  0.,  0.
  };
  matrix1_t M(aM);

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
  matrix2_t M(aM);

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
  matrix1_t M = aM;

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
  matrix2_t M = aM;

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
  matrix1_t M;
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
  matrix2_t M;
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
  matrix1_t M(aM);

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
  matrix2_t M(aM);

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
  matrix1_t M = aM;

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
  matrix2_t M = aM;

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
  matrix1_t M;
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
  matrix2_t M;
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
  matrix1_t M(
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
  matrix2_t M(
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

BOOST_AUTO_TEST_CASE(list_construct1)
{
  matrix1_t M {
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
  matrix2_t M {
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
  matrix1_t M = {
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
  matrix2_t M = {
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
  matrix1_t M;
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
  matrix2_t M;
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
  matrix1_t M;
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
  matrix2_t M;
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
