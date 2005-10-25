/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  XXX The tests should use a testing rig, but this can wait for now.
 */

#include <iostream>
#include <cml/core/fixed.h>
#include <cml/core/dynamic.h>
#include <cml/matrix.h>

/* For convenience: */
using std::cerr;
using std::endl;

/* Note: this has to have the same template params as cml::matrix<>: */
template<typename Element, class ArrayType, typename Orient> std::ostream&
operator<<(std::ostream& os, const cml::matrix<Element,ArrayType,Orient>& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < m.rows(); ++ i) {
        os << "  [";
        for(size_t j = 0; j < m.cols(); ++ j) {
            os << " " << m(i,j);
        }
        os << " ]" << endl;
    }
    os << "]" << endl;
    return os;
}

/** Test const access into the matrix. */
template<class M>
void const_test(const char* n, const M& m)
{
  cerr << "const " << n << "(1,2) = " << m(1,2) << endl;
}

/** Try to create static and dynamic matrices.
 *
 * @return 0 if the test was successful.
 */
int instance_test()
{
  using cml::core::fixed;
  using cml::core::dynamic;
  using cml::row_major;
  using cml::col_major;

  typedef cml::matrix<double, fixed<4,4>, row_major> matrix_d4_4r;
  typedef cml::matrix<double, fixed<4,4>, col_major> matrix_d4_4c;

  typedef cml::matrix<double, dynamic<>, row_major> matrix_dr;
  typedef cml::matrix<double, dynamic<>, col_major> matrix_dc;

  matrix_d4_4r m1;
  matrix_d4_4c m2;
  matrix_dr m3(4,4);
  matrix_dc m4(4,4);

  cerr << "m1 size = (" << m1.rows() << "x" << m1.cols() << ")" << endl;
  cerr << "m3 size = (" << m3.rows() << "x" << m3.cols() << ")" << endl;
  
  m1(1,2) = m2(1,2) = m3(1,2) = m4(1,2) = 6.;
  cerr << "m1(1,2) = " << m1(1,2) << endl;
  cerr << "m2(1,2) = " << m2(1,2) << endl;
  cerr << "m3(1,2) = " << m4(1,2) << endl;
  cerr << "m4(1,2) = " << m4(1,2) << endl;
  cerr << "m1(2) = " << m1(2) << endl;

  const_test("m1", m1);
  const_test("m3", m3);

  return 0;
}

int main()
{
  return instance_test();
}

// -------------------------------------------------------------------------
// vim:ft=cpp
