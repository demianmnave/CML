/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#include "timing.cpp"

int main(int argc, char** argv)
{
    using std::cin;
    /* For external_vec_et1.cpp and external_c1.cpp: */
    double c_v[5][4];
    double c_m[5][4][4];
    int c_i = 0;

    matrix_d44 MATINIT(m), MATINIT(m1), MATINIT(m2), MATINIT(m3);
    vector_d4 VECINIT(v), VECINIT(v1), VECINIT(v2), VECINIT(v3), VECINIT(v4);

    int i, j;
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) m[i][j] = 0.;
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) cin >> m1[i][j];
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) cin >> m2[i][j];
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) cin >> m3[i][j];
    for(i = 0; i < 4; ++i) v[i] = 0.;
    std::cin >> v1[0] >> v1[1] >> v1[2] >> v1[3];
    std::cin >> v2[0] >> v2[1] >> v2[2] >> v2[3];
    std::cin >> v3[0] >> v3[1] >> v3[2] >> v3[3];
    std::cin >> v4[0] >> v4[1] >> v4[2] >> v4[3];


    //size_t n_iter = atoi(argv[1]);
    //size_t n_iter = 1000*1000*1000; //1 000 000 000
    size_t n_iter = 10*1000*1000; //10 000 000
    //size_t n_iter = 1*1000*1000; //10 000 000
    //size_t n_iter = 100000;
    //size_t n_iter = 1;


    if(argc == 2)
      n_iter = std::atol(argv[1]);

    usec_t t_start = usec_time();
    timed1(m,m1,m2,m3, v,v1,v2,v3,v4, n_iter);
    usec_t t_end = usec_time();
    double t = double(t_end - t_start);
    printf("%.4g s\n", t/1e6);

    /* Force result to be used: */
    cerr << "v = " << v << endl;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
