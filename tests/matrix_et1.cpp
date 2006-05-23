/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Test matrix expressions.
 *
 * Unary expressions (+,-):
 *
 * op Matrix -> Matrix
 * op MatXpr -> Matrix
 *
 * Matrix binary expressions (+,-):
 *
 * Matrix op Matrix -> Matrix
 * MatXpr op Matrix -> MatXpr
 * Matrix op MatXpr -> MatXpr
 * MatXpr op MatXpr -> MatXpr
 *
 * Matrix/scalar binary expressions (*,/):
 *
 * Matrix op Scalar -> Matrix
 * Scalar op Matrix -> Matrix
 * MatXpr op Scalar -> MatXpr
 * Scalar op MatXpr -> MatXpr
 *
 * Transpose (via temporary):
 *
 * transpose Matrix -> Matrix
 * transpose MatXpr -> Matrix
 *
 * Multiply (via mul() or operator*):
 *
 * Matrix * Matrix -> Scalar
 * MatXpr * Matrix -> Scalar
 * Matrix * MatXpr -> Scalar
 * MatXpr * MatXpr -> Scalar
 *
 * @sa cml/matrix_ops.h
 * @sa cml/matrix_mul.h
 * @sa cml/et/matrix_transpose.h
 */

#include <iostream>
#include <stdexcept>
#include <string>
#if defined(__ICC) && defined(__linux__) && (__ICC >= 900)
#include <math.h>
namespace std {
    using ::fabs;
}
#else
#include <cmath>
#endif

#include <cml/cml.h>

/* Prefix on error messages in single_- and mixed_vector_tests.ixx: */
#define ERROR_MSG_TAG \
    std::string(__FUNCTION__) + "@" + TO_STRING(__LINE__) + ": "

using std::cout;
using std::endl;
using namespace cml;

template<typename E, class AT, typename BO, class L> void
assign(
        cml::matrix<E,AT,BO,L>& m,
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22
      )
{
    m(0,0) = m00; m(0,1) = m01; m(0,2) = m02;
    m(1,0) = m10; m(1,1) = m11; m(1,2) = m12;
    m(2,0) = m20; m(2,1) = m21; m(2,2) = m22;
}

template<
    typename E1, class AT1, class L1,
    typename E2, class AT2, class L2,
    typename BO
> void
equal_or_fail(
        const cml::matrix<E1,AT1,BO,L1>& m1,
        const cml::matrix<E2,AT2,BO,L2>& m2,
        std::string msg = "matrix equality failed",
        double tol = 1e-8
        )
{
    matrix_size N = m1.size();
    for(size_t i = 0; i < N.first; ++ i)
        for(size_t j = 0; j < N.second; ++ j)
            if(std::fabs(m1(i,j)-m2(i,j)) > tol)
                throw std::runtime_error(msg);
}

void
equal_or_fail(
        double a,
        double b,
        std::string msg = "scalar equality failed",
        double tol = 1e-8
        )
{
    if(std::fabs(a-b) > tol) {
        throw std::runtime_error(msg);
    }
}

void fixed_test()
{
    typedef matrix<double, fixed<3,3>, col_basis, row_major> matrix_type;

#define CONSTRUCT(_a_) _a_
#define COPY_ASSIGN(_a_) _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(_e_)

#include "single_matrix_tests.ixx"

#undef CONSTRUCT
#undef COPY_ASSIGN
#undef COPY_CONSTRUCT
}

/* Note: dynamic matrices can be copy-constructed only if
 * CML_AUTOMATIC_MATRIX_RESIZE_ON_ASSIGNMENT is defined.
 */
void dynamic_test()
{
    typedef matrix<double, dynamic<>, col_basis, row_major> matrix_type;

#define CONSTRUCT(_a_) _a_(3,3)
#if defined(CML_AUTOMATIC_MATRIX_RESIZE_ON_ASSIGNMENT)
#define COPY_ASSIGN(_a_) _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(_e_)
#else
#define COPY_ASSIGN(_a_) _a_(3,3); _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(3,3); _a_ = (_e_)
#endif

#include "single_matrix_tests.ixx"

#undef CONSTRUCT
#undef COPY_ASSIGN
#undef COPY_CONSTRUCT
}

/* Note: external matrices cannot be copy-constructed, but they can be
 * assigned.
 */
void external_test()
{
    typedef matrix<double, external<3,3>, col_basis, row_major> matrix_type;

    /* Need the matrices to store to: */
    double _w[3][3], _x[3][3], _y[3][3], _z[3][3];

    /* These are used to initialize the tests: */
    double _a[3][3], _b[3][3], _c[3][3], _d[3][3];
    double _e[3][3], _f[3][3], _g[3][3], _h[3][3];
    double _i[3][3], _j[3][3];

    /* These are used to store the expected and test values: */
    double _a1[3][3], _b1[3][3], _c1[3][3], _d1[3][3];
    double _e1[3][3], _f1[3][3], _g1[3][3], _h1[3][3];
    double _j1[3][3], _i1[3][3];

#define CONSTRUCT(_a_) _a_(&_##_a_[0][0])
#define COPY_ASSIGN(_a_) _a_(&_##_a_[0][0]); _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(&_##_a_[0][0]); _a_ = _e_

#include "single_matrix_tests.ixx"

#undef CONSTRUCT
#undef COPY_ASSIGN
#undef COPY_CONSTRUCT
}

#if 0
void mixed_fixed_dynamic_test()
{
    typedef matrix<double, fixed<3,3>, col_basis, row_major> matrix_type1;
#define CONSTRUCT_1(_a_) _a_
#define COPY_ASSIGN_1(_a_) _a_
#define COPY_CONSTRUCT_1(_a_,_e_) _a_(_e_)


    typedef matrix<double, dynamic<>, col_basis, row_major> matrix_type2;
#define CONSTRUCT_2(_a_) _a_(3,3)
#if defined(CML_AUTOMATIC_MATRIX_RESIZE_ON_ASSIGNMENT)
#define COPY_ASSIGN_2(_a_) _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(_e_)
#else
#define COPY_ASSIGN_2(_a_) _a_(3,3); _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(3,3); _a_ = (_e_)
#endif

#include "mixed_matrix_tests.ixx"

#undef CONSTRUCT_1
#undef COPY_ASSIGN_1
#undef COPY_CONSTRUCT_1
#undef CONSTRUCT_2
#undef COPY_ASSIGN_2
#undef COPY_CONSTRUCT_2
}

void mixed_fixed_external_test()
{
    typedef matrix<double, fixed<3,3>, col_basis, row_major> matrix_type1;
#define CONSTRUCT_1(_a_) _a_
#define COPY_ASSIGN_1(_a_) _a_
#define COPY_CONSTRUCT_1(_a_,_e_) _a_(_e_)


    typedef matrix<double, external<3,3>, col_basis, row_major> matrix_type2;

    /* Need the matrices to store to (these are the ony ones used in the
     * tests):
     */
    double _y[3][3], _z[3][3];
    double _d[3][3], _f[3][3], _h[3][3];
    double _c1[3][3], _e1[3][3], _g1[3][3], _i1[3][3];

#define CONSTRUCT_2(_a_) _a_(_##_a_)
#define COPY_ASSIGN_2(_a_) _a_(_##_a_); _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(_##_a_); _a_ = _e_

#include "mixed_matrix_tests.ixx"

#undef CONSTRUCT_1
#undef COPY_ASSIGN_1
#undef COPY_CONSTRUCT_1
#undef CONSTRUCT_2
#undef COPY_ASSIGN_2
#undef COPY_CONSTRUCT_2
}

void mixed_dynamic_external_test()
{
    typedef matrix<double, fixed<3,3>, col_basis, row_major> matrix_type1;
#define CONSTRUCT_1(_a_) _a_
#define COPY_ASSIGN_1(_a_) _a_
#define COPY_CONSTRUCT_1(_a_,_e_) _a_(_e_)


    typedef matrix<double, external<3,3>, col_basis, row_major> matrix_type2;

    /* Need the matrices to store to (these are the ony ones used in the
     * tests):
     */
    double _y[3][3], _z[3][3];
    double _d[3][3], _f[3][3], _h[3][3];
    double _c1[3][3], _e1[3][3], _g1[3][3], _i1[3][3];

#define CONSTRUCT_2(_a_) _a_(&_##_a_[0][0])
#define COPY_ASSIGN_2(_a_) _a_(&_##_a_[0][0]); _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(&_##_a_[0][0]); _a_ = _e_

#include "mixed_matrix_tests.ixx"

#undef CONSTRUCT_1
#undef COPY_ASSIGN_1
#undef COPY_CONSTRUCT_1
#undef CONSTRUCT_2
#undef COPY_ASSIGN_2
#undef COPY_CONSTRUCT_2
}
#endif

int main()
{
    fixed_test();
    dynamic_test();
    external_test();
#if 0
    mixed_fixed_dynamic_test();
    mixed_fixed_external_test();
    mixed_dynamic_external_test();
#endif
}

// -------------------------------------------------------------------------
// vim:ft=cpp
