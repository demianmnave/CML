/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef dynamic_matrix_h
#define dynamic_matrix_h

#include <cml/core/common.h>
#include <cml/matrix/matrix_unroller.h>
#include <cml/matrix/class_ops.h>
#include <cml/dynamic.h>

namespace cml {

/** Resizeable, dynamic-memory matrix. */
template<typename Element, typename Alloc, typename Layout>
class matrix<Element,dynamic<Alloc>,Layout>
: public dynamic_2D<Element,Layout,Alloc>
{
  public:

    /* Shorthand for the generator: */
    typedef dynamic<Alloc> generator_type;

    /* Shorthand for the array type: */
    typedef dynamic_2D<Element,Layout,Alloc> array_type;

    /* Shorthand for the type of this matrix: */
    typedef matrix<Element,generator_type,Layout> matrix_type;

    /* For integration into the expression template code: */
    typedef matrix_type expr_type;

    /* For integration into the expression template code: */
    typedef matrix_type temporary_type;

    /* Standard: */
    typedef typename array_type::value_type value_type;
    typedef typename array_type::reference reference;
    typedef typename array_type::const_reference const_reference;

    /* For integration into the expression templates code: */
    typedef matrix_type& expr_reference;
    typedef const matrix_type& expr_const_reference;

    /* For matching by memory layout: */
    typedef typename array_type::layout layout;

    /* For matching by storage type: */
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
        typename array_type::row_array_type::generator_type,
        row_vector
    > row_vector_type;

    typedef vector<
        Element,
        typename array_type::col_array_type::generator_type,
        col_vector
    > col_vector_type;


  public:

    /** Default constructor.
     *
     * @throws same as the ArrayType constructor.
     * @sa cml::fixed
     * @sa cml::dynamic
     */
    matrix() {}

    /** Constructor for dynamically-sized arrays.
     *
     * @param rows specify the number of rows.
     * @param cols specify the number of cols.
     *
     * @throws same as the ArrayType constructor.
     * @sa cml::fixed
     * @sa cml::dynamic
     */
    explicit matrix(size_t rows, size_t cols)
        : array_type(rows,cols) {}


  public:

    /** Return the matrix size as a pair. */
    matrix_size size() const {
        return matrix_size(this->rows(),this->cols());
    }


  public:

    /* Define common class operators: */
    CML_MAT_COPY_FROM_MATTYPE
    CML_MAT_COPY_FROM_MAT
    CML_MAT_COPY_FROM_MATXPR

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
