/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

{
    vector_type1 CONSTRUCT_1(w); assign(w, 1., 2., 3., 4.);
    vector_type1 CONSTRUCT_1(x); assign(x, 3., 1., 2., 4.);

    vector_type2 CONSTRUCT_2(y); assign(y, 1., 3., 2., 4.);
    vector_type2 CONSTRUCT_2(z); assign(z, 1., 2., 4., 3.);

    /* Binary, 2 vectors: */
    vector_type1 COPY_ASSIGN_1(c) = x+y;
    vector_type2 CONSTRUCT_2(c1);
    assign(c1,4.,4.,4.,8.);
    equal_or_fail(c,c1, ERROR_MSG_TAG "x+y");

    vector_type2 COPY_CONSTRUCT_2(d,x-y);
    vector_type1 CONSTRUCT_1(d1);
    assign(d1,2.,-2.,0.,0.);
    equal_or_fail(d,d1, ERROR_MSG_TAG "x-y");

    /* Binary, vectors and vector expressions: */
    vector_type1 CONSTRUCT_1(e);
    vector_type2 CONSTRUCT_2(e1);
    e = x+y-z;
    assign(e1,3.,2.,0.,5.);
    equal_or_fail(e,e1, ERROR_MSG_TAG "x+y-z");

    /* Binary, vectors and scalars: */
    vector_type2 COPY_CONSTRUCT_2(f,2.*(x+y+z));
    vector_type1 CONSTRUCT_1(f1);
    assign(f1,10.,12.,16.,22.);
    equal_or_fail(f,f1, ERROR_MSG_TAG "2.*(x+y+z)");

    vector_type1 COPY_CONSTRUCT_1(g,2.*x+y);
    vector_type2 CONSTRUCT_2(g1);
    assign(g1,7.,5.,6.,12.);
    equal_or_fail(g,g1, ERROR_MSG_TAG "2.*x+y");

    vector_type2 CONSTRUCT_2(h);
    vector_type1 CONSTRUCT_1(h1);
    h = w/2.+x;
    assign(h1,3.5,2.,3.5,6.);
    equal_or_fail(h,h1, ERROR_MSG_TAG "w/2.+x");

    vector_type1 CONSTRUCT_1(i);
    vector_type2 CONSTRUCT_2(i1);
    i = (w+x)/2.;
    assign(i1,2.,1.5,2.5,4.);
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
