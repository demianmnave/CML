/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * @todo Add a C library to avoid having to calculate the matrix tests by
 * hand.
 */

{
    matrix_type CONSTRUCT(w);
    assign(w,
            1., 2., 3.,
            3., 1., 2.,
            1., 3., 2.
            );

    matrix_type CONSTRUCT(x);
    assign(x,
            3., 2., 3.,
            3., 2., 2.,
            1., 3., 1.
            );

    matrix_type CONSTRUCT(y);
    assign(y,
            1., 1., 1.,
            3., 1., 2.,
            1., 2., 2.
            );

    matrix_type CONSTRUCT(z);
    assign(z,
            1., 1., 3.,
            3., 3., 3.,
            1., 2., 1.
            );

    /* Unary: */
    matrix_type COPY_ASSIGN(a) = + w;
    matrix_type CONSTRUCT(a1);
    assign(a1,
            1., 2., 3.,
            3., 1., 2.,
            1., 3., 2.
            );
    equal_or_fail(a,a1, ERROR_MSG_TAG "+ w");

    matrix_type COPY_ASSIGN(b) = - x;
    matrix_type CONSTRUCT(b1);
    assign(b1,
            -1., -2., -3.,
            -3., -1., -2.,
            -1., -3., -2.
            );
    equal_or_fail(a,a1, ERROR_MSG_TAG "- x");

    /* Binary: */

    //   3., 2., 3., 3., 2., 2., 1., 3., 1.
    // + 1., 1., 1., 3., 1., 2., 1., 2., 2.
    //   4., 3., 4., 6., 3., 4., 2., 5., 3.
    matrix_type COPY_ASSIGN(c) = x+y;
    matrix_type CONSTRUCT(c1);
    assign(c1, 4., 3., 4., 6., 3., 4., 2., 5., 3.);
    equal_or_fail(c,c1, ERROR_MSG_TAG "x+y");


    //   3., 2., 3., 3., 2., 2., 1., 3., 1.
    // - 1., 1., 1., 3., 1., 2., 1., 2., 2.
    //   2., 1., 2., 0., 1., 0., 0., 1., -1.
    matrix_type COPY_CONSTRUCT(d,x-y);
    matrix_type CONSTRUCT(d1);
    assign(d1, 2., 1., 2., 0., 1., 0., 0., 1., -1.);
    equal_or_fail(d,d1, ERROR_MSG_TAG "x-y");


    //   1., 2., 3., 3., 1., 2., 1., 3., 2.
    // + 3., 2., 3., 3., 2., 2., 1., 3., 1.
    // + 1., 1., 1., 3., 1., 2., 1., 2., 2.
    // - 1., 1., 3., 3., 3., 3., 1., 2., 1.
    //   4., 4., 4., 6., 1., 3., 2., 6., 4.
    matrix_type COPY_CONSTRUCT(e,w);
    matrix_type CONSTRUCT(e1);
    e += x+y-z;
    assign(e1, 4., 4., 4., 6., 1., 3., 2., 6., 4.);
    equal_or_fail(e,e1, ERROR_MSG_TAG "x+y-z");

    //   3., 2., 3., 3., 2., 2., 1., 3., 1.
    // + 1., 1., 1., 3., 1., 2., 1., 2., 2.
    // + 1., 1., 3., 3., 3., 3., 1., 2., 1.
    //   5., 4., 7., 9., 6., 7., 3., 7., 4.
    // * 2.
    //   10., 8., 14., 18., 12., 14., 6., 14., 8.
    matrix_type COPY_CONSTRUCT(f,2.*(x+y+z));
    matrix_type CONSTRUCT(f1);
    assign(f1, 10., 8., 14., 18., 12., 14., 6., 14., 8.);
    equal_or_fail(f,f1, ERROR_MSG_TAG "2.*(x+y+z)");

    //   3., 2., 3., 3., 2., 2., 1., 3., 1.
    // * 2
    //   6., 4., 6., 6., 4., 4., 2., 6., 2.
    // + 1., 1., 1., 3., 1., 2., 1., 2., 2.
    //   7., 5., 7., 9., 5., 6., 3., 8., 4.
    matrix_type COPY_CONSTRUCT(g,2.*x+y);
    matrix_type CONSTRUCT(g1);
    assign(g1, 7., 5., 7., 9., 5., 6., 3., 8., 4.);
    equal_or_fail(g,g1, ERROR_MSG_TAG "2.*x+y");

    //   1., 2., 3., 3., 1., 2., 1., 3., 2.
    // / 2.
    //    .5, 1., 1.5, 1.5,  .5, 1.,  .5, 1.5, 1.
    // + 3. , 2., 3. , 3. , 2. , 2., 1. , 3. , 1.
    //   3.5, 3., 4.5, 4.5, 2.5, 3., 1.5, 4.5, 2.
    matrix_type CONSTRUCT(h);
    matrix_type CONSTRUCT(h1);
    h = w/2.+x;
    assign(h1, 3.5, 3., 4.5, 4.5, 2.5, 3., 1.5, 4.5, 2.);
    equal_or_fail(h,h1, ERROR_MSG_TAG "w/2.+x");

    //   1. , 2. , 3. , 3. , 1. , 2. , 1. , 3. , 2.
    // + 3. , 2. , 3. , 3. , 2. , 2. , 1. , 3. , 1.
    //   4. , 4. , 6. , 6. , 3. , 4. , 2. , 6. , 3.
    // / 2
    //   2. , 2. , 3. , 3. , 1.5, 2. , 1. , 3. , 1.5
    matrix_type CONSTRUCT(i);
    matrix_type CONSTRUCT(i1);
    i = (w+x)/2.;
    assign(i1, 2. , 2. , 3. , 3. , 1.5, 2. , 1. , 3. , 1.5);
    equal_or_fail(i,i1, ERROR_MSG_TAG "(w+x)/2.");

    //   3., 2., 3., 3., 2., 2., 1., 3., 1.
    // * 2
    //   6., 4., 6., 6., 4., 4., 2., 6., 2.
    matrix_type COPY_CONSTRUCT(j,x);
    matrix_type CONSTRUCT(j1);
    j *= 2.;
    assign(j1, 6., 4., 6., 6., 4., 4., 2., 6., 2.);
    equal_or_fail(i,i1, ERROR_MSG_TAG "(w+x)/2.");

#if 0
    /* Multiply: */
    double da = dot(w,x), da1 = 27.;
    equal_or_fail(da,da1, ERROR_MSG_TAG "dot(w,x)");

    double db = dot(w,x+y), db1 = 56.;
    equal_or_fail(db,db1, ERROR_MSG_TAG "dot(w,x+y)");

    double dc = dot(w+x,y+z), dc1 = 109.;
    equal_or_fail(dc,dc1, ERROR_MSG_TAG "dot(w+x,y-z)");

    /* Transpose (via temporary): */
    double dd = w*T(x), dd1 = 27.;
    equal_or_fail(dd,dd1, ERROR_MSG_TAG "w*T(x)");

    double de = w*T(x+y), de1 = 56.;
    equal_or_fail(de,de1, ERROR_MSG_TAG "w*T(x+y)");

    double df = (w+x)*T(y+z), df1 = 109.;
    equal_or_fail(df,df1, ERROR_MSG_TAG "(w+x)*T(y+z)");
#endif
}

// -------------------------------------------------------------------------
// vim:ft=cpp
