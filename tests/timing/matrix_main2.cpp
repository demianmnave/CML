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
    matrix_d44 MATINIT(m), MATINIT(m1), MATINIT(m2), MATINIT(m3);

    int i, j;
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) m[i][j] = 0.;
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) cin >> m1[i][j];
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) cin >> m2[i][j];
    for(i = 0; i < 4; ++i) for(j = 0; j < 4; ++j) cin >> m3[i][j];


    //size_t n_iter = atoi(argv[1]);
    //size_t n_iter = 1000*1000*1000; //1 000 000 000
    size_t n_iter = 10*1000*1000; //10 000 000
    //size_t n_iter = 1*1000*1000; //1 000 000
    //size_t n_iter = 100000;
    //size_t n_iter = 10000;
    //size_t n_iter = 1;


    if(argc == 2)
      n_iter = std::atol(argv[1]);

    usec_t t_start = usec_time();
    timed2(m,m1,m2,m3, n_iter);
    usec_t t_end = usec_time();
    double t = double(t_end - t_start);
    printf("%.4g s\n", t/1e6);

    /* Force result to be used: */
    cerr << "m = " << m << endl;
}

// -------------------------------------------------------------------------
// vim:ft=cpp
