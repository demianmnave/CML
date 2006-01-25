/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#if !defined(cml_matrix_h)
#error "This should only be included from cml/matrix.h"
#else

#ifndef matrix_expr_h
#define matrix_expr_h

#include <cml/et/matrix_traits.h>
#include <cml/et/size_checking.h>

namespace cml {

/* Forward declare for the matrix expressions below: */
template<typename Element, class ArrayType, typename Orient> class matrix;

namespace et {

/** A placeholder for a matrix expression in the expression tree. */
template<class ExprT>
class MatrixXpr
{
  public:

    typedef MatrixXpr<ExprT> expr_type;

#if defined(CML_USE_MAT_XPR_REF)
    /* Use a reference to the compiler's MatrixXpr<> temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_MAT_XPR_REF

    typedef typename ExprT::value_type value_type;
    typedef matrix_result_tag result_tag;
    typedef typename ExprT::size_tag size_tag;  // Just inherit size type.

    /* Store the expression traits: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Get the reference type: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Get the result type: */
    typedef typename expr_traits::result_type result_type;


  public:

    /** Return number of rows in the expression (same as subexpression). */
    size_t rows() const { return m_expr.rows(); }

    /** Return number of columns in the expression (same as subexpression). */
    size_t cols() const { return m_expr.cols(); }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i of the result vector. */
    value_type operator()(size_t i) const {
        return expr_traits().get(m_expr,i);
    }

    /** Compute value at index i,j of the result vector. */
    value_type operator()(size_t i, size_t j) const {
        return expr_traits().get(m_expr,i,j);
    }


  public:

    /** Record result size as an enum (if applicable). */
    enum { array_rows = ExprT::array_rows, array_cols = ExprT::array_cols };


  public:

    /** Construct from the subexpression to store. */
    MatrixXpr(const ExprT& expr) : m_expr(expr) {}

    /** Copy constructor. */
    MatrixXpr(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for MatrixXpr<>. */
template<class ExprT>
struct ExprTraits< MatrixXpr<ExprT> >
{
    typedef MatrixXpr<ExprT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::result_type result_type;

    /** This is used primarily for linear unrolling. */
    value_type get(const expr_type& e, size_t i) const { return e(i); }

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};


/** A unary matrix expression operating on matrix elements as a list.
 *
 * The operator must take exactly one argument.
 */
template<class ArgT, class OpT>
class LinearUnaryMatrixOp
{
  public:

    typedef LinearUnaryMatrixOp<ArgT,OpT> expr_type;

#if defined(CML_USE_MAT_UNIOP_REF)
    /* Use a reference to the compiler's LinearUnaryMatrixOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_MAT_UNIOP_REF

    typedef typename OpT::value_type value_type;
    typedef matrix_result_tag result_tag;
    typedef typename ArgT::size_tag size_tag;  // Just inherit size type.

    /* Store the expression traits for the subexpression: */
    typedef ExprTraits<ArgT> arg_traits;

    /* Reference type for the subexpression: */
    typedef typename arg_traits::const_reference arg_reference;

    /* Get the result type: */
    typedef typename arg_traits::result_type result_type;


  public:

    /** Return number of rows in the expression (same as argument). */
    size_t rows() const { return m_arg.rows(); }

    /** Return number of columns in the expression (same as argument). */
    size_t cols() const { return m_arg.cols(); }

    /** Compute value at index i of the result vector. */
    value_type operator()(size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i,j'th element of the subexpression:
         */
        return OpT().apply(arg_traits().get(m_arg,i));
    }

    /** Compute value at index i,j of the result vector. */
    value_type operator()(size_t i, size_t j) const {

        /* This uses the expression traits to figure out how to access the
         * i,j'th element of the subexpression:
         */
        return OpT().apply(arg_traits().get(m_arg,i,j));
    }


  public:

    /** Construct from the subexpression. */
    LinearUnaryMatrixOp(const ArgT& arg)
        : m_arg(arg) {}

    /** Copy constructor. */
    LinearUnaryMatrixOp(const expr_type& e)
        : m_arg(e.m_arg) {}


  protected:

    arg_reference m_arg;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for LinearUnaryMatrixOp<>. */
template<class ArgT, class OpT>
struct ExprTraits< LinearUnaryMatrixOp<ArgT,OpT> >
{
    typedef LinearUnaryMatrixOp<ArgT,OpT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::result_type result_type;

    /** This is used primarily for linear unrolling. */
    value_type get(const expr_type& e, size_t i) const { return e(i); }

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};


/** A binary matrix expression. */
template<class LeftT, class RightT, class OpT>
class LinearBinaryMatrixOp
{
  public:

    typedef LinearBinaryMatrixOp<LeftT,RightT,OpT> expr_type;

#if defined(CML_USE_MAT_BINOP_REF)
    /* Use a reference to the compiler's LinearBinaryMatrixOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the LinearUnaryMatrixOp expression by value into parent
     * expression tree nodes:
     */
    typedef expr_type expr_const_reference;
#endif // CML_USE_MAT_BINOP_REF

    typedef typename OpT::value_type value_type;
    typedef matrix_result_tag result_tag;

    /* Record the expression traits for the two subexpressions: */
    typedef ExprTraits<LeftT> left_traits;
    typedef ExprTraits<RightT> right_traits;

    /* Reference types for the two subexpressions: */
    typedef typename left_traits::const_reference left_reference;
    typedef typename right_traits::const_reference right_reference;

    /* A checker to verify the argument sizes at compile- or run-time: */
    typedef CheckLinearMatrixSizes<expr_type> check_size;

    /* Figure out the result size and type based on the subexpressions: */
    typedef DeduceMatrixResultSize<expr_type> deduce_size;
    typedef typename deduce_size::tag size_tag;

#if 0
    /* Get the result type: */
    typedef typename expr_traits::result_type result_type;
#endif


  public:

    /** Record result size as an enum (if applicable).
     *
     * MatrixSizeChecker<> ensures that this works as expected.
     */
    enum {
        array_rows = deduce::result_rows,
        array_cols = deduce::result_cols
    };


  public:

    /** Return number of rows in the result. */
    size_t rows() const {
        return left_traits().rows(m_left);
    }

    /** Return number of cols in the result. */
    size_t cols() const {
        return right_traits().cols(m_right);
    }

    /** Compute value at index i of the result vector. */
    value_type operator()(size_t i) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the two subexpressions:
         */
        return OpT().apply(
                left_traits().get(m_left,i),
                right_traits().get(m_right,i));
    }

    /** Compute value at index i,j of the result vector. */
    value_type operator()(size_t i, size_t j) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the two subexpressions:
         */
        return OpT().apply(
                left_traits().get(m_left,i,j),
                right_traits().get(m_right,i,j));
    }


  public:

    /** Construct from the two subexpressions. */
    LinearBinaryMatrixOp(const LeftT& left, const RightT& right)
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    LinearBinaryMatrixOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for LinearBinaryMatrixOp<>. */
template<class LeftT, class RightT, class OpT>
struct ExprTraits< LinearBinaryMatrixOp<LeftT,RightT,OpT> >
{
    typedef LinearBinaryMatrixOp<LeftT,RightT,OpT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::result_type result_type;

    /** This is used primarily for linear unrolling. */
    value_type get(const expr_type& e, size_t i) const { return e(i); }

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};


} // namespace et
} // namespace cml

#endif
#endif // !defined(cml_vector_h)

// -------------------------------------------------------------------------
// vim:ft=cpp
