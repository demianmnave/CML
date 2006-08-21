/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Test vector expressions.
 *
 * Unary expressions (+,-):
 *
 * op Vector -> Vector
 * op VecXpr -> Vector
 *
 * Vector binary expressions (+,-):
 *
 * Vector op Vector -> Vector
 * VecXpr op Vector -> VecXpr
 * Vector op VecXpr -> VecXpr
 * VecXpr op VecXpr -> VecXpr
 *
 * Vector/scalar binary expressions (*,/):
 *
 * Vector op Scalar -> Vector
 * Scalar op Vector -> Vector
 * VecXpr op Scalar -> VecXpr
 * Scalar op VecXpr -> VecXpr
 *
 * Dot (via dot() or operator*):
 *
 * Vector dot Vector -> Scalar
 * VecXpr dot Vector -> Scalar
 * Vector dot VecXpr -> Scalar
 * VecXpr dot VecXpr -> Scalar
 *
 * @sa cml/vector_ops.h
 * @sa cml/vector_dot.h
 *
 * @todo Add tests for outer().
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

template<typename E, class AT> void
assign(cml::vector<E,AT>& v, double a, double b, double c, double d) {
    v[0] = a; v[1] = b; v[2] = c; v[3] = d;
}

template<
    typename E1, class AT1,
    typename E2, class AT2
> void
equal_or_fail(
        const cml::vector<E1,AT1>& v1,
        const cml::vector<E2,AT2>& v2,
        std::string msg = "vector equality failed",
        double tol = 1e-8
        )
{
    size_t N = v1.size();
    for(size_t i = 0; i < N; ++ i)
        if(std::fabs(v1[i]-v2[i]) > tol)
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
    typedef vector< double, fixed<4> > vector_type;

#define CONSTRUCT(_a_) _a_
#define COPY_ASSIGN(_a_) _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(_e_)

#include "single_vector_tests.ixx"

#undef CONSTRUCT
#undef COPY_ASSIGN
#undef COPY_CONSTRUCT
}

/* Note: dynamic vectors can be copy-constructed only if
 * CML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT is defined.
 */
void dynamic_test()
{
    typedef vector< double, dynamic<> > vector_type;

#define CONSTRUCT(_a_) _a_(4)
#if defined(CML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT)
#define COPY_ASSIGN(_a_) _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(_e_)
#else
#define COPY_ASSIGN(_a_) _a_(4); _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(4); _a_ = (_e_)
#endif

#include "single_vector_tests.ixx"

#undef CONSTRUCT
#undef COPY_ASSIGN
#undef COPY_CONSTRUCT
}

/* Note: external vectors cannot be copy-constructed, but they can be
 * assigned.
 */
void external_test()
{
    typedef vector< double, external<4> > vector_type;

    /* Need the vectors to store to: */
    double _w[4], _x[4], _y[4], _z[4];

    /* These are used to initialize the tests: */
    double _a[4], _b[4], _c[4], _d[4];
    double _e[4], _f[4], _g[4], _h[4];
    double _i[4], _j[4];

    /* These are used to store the expected and test values: */
    double _a1[4], _b1[4], _c1[4], _d1[4];
    double _e1[4], _f1[4], _g1[4], _h1[4];
    double _j1[4], _i1[4];

#define CONSTRUCT(_a_) _a_(_##_a_)
#define COPY_ASSIGN(_a_) _a_(_##_a_); _a_
#define COPY_CONSTRUCT(_a_,_e_) _a_(_##_a_); _a_ = _e_

#include "single_vector_tests.ixx"

#undef CONSTRUCT
#undef COPY_ASSIGN
#undef COPY_CONSTRUCT
}

void mixed_fixed_dynamic_test()
{
    typedef vector< double, fixed<4> > vector_type1;
#define CONSTRUCT_1(_a_) _a_
#define COPY_ASSIGN_1(_a_) _a_
#define COPY_CONSTRUCT_1(_a_,_e_) _a_(_e_)


    typedef vector< double, dynamic<> > vector_type2;
#define CONSTRUCT_2(_a_) _a_(4)
#if defined(CML_AUTOMATIC_VECTOR_RESIZE_ON_ASSIGNMENT)
#define COPY_ASSIGN_2(_a_) _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(_e_)
#else
#define COPY_ASSIGN_2(_a_) _a_(4); _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(4); _a_ = (_e_)
#endif

#include "mixed_vector_tests.ixx"

#undef CONSTRUCT_1
#undef COPY_ASSIGN_1
#undef COPY_CONSTRUCT_1
#undef CONSTRUCT_2
#undef COPY_ASSIGN_2
#undef COPY_CONSTRUCT_2
}

void mixed_fixed_external_test()
{
    typedef vector< double, fixed<4> > vector_type1;
#define CONSTRUCT_1(_a_) _a_
#define COPY_ASSIGN_1(_a_) _a_
#define COPY_CONSTRUCT_1(_a_,_e_) _a_(_e_)


    typedef vector< double, external<4> > vector_type2;

    /* Need the vectors to store to (these are the ony ones used in the
     * tests):
     */
    double _y[4], _z[4];
    double _d[4], _f[4], _h[4];
    double _c1[4], _e1[4], _g1[4], _i1[4];

#define CONSTRUCT_2(_a_) _a_(_##_a_)
#define COPY_ASSIGN_2(_a_) _a_(_##_a_); _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(_##_a_); _a_ = _e_

#include "mixed_vector_tests.ixx"

#undef CONSTRUCT_1
#undef COPY_ASSIGN_1
#undef COPY_CONSTRUCT_1
#undef CONSTRUCT_2
#undef COPY_ASSIGN_2
#undef COPY_CONSTRUCT_2
}

void mixed_dynamic_external_test()
{
    typedef vector< double, fixed<4> > vector_type1;
#define CONSTRUCT_1(_a_) _a_
#define COPY_ASSIGN_1(_a_) _a_
#define COPY_CONSTRUCT_1(_a_,_e_) _a_(_e_)


    typedef vector< double, external<4> > vector_type2;

    /* Need the vectors to store to (these are the ony ones used in the
     * tests):
     */
    double _y[4], _z[4];
    double _d[4], _f[4], _h[4];
    double _c1[4], _e1[4], _g1[4], _i1[4];

#define CONSTRUCT_2(_a_) _a_(_##_a_)
#define COPY_ASSIGN_2(_a_) _a_(_##_a_); _a_
#define COPY_CONSTRUCT_2(_a_,_e_) _a_(_##_a_); _a_ = _e_

#include "mixed_vector_tests.ixx"

#undef CONSTRUCT_1
#undef COPY_ASSIGN_1
#undef COPY_CONSTRUCT_1
#undef CONSTRUCT_2
#undef COPY_ASSIGN_2
#undef COPY_CONSTRUCT_2
}

int main()
{
    fixed_test();
    dynamic_test();
#if 0
    external_test();
    mixed_fixed_dynamic_test();
    mixed_fixed_external_test();
    mixed_dynamic_external_test();
#endif
}

// -------------------------------------------------------------------------
// vim:ft=cpp
