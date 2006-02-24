/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 *  The configurable matrix<> class.
 */

#ifndef matrix_h
#define matrix_h

#include <cstddef>              // for size_t
#include <cml/core/common.h>
#include <cml/et/matrix_unroller.h>
#include <cml/matrix_ops.h>

namespace cml {

/** A configurable matrix.
 *
 * This class encapsulates the notion of a matrix.  The ArrayType template
 * argument can be used to select the type of array to be used as internal
 * storage for a 2D arrayy of type Element.  The ArrayType is expected to
 * implement operator()(size_t) (linear) and operator()(size_t,size_t)
 * (matrix) to access Element's of the matrix.
 *
 * @warning Matrices with different ArrayType's may not yet work as
 * expected in expressions, particularly those using dynamically-allocated
 * memory.
 *
 * @sa cml::fixed
 * @sa cml::dynamic
 */
template<typename Element, class ArrayType>
class matrix

/* Figure out (and inherit from) the selected base array type: */
: public ArrayType::template rebind<twod_tag,Element>::other
{
  public:

    /* Shorthand for the base array type: */
    typedef typename ArrayType::template rebind<twod_tag,Element>::other
        array_type;

    /* Shorthand for the type of this matrix: */
    typedef matrix<Element,ArrayType> matrix_type;

    /* For integration into the expression template code: */
    typedef matrix_type expr_type;

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
    typedef matrix<Element, typename ArrayType::transposed_type>
        transposed_type;


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

    /** Constructor for external arrays.
     *
     * @param rows specify the number of rows.
     * @param cols specify the number of cols.
     * @param ptr specify the external pointer.
     *
     * @throws same as the ArrayType constructor.
     * @sa cml::fixed
     * @sa cml::dynamic
     */
    explicit matrix(size_t rows, size_t cols, value_type* ptr)
        : array_type(rows,cols,ptr) {}


  public:

    /** Construct from another matrix.
     *
     * @param m the matrix to copy from.
     */
    template<typename E, class AT> matrix(const matrix<E,AT>& m) {
        typedef et::OpAssign<Element,E> OpT;
        this->reshape(m);
        et::UnrollAssignment<OpT>(*this,m);
    }

    /** Construct from a matrix expression.
     *
     * @param expr the expression to copy from.
     *
     * @internal This must be explicit to prevent conversions for arbitrary
     * XprT's.
     */
    template<class XprT> matrix(const et::MatrixXpr<XprT>& expr) {
        /* Verify that a promotion exists at compile time: */
        typedef typename et::MatrixPromote<
            matrix_type, typename XprT::result_type>::type result_type;
        typedef typename XprT::value_type src_value_type;
        typedef et::OpAssign<Element,src_value_type> OpT;
        et::UnrollAssignment<OpT>(*this,expr);
    }


  public:

    /** Reshape the matrix to match the argument.
     *
     * This only works for dynamic matrices; it's a no-op for fixed
     * matrices.
     *
     * @param m the matrix to copy from.
     */
    template<typename E, class AT>
    void reshape(const matrix<E,AT>& m) {

        /* Dispatch to the proper reshape function: */
        this->reshape(m,size_tag());
    }


  public:

    /** Assign this matrix from another using the given elementwise op.
     *
     * This allows assignment from arbitrary matrix types.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     */
#define CML_ASSIGN_FROM_MAT(_op_, _op_name_)                            \
    template<typename E, class AT> matrix_type&                         \
    operator _op_ (const matrix<E,AT>& m) {                             \
        typedef _op_name_ <Element,E> OpT;                              \
        this->reshape(m);                                               \
        et::UnrollAssignment<OpT>(*this,m);                             \
        return *this;                                                   \
    }

    CML_ASSIGN_FROM_MAT(=, et::OpAssign)
    CML_ASSIGN_FROM_MAT(+=, et::OpAddAssign)
    CML_ASSIGN_FROM_MAT(-=, et::OpSubAssign)
#undef CML_ASSIGN_FROM_MAT


    /** Declare a function to assign this matrix from a matrix expression.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     */
#define CML_ASSIGN_FROM_MATXPR(_op_, _op_name_)                         \
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

    CML_ASSIGN_FROM_MATXPR(=, et::OpAssign)
    CML_ASSIGN_FROM_MATXPR(+=, et::OpAddAssign)
    CML_ASSIGN_FROM_MATXPR(-=, et::OpSubAssign)

#undef CML_ASSIGN_FROM_MATXPR


    /** Declare a function to assign this matrix from a scalar.
     *
     * @param _op_ the operator (e.g. +=)
     * @param _op_name_ the op functor (e.g. et::OpAssign)
     *
     * @internal This shouldn't be used for ops, like +=, which aren't
     * defined in vector algebra.
     */
#define CML_ASSIGN_FROM_SCALAR(_op_, _op_name_)                         \
    matrix_type& operator _op_ (const value_type& s) {                  \
        typedef _op_name_ <Element,value_type> OpT;                     \
        et::UnrollAssignment<OpT>(*this,s);                             \
        return *this;                                                   \
    }

    CML_ASSIGN_FROM_SCALAR(*=, et::OpMulAssign)
    CML_ASSIGN_FROM_SCALAR(/=, et::OpDivAssign)

#undef CML_ASSIGN_FROM_SCALAR


  protected:

    /** Reshape for fixed-size matrices. */
    template<typename E, class AT>
        void reshape(const matrix<E,AT>&, fixed_size_tag) {
            /* Do nothing. */
        }

    /** Reshape for dynamically-sized matrices. */
    template<typename E, class AT>
        void reshape(const matrix<E,AT>& m, dynamic_size_tag) {
            this->resize(m.rows(),m.cols());
        }


#if defined(CML_ENABLE_MATRIX_BRACES)
  public:

    /* These should probably only be used for testing: */

    /* Helper to use operator[] to access rows of the matrix: */
    template<class Matrix> struct row_ref {
        typedef typename Matrix::reference reference;
        reference operator[](size_t col) { return m(row,col); }
        Matrix& m;
        size_t row;
    };

    /* Helper to use operator[] to access const rows of the matrix: */
    template<class Matrix> struct const_row_ref {
        typedef typename Matrix::const_reference const_reference;
        const_reference operator[](size_t col) const { return m(row,col); }
        const Matrix& m;
        size_t row;
    };

    row_ref<matrix_type> operator[](size_t row) {
        row_ref<matrix_type> ref = { *this, row }; return ref;
    }

    const_row_ref<matrix_type> operator[](size_t row) const {
        const_row_ref<matrix_type> ref = { *this, row }; return ref;
    }
#endif
};

} // namespace cml

/* Clean up: */
#undef ORIENT_MACRO
#undef COPY_TEMPLATE_PARAMS

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
