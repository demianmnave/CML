/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_class_ops_h
#define matrix_class_ops_h

#include <cml/et/scalar_ops.h>
#include <cml/matrix/matrix_expr.h>

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
matrix(const et::MatrixXpr<XprT>& expr) {                           \
    /* Verify that a promotion exists at compile time: */           \
    typedef typename et::MatrixPromote<                             \
        matrix_type, typename XprT::result_type>::type result_type; \
    typedef typename XprT::value_type src_value_type;               \
    typedef et::OpAssign <Element,src_value_type> OpT;              \
    et::UnrollAssignment<OpT>(*this,expr);                          \
}

/** Assign from the same matrix type.
 *
 * @param m the matrix to copy from.
 */
#define CML_MAT_ASSIGN_FROM_MATTYPE                                 \
matrix_type& operator=(const matrix_type& m) {                      \
    typedef et::OpAssign<Element,Element> OpT;                      \
    et::UnrollAssignment<OpT>(*this,m);                             \
    return *this;                                                   \
}

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
operator _op_ (const et::MatrixXpr<XprT>& expr) {                   \
    /* Verify that a promotion exists at compile time: */           \
    typedef typename et::MatrixPromote<                             \
        matrix_type, typename XprT::result_type>::type result_type; \
    typedef typename XprT::value_type src_value_type;               \
    typedef _op_name_ <Element,src_value_type> OpT;                 \
    et::UnrollAssignment<OpT>(*this,expr);                          \
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
matrix_type& operator _op_ (const value_type& s) {                  \
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
