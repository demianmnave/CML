/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#if 1
#define CML_ENABLE_MATRIX_BRACES // for operator[][] to load/print a matrix

#include <iostream>
#include <cml/cml.h>
using namespace cml;

/* For convenience: */
using std::cerr;
using std::endl;

typedef matrix<double, fixed<4,4>, cml::col_basis> matrix_d44;
#define MATINIT(_m_) _m_

#include "print_matrix.cpp"
#endif

#if 0
#include <iostream>

/* For convenience: */
using std::cerr;
using std::endl;

#define MATINIT(_m_) _m_
struct matrix_d44 {
  public:
    int rows() const { return 4; }
    int cols() const { return 4; }
    double operator()(int i, int j) const { return m_data[i][j]; }
    double& operator()(int i, int j) { return m_data[i][j]; }
    const double* operator[](int i) const { return &m_data[i][0]; }
    double* operator[](int i) { return &m_data[i][0]; }
  protected:
    double m_data[4][4];
};

/* Note: this has to have the same template params as cml::matrix<>: */
std::ostream&
operator<<(std::ostream& os, const matrix_d44& m)
{
    os << "[" << endl;
    for(size_t i = 0; i < m.rows(); ++i) {
        os << "  [";
        for(size_t j = 0; j < m.cols(); ++j) {
            os << " " << m[i][j];
        }
        os << "]" << endl;
    }
    os << "]";
    return os;
}
#endif

#if 0
#include <iostream>
#include <ltl/fmatrix.h>
using std::cerr;
using std::endl;
using namespace ltl;

typedef FMatrix<double,4,4> matrix_d44;
#define MATINIT(_v_) _v_
#endif

#include "matrix_algebra2.cpp"
#include "matrix_main2.cpp"

// -------------------------------------------------------------------------
// vim:ft=cpp
