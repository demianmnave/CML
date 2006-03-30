/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * @note GCC4 requires a copy constructor to elide---it won't elide a
 * compiler-generated copy constructor!
 */

#ifndef matrix_class_ops_h
#define matrix_class_ops_h

/** Copy-construct a matrix from a fixed-size array of values. */
#define CML_MAT_COPY_FROM_FIXED_ARRAY(_R_,_C_)                      \
matrix(value_type m[_R_][_C_]) {                                    \
    typedef et::OpAssign<Element,Element> OpT;                      \
    cml::matrix< value_type, external<_R_,_C_> > src(&m[0][0]);     \
    et::UnrollAssignment<OpT>(*this,src);                           \
}

/** Copy this matrix from another using the given elementwise op.
 *
 * @internal This is required for GCC4, since it won't elide the default
 * copy constructor.
 */
#define CML_MAT_COPY_FROM_MATTYPE                                   \
matrix(const matrix_type& m) {                                      \
    typedef et::OpAssign <Element,Element> OpT;                     \
    et::UnrollAssignment<OpT>(*this,m);                             \
}

/** Copy this matrix from another using the given elementwise op.
 *
 * This allows copies from arbitrary matrix types.
 */
#define CML_MAT_COPY_FROM_MAT                                       \
template<typename E, class AT, typename L>                          \
matrix(const matrix<E,AT,L>& m) {                                   \
    typedef et::OpAssign <Element,E> OpT;                           \
    et::UnrollAssignment<OpT>(*this,m);                             \
}

/** Declare a function to copy this matrix from a matrix expression. */
#define CML_MAT_COPY_FROM_MATXPR                                    \
template<class XprT>                                                \
matrix(MATXPR_ARG_TYPE e) {                                         \
    /* Verify that a promotion exists at compile time: */           \
    typedef typename et::MatrixPromote<                             \
        matrix_type, typename XprT::result_type>::type result_type; \
    typedef typename XprT::value_type src_value_type;               \
    typedef et::OpAssign <Element,src_value_type> OpT;              \
    et::UnrollAssignment<OpT>(*this,e);                             \
}

#if defined(CML_USE_GENERATED_MATRIX_ASSIGN_OP)
#define CML_MAT_ASSIGN_FROM_MATTYPE
#else
/** Assign from the same matrix type.
 *
 * @param m the matrix to copy from.
 *
 * @note This is required for GCC4, otherwise it generates a slow
 * assignment operator using memcpy.
 *
 * @note ICC9/Linux-x86 seems to prefer its own assignment operator (need
 * to figure out why).
 */
#define CML_MAT_ASSIGN_FROM_MATTYPE                                 \
matrix_type& operator=(const matrix_type& m) {                      \
    typedef et::OpAssign<Element,Element> OpT;                      \
    et::UnrollAssignment<OpT>(*this,m);                             \
    return *this;                                                   \
}
#endif


/** Assign this matrix from another using the given elementwise op.
 *
 * This allows assignment from arbitrary matrix types.
 *
 * @param _op_ the operator (e.g. +=)
 * @param _op_name_ the op functor (e.g. et::OpAssign)
 */
#define CML_MAT_ASSIGN_FROM_MAT(_op_, _op_name_)                    \
template<typename E, class AT, typename L> matrix_type&             \
operator _op_ (const matrix<E,AT,L>& m) {                           \
    typedef _op_name_ <Element,E> OpT;                              \
    et::UnrollAssignment<OpT>(*this,m);                             \
    return *this;                                                   \
}

/** Declare a function to assign this matrix from a matrix expression.
 *
 * @param _op_ the operator (e.g. +=)
 * @param _op_name_ the op functor (e.g. et::OpAssign)
 */
#define CML_MAT_ASSIGN_FROM_MATXPR(_op_, _op_name_)                 \
template<class XprT> matrix_type&                                   \
operator _op_ (MATXPR_ARG_TYPE e) {                                 \
    /* Verify that a promotion exists at compile time: */           \
    typedef typename et::MatrixPromote<                             \
        matrix_type, typename XprT::result_type>::type result_type; \
    typedef typename XprT::value_type src_value_type;               \
    typedef _op_name_ <Element,src_value_type> OpT;                 \
    et::UnrollAssignment<OpT>(*this,e);                             \
    return *this;                                                   \
}

/** Declare a function to assign this matrix from a scalar.
 *
 * @param _op_ the operator (e.g. +=)
 * @param _op_name_ the op functor (e.g. et::OpAssign)
 *
 * @internal This shouldn't be used for ops, like +=, which aren't
 * defined in vector algebra.
 */
#define CML_MAT_ASSIGN_FROM_SCALAR(_op_, _op_name_)                 \
matrix_type& operator _op_ (const value_type s) {                   \
    typedef _op_name_ <Element,value_type> OpT;                     \
    et::UnrollAssignment<OpT>(*this,s);                             \
    return *this;                                                   \
}

/* These should only be used for testing: */
#define CML_MATRIX_BRACE_OPERATORS                                  \
template<class Matrix> struct row_ref {                             \
    typedef typename Matrix::reference reference;                   \
    reference operator[](size_t col) { return m(row,col); }         \
    Matrix& m;                                                      \
    size_t row;                                                     \
};                                                                  \
                                                                    \
template<class Matrix> struct const_row_ref {                       \
    typedef typename Matrix::const_reference const_reference;       \
    const_reference operator[](size_t col) const { return m(row,col); }\
    const Matrix& m;                                                \
    size_t row;                                                     \
};                                                                  \
                                                                    \
row_ref<matrix_type> operator[](size_t row) {                       \
    row_ref<matrix_type> ref = { *this, row }; return ref;          \
}                                                                   \
                                                                    \
const_row_ref<matrix_type> operator[](size_t row) const {           \
    const_row_ref<matrix_type> ref = { *this, row }; return ref;    \
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
