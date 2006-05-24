/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef external_matrix_h
#define external_matrix_h

#include <cml/core/external_2D.h>
#include <cml/matrix/matrix_expr.h>
#include <cml/matrix/class_ops.h>
#include <cml/matrix/matrix_unroller.h>

namespace cml {

/** Fixed-size, external-memory matrix. */
template<typename Element, int Rows, int Cols,
    typename BasisOrient, typename Layout>
class matrix<Element,external<Rows,Cols>,BasisOrient,Layout>
: public external_2D<Element,Rows,Cols,Layout>
{
  public:

    /* Shorthand for the generator: */
    typedef external<Rows,Cols> generator_type;

    /* Shorthand for the array type: */
    typedef external_2D<Element,Rows,Cols,Layout> array_type;

    /* Shorthand for the type of this matrix: */
    typedef matrix<Element,generator_type,BasisOrient,Layout> matrix_type;

    /* For integration into the expression template code: */
    typedef matrix_type expr_type;

    /* For integration into the expression template code: */
    typedef matrix<Element,fixed<Rows,Cols>,BasisOrient,Layout> temporary_type;
    /* Note: this ensures that an external matrix is copied into the proper
     * temporary; external<> temporaries are not allowed.
     */

    /* Standard: */
    typedef typename array_type::value_type value_type;
    typedef typename array_type::reference reference;
    typedef typename array_type::const_reference const_reference;

    typedef matrix_type& expr_reference;
    typedef const matrix_type& expr_const_reference;

    /* For matching by basis: */
    typedef BasisOrient basis_orient;

    /* For matching by memory layout: */
    typedef typename array_type::layout layout;

    /* For matching by storage type if necessary: */
    typedef typename array_type::memory_tag memory_tag;

    /* For matching by size type if necessary: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::matrix_result_tag result_tag;

    /* For matching by assignability: */
    typedef cml::et::assignable_tag assignable_tag;

    /* To simplify the matrix transpose operator: */
    typedef matrix<
        Element,
        typename array_type::transposed_type::generator_type,
        BasisOrient,
        Layout
    > transposed_type;

    /* To simplify the matrix row and column operators: */
    typedef vector<
        Element,
        typename array_type::row_array_type::generator_type
    > row_vector_type;

    typedef vector<
        Element,
        typename array_type::col_array_type::generator_type
    > col_vector_type;


  public:

    /** Set this matrix to zero. */
    matrix_type& zero() {
        typedef cml::et::OpAssign<Element,Element> OpT;
        cml::et::UnrollAssignment<OpT>(*this,Element(0));
        return *this;
    }

    /** Set this matrix to the identity.
     *
     * This only makes sense for a square matrix, but no error will be
     * signaled if the matrix is not square.
     */
    matrix_type& identity() {
        for(size_t i = 0; i < this->rows(); ++ i) {
            for(size_t j = 0; j < this->cols(); ++ j) {
                (*this)(i,j) = value_type((i == j)?1:0);
            }
        }
        return *this;
    }

    /** Set this matrix to its transpose.
     *
     * This only makes sense for a square matrix, but no error will be
     * signaled if the matrix is not square.
     */
    matrix_type& transpose() {
        /* transpose() returns a temporary: */
        *this = transpose(*this);
        return *this;
    }

    /** Set this matrix to its inverse.
     *
     * This only makes sense for a square matrix, but no error will be
     * signaled if the matrix is not square.
     */
    matrix_type& inverse() {
        /* inverse() returns a temporary: */
        *this = inverse(*this);
        return *this;
    }


  public:

    /** Constructor for fixed-size external matrices.
     *
     * The array must be given as a pointer to Element*, not a
     * multi-dimensional array.  The caller owns the pointer, and is
     * responsible for doing any necessary memory management.
     *
     * @param ptr specify the external pointer.
     *
     * @throws same as the ArrayType constructor.
     */
    explicit matrix(value_type* ptr) : array_type(ptr) {}


  public:

    /** Return the matrix size as a pair. */
    matrix_size size() const {
        return matrix_size(this->rows(),this->cols());
    }

    /** Return element j of basis vector i. */
    value_type basis_element(size_t i, size_t j) const {
        return basis_element(i,j,basis_orient());
    }

    /** Set the given basis element. */
    void set_basis_element(size_t i, size_t j, ELEMENT_ARG_TYPE s) {
        set_basis_element(i,j,s,basis_orient());
    }


  public:

    /* Define class operators for external matrices. Note: external matrices
     * cannot be copy-constructed, but they can be assigned to:
     */
    CML_MAT_ASSIGN_FROM_MATTYPE

    CML_MAT_ASSIGN_FROM_MAT(=, et::OpAssign)
    CML_MAT_ASSIGN_FROM_MAT(+=, et::OpAddAssign)
    CML_MAT_ASSIGN_FROM_MAT(-=, et::OpSubAssign)

    CML_MAT_ASSIGN_FROM_MATXPR(=, et::OpAssign)
    CML_MAT_ASSIGN_FROM_MATXPR(+=, et::OpAddAssign)
    CML_MAT_ASSIGN_FROM_MATXPR(-=, et::OpSubAssign)

    CML_MAT_ASSIGN_FROM_SCALAR(*=, et::OpMulAssign)
    CML_MAT_ASSIGN_FROM_SCALAR(/=, et::OpDivAssign)

    /** Accumulated matrix multiplication.
     *
     * This only makes sense for a square matrix, but no error will be
     * signaled if the matrix is not square.
     */
    matrix_type& operator*=(const matrix_type& m) {
        /* Matrix multiplication returns a temporary: */
        *this = (*this)*m;
        return *this;
    }

    /** Accumulated matrix multiplication.
     *
     * This only makes sense for a square matrix, but no error will be
     * signaled if the matrix is not square.
     */
    template<typename E, class AT, typename BO, typename L> matrix_type&
    operator*=(const matrix<E,AT,BO,L>& m) {
        /* Matrix multiplication returns a temporary: */
        *this = (*this)*m;
        return *this;
    }

    /** Accumulated matrix multiplication.
     *
     * This only makes sense for a square matrix, but no error will be
     * signaled if the matrix is not square.
     */
    template<class XprT> matrix_type&
    operator*=(MATXPR_ARG_TYPE e) {
        /* Verify that a promotion exists at compile time: */
        typedef typename et::MatrixPromote<
            matrix_type, typename XprT::result_type>::type result_type;
        /* Matrix multiplication returns a temporary: */
        *this = (*this)*e;
        return *this;
    }


  protected:

    value_type basis_element(size_t i, size_t j, row_basis) const {
        return (*this)(i,j);
    }

    value_type basis_element(size_t i, size_t j, col_basis) const {
        return (*this)(j,i);
    }

    void set_basis_element(size_t i, size_t j, ELEMENT_ARG_TYPE s, row_basis) {
        (*this)(i,j) = s;
    }

    void set_basis_element(size_t i, size_t j, ELEMENT_ARG_TYPE s, col_basis) {
        (*this)(j,i) = s;
    }


  public:

    /* Braces should only be used for testing: */
#if defined(CML_ENABLE_MATRIX_BRACES)
    CML_MATRIX_BRACE_OPERATORS
#endif
};

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
