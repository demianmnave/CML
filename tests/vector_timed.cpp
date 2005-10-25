/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  XXX The tests should use a testing rig, but this can wait for now.
 */

#ifdef C_TIMED
#include <stdio.h>
#include <sys/time.h>

typedef double Vec[4];
inline void add(const Vec& a, const Vec& b, Vec& res)
{
    int i;
    for(i = 0; i < 4; ++ i)
        res[i] = a[i]+b[i];
}

inline void c_timed()
{
    struct timeval t_start, t_end;
    gettimeofday(&t_start,0);
    double v3[4];
    {
        double v1[4], v2[4];
        int i;
        v1[0] = 1.; v1[1] = 7.; v1[2] = 6.; v1[3] = 1.;
        v2[0] = 8.; v2[1] = 13.; v2[2] = 9.; v2[3] = 7.;
        for(i = 0; i < 10000000; ++ i) {
            add(v1,v2,v3);
        }
    }
    gettimeofday(&t_end,0);
    double t = (t_end.tv_sec - t_start.tv_sec)*1e6;
    t += (double)(t_end.tv_usec - t_start.tv_usec);
    printf("%.4g ms\n", t/1e3);

    /* Force result to be used: */
    printf("v3 = [");
    for(size_t i = 0; i < 4; ++ i) {
        printf(" %g", v3[i]);
    }
    printf(" ]\n");
}
#else

#include <iostream>
#include <cml/core/fixed.h>
#include <cml/core/dynamic.h>
#include <cml/vector.h>
#include <sys/time.h>

/* For convenience: */
using std::cerr;
using std::endl;

/* Note: this has to have the same template params as cml::vector<>: */
template<typename Element, class ArrayType> std::ostream&
operator<<(std::ostream& os, const cml::vector<Element,ArrayType>& v)
{
    os << "[";
    for(size_t i = 0; i < v.size(); ++ i) {
        os << " " << v[i];
    }
    os << " ]";
    return os;
}

inline void timed()
{
    using cml::core::fixed;
    typedef cml::vector< double, fixed<4> > vector_d4;

    struct timeval t_start, t_end;
    gettimeofday(&t_start,0);
    vector_d4 v3;
    {
        vector_d4 v1, v2;
        v1[0] = 1.; v1[1] = 7.; v1[2] = 6.; v1[3] = 1.;
        v2[0] = 8.; v2[1] = 13.; v2[2] = 9.; v2[3] = 7.;
#if 0
        cerr << "here!" << endl;
        v3 = v1+v2;
#else
        for(int i = 0; i < 10000000; ++ i) {
#if 0
            for(int k = 0; k < 4; ++ k) {
                v3[k] = v1[k]+v2[k];
            }
#else
            v3 = v1+v2;
#endif
        }
#endif
    }
    gettimeofday(&t_end,0);
    double t = (t_end.tv_sec - t_start.tv_sec)*1e6;
    t += (double)(t_end.tv_usec - t_start.tv_usec);
    printf("%.4g ms\n", t/1e3);

    /* Force result to be used: */
    cerr << "v3 = " << v3 << endl;
}
#endif

int main()
{
#ifdef C_TIMED
    c_timed();
#else
    timed();
#endif
    return 0;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
