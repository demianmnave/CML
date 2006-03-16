/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef external_matrix_h
#define external_matrix_h

#include <cml/core/common.h>
#include <cml/core/external_2D.h>
#include <cml/matrix/matrix_expr.h>
#include <cml/matrix/class_ops.h>
#include <cml/matrix/matrix_unroller.h>
#include <cml/matrix/matrix_transpose.h>
#include <cml/matrix/matrix_ops.h>
#include <cml/matrix/matrix_mul.h>
#include <cml/matvec/matvec_mul.h>

namespace cml {

/** Fixed-size, external-memory vector. */
template<typename Element, int Rows, int Cols, typename Layout>
class matrix<Element,external<Rows,Cols>,Layout>
: public external_2D<Element,Rows,Cols,Layout>
{
  public:

    /* Shorthand for the generator: */
    typedef external<Rows,Cols> generator_type;

    /* Shorthand for the array type: */
    typedef external_2D<Element,Rows,Cols,Layout> array_type;

    /* Shorthand for the type of this matrix: */
    typedef matrix<Element,generator_type,Layout> matrix_type;

    /* For integration into the expression template code: */
    typedef matrix_type expr_type;

    /* For integration into the expression template code: */
    typedef matrix<Element,fixed<Rows,Cols>,Layout> temporary_type;
    /* Note: this ensures that an external matrix is copied into the proper
     * temporary; external<> temporaries are not allowed.
     */

    /* Standard: */
    typedef typename array_type::value_type value_type;
    typedef typename array_type::reference reference;
    typedef typename array_type::const_reference const_reference;

    typedef matrix_type& expr_reference;
    typedef const matrix_type& expr_const_reference;

    /* For matching by memory layout: */
    typedef typename array_type::layout layout;

    /* For matching by storage type if necessary: */
    typedef typename array_type::memory_tag memory_tag;

    /* For matching by size type if necessary: */
    typedef typename array_type::size_tag size_tag;

    /* For matching by result-type: */
    typedef cml::et::matrix_result_tag result_tag;

    /* To simplify the matrix transpose operator: */
    typedef matrix<
        Element, typename array_type::transposed_type::generator_type, Layout
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
