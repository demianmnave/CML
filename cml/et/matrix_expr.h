/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_expr_h
#define matrix_expr_h


#include <cml/core/common.h>
#include <cml/et/matrix_traits.h>
#include <cml/et/matrix_promotions.h>
#include <cml/et/size_checking.h>

namespace cml {

/* Forward declare for the matrix expressions below: */
template<typename E, class AT, typename O> class matrix;

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

    /** Record result size as an enum (if applicable). */
    enum { array_rows = ExprT::array_rows, array_cols = ExprT::array_cols };


  public:

    /** Return number of rows in the expression (same as subexpression). */
    size_t rows() const { return m_expr.rows(); }

    /** Return number of columns in the expression (same as subexpression). */
    size_t cols() const { return m_expr.cols(); }

    /** Return reference to contained expression. */
    expr_reference expression() const { return m_expr; }

    /** Compute value at index i,j of the result matrix. */
    value_type operator()(size_t i, size_t j) const {
        return expr_traits().get(m_expr,i,j);
    }


  public:

    /** Construct from the subexpression to store. */
    explicit MatrixXpr(const ExprT& expr) : m_expr(expr) {}

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
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

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
class UnaryMatrixOp
{
  public:

    typedef UnaryMatrixOp<ArgT,OpT> expr_type;

    /* Record ary-ness of the expression: */
    typedef unary_expression expr_ary;

#if defined(CML_USE_MAT_UNIOP_REF)
    /* Use a reference to the compiler's UnaryMatrixOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the expression by value into higher-up expressions: */
    typedef expr_type expr_const_reference;
#endif // CML_USE_MAT_UNIOP_REF

    typedef typename OpT::value_type value_type;
    typedef matrix_result_tag result_tag;
    typedef typename ArgT::size_tag size_tag;

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

    /** Compute value at index i,j of the result matrix. */
    value_type operator()(size_t i, size_t j) const {

        /* This uses the expression traits to figure out how to access the
         * i,j'th element of the subexpression:
         */
        return OpT().apply(arg_traits().get(m_arg,i,j));
    }


  public:

    /** Construct from the subexpression. */
    explicit UnaryMatrixOp(const ArgT& arg) : m_arg(arg) {}

    /** Copy constructor. */
    UnaryMatrixOp(const expr_type& e) : m_arg(e.m_arg) {}


  protected:

    arg_reference m_arg;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for UnaryMatrixOp<>. */
template<class ArgT, class OpT>
struct ExprTraits< UnaryMatrixOp<ArgT,OpT> >
{
    typedef UnaryMatrixOp<ArgT,OpT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};


/** A binary matrix expression. */
template<class LeftT, class RightT, class OpT>
class BinaryMatrixOp
{
  public:

    typedef BinaryMatrixOp<LeftT,RightT,OpT> expr_type;

#if defined(CML_USE_MAT_BINOP_REF)
    /* Use a reference to the compiler's BinaryMatrixOp temporary in
     * expressions:
     */
    typedef const expr_type& expr_const_reference;
#else
    /* Copy the UnaryMatrixOp expression by value into parent
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
    typedef CheckLinearExprSizes<LeftT,RightT,result_tag> check_size;

    /* Figure out the expression's resulting (matrix) type: */
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename MatrixPromote<left_result,right_result>::type result_type;
    typedef typename result_type::size_tag size_tag;


  public:

    /** Record result size as an enum (if applicable).
     *
     * CheckExprSizes<> ensures that this works as expected.
     */
    enum {
        array_rows = result_type::array_rows,
        array_cols = result_type::array_cols
    };


  public:

    /** Return number of rows in the result. */
    size_t rows() const {

        /* The matrices must have the same dimensions, so just return the
         * number of rows of the left-hand argument:
         */
        return m_left.rows();
    }

    /** Return number of cols in the result. */
    size_t cols() const {

        /* The matrices must have the same dimensions, so just return the
         * number of cols of the left-hand argument:
         */
        return m_left.cols();
    }

    /** Compute value at index i,j of the result matrix. */
    value_type operator()(size_t i, size_t j) const {

        /* This uses the expression traits to figure out how to access the
         * i'th index of the two subexpressions:
         */
        return OpT().apply(
                left_traits().get(m_left,i,j),
                right_traits().get(m_right,i,j));
    }


  public:

    /** Construct from the two subexpressions.
     *
     * @throws std::invalid_argument if the subexpression sizes don't
     * match.
     *
     * @bug The constructor ensures that left and right have the same
     * size through CheckExprSizes.  For dynamically-allocated arrays this
     * could become very costly, since the check happens at each call to the
     * BinaryVectorOp constructor.
     */
    explicit BinaryMatrixOp(const LeftT& left, const RightT& right)
        : m_left(left), m_right(right) { check_size()(left,right); }

    /** Copy constructor. */
    BinaryMatrixOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for BinaryMatrixOp<>. */
template<class LeftT, class RightT, class OpT>
struct ExprTraits< BinaryMatrixOp<LeftT,RightT,OpT> >
{
    typedef BinaryMatrixOp<LeftT,RightT,OpT> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
