/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * @todo Add a C library to avoid having to calculate the vector tests by
 * hand.
 */

{
    vector_type CONSTRUCT(w); assign(w, 1., 2., 3., 4.);
    vector_type CONSTRUCT(x); assign(x, 3., 1., 2., 4.);
    vector_type CONSTRUCT(y); assign(y, 1., 3., 2., 4.);
    vector_type CONSTRUCT(z); assign(z, 1., 2., 4., 3.);

    /* Unary: */
    vector_type COPY_ASSIGN(a) = + w;
    vector_type CONSTRUCT(a1);
    assign(a1,1.,2.,3.,4.);
    equal_or_fail(a,a1, ERROR_MSG_TAG "+ w");

    vector_type COPY_ASSIGN(b) = - x;
    vector_type CONSTRUCT(b1);
    assign(b1,-1.,-2.,-3.,-4.);
    equal_or_fail(a,a1, ERROR_MSG_TAG "- x");

    /* Binary: */
    vector_type COPY_ASSIGN(c) = x+y;
    vector_type CONSTRUCT(c1);
    assign(c1,4.,4.,4.,8.);
    equal_or_fail(c,c1, ERROR_MSG_TAG "x+y");

    vector_type COPY_CONSTRUCT(d,x-y);
    vector_type CONSTRUCT(d1);
    assign(d1,2.,-2.,0.,0.);
    equal_or_fail(d,d1, ERROR_MSG_TAG "x-y");

    vector_type COPY_CONSTRUCT(e,w);
    vector_type CONSTRUCT(e1);
    e += x+y-z;
    assign(e1,4.,4.,3.,9.);
    equal_or_fail(e,e1, ERROR_MSG_TAG "x+y-z");

    vector_type COPY_CONSTRUCT(f,2.*(x+y+z));
    vector_type CONSTRUCT(f1);
    assign(f1,10.,12.,16.,22.);
    equal_or_fail(f,f1, ERROR_MSG_TAG "2.*(x+y+z)");

    vector_type COPY_CONSTRUCT(g,2.*x+y);
    vector_type CONSTRUCT(g1);
    assign(g1,7.,5.,6.,12.);
    equal_or_fail(g,g1, ERROR_MSG_TAG "2.*x+y");

    vector_type CONSTRUCT(h);
    vector_type CONSTRUCT(h1);
    h = w/2.+x;
    assign(h1,3.5,2.,3.5,6.);
    equal_or_fail(h,h1, ERROR_MSG_TAG "w/2.+x");

    vector_type CONSTRUCT(i);
    vector_type CONSTRUCT(i1);
    i = (w+x)/2.;
    assign(i1,2.,1.5,2.5,4.);
    equal_or_fail(i,i1, ERROR_MSG_TAG "(w+x)/2.");

    vector_type COPY_CONSTRUCT(j,x);
    vector_type CONSTRUCT(j1);
    j *= 2.;
    assign(j1,6.,2.,4.,8.);
    equal_or_fail(i,i1, ERROR_MSG_TAG "(w+x)/2.");

    /* Dot: */
    double da = dot(w,x), da1 = 27.;
    equal_or_fail(da,da1, ERROR_MSG_TAG "dot(w,x)");

    double db = dot(w,x+y), db1 = 56.;
    equal_or_fail(db,db1, ERROR_MSG_TAG "dot(w,x+y)");

    double dc = dot(w+x,y+z), dc1 = 109.;
    equal_or_fail(dc,dc1, ERROR_MSG_TAG "dot(w+x,y-z)");

#if defined(CML_ENABLE_DOT_OPERATOR)
    /* Dot: */
    double da = w*x, da1 = 27.;
    equal_or_fail(da,da1, ERROR_MSG_TAG "w*x");

    double db = w*(x+y), db1 = 56.;
    equal_or_fail(db,db1, ERROR_MSG_TAG "w*(x+y)");

    double dc = (w+x)*(y+z), dc1 = 109.;
    equal_or_fail(dc,dc1, ERROR_MSG_TAG "(w+x)*(y-z)");
#endif
}

// -------------------------------------------------------------------------
// vim:ft=cpp
