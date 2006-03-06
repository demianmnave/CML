/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_expr_h
#define matrix_expr_h


#include <cml/core/common.h>
#include <cml/et/size_checking.h>
#include <cml/matrix/matrix_traits.h>
#include <cml/matrix/matrix_promotions.h>

namespace cml {
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

    /** Return the expression size as a pair. */
    matrix_size size() const {
        return matrix_size(this->rows(),this->cols());
    }

    /** Return number of rows in the expression (same as subexpression). */
    size_t rows() const { 
        return expr_traits().rows(m_expr);
    }

    /** Return number of columns in the expression (same as subexpression). */
    size_t cols() const {
        return expr_traits().cols(m_expr);
    }

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
    typedef ExprT arg_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }


    matrix_size size(const expr_type& e) const { return e.size(); }
    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};


/** A unary matrix expression operating on matrix elements as a list.
 *
 * The operator must take exactly one argument.
 */
template<class ExprT, class OpT>
class UnaryMatrixOp
{
  public:

    typedef UnaryMatrixOp<ExprT,OpT> expr_type;

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
    typedef typename ExprT::size_tag size_tag;

    /* Store the expression traits for the subexpression: */
    typedef ExprTraits<ExprT> expr_traits;

    /* Reference type for the subexpression: */
    typedef typename expr_traits::const_reference expr_reference;

    /* Get the result type: */
    typedef typename expr_traits::result_type result_type;


  public:

    /** Return the expression size as a pair. */
    matrix_size size() const {
        return matrix_size(this->rows(),this->cols());
    }

    /** Return number of rows in the expression (same as argument). */
    size_t rows() const {
        return expr_traits().rows(m_expr);
    }

    /** Return number of columns in the expression (same as argument). */
    size_t cols() const {
        return expr_traits().cols(m_expr);
    }

    /** Compute value at index i,j of the result matrix. */
    value_type operator()(size_t i, size_t j) const {

        /* This uses the expression traits to figure out how to access the
         * i,j'th element of the subexpression:
         */
        return OpT().apply(expr_traits().get(m_expr,i,j));
    }


  public:

    /** Construct from the subexpression. */
    explicit UnaryMatrixOp(const ExprT& expr) : m_expr(expr) {}

    /** Copy constructor. */
    UnaryMatrixOp(const expr_type& e) : m_expr(e.m_expr) {}


  protected:

    expr_reference m_expr;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for UnaryMatrixOp<>. */
template<class ExprT, class OpT>
struct ExprTraits< UnaryMatrixOp<ExprT,OpT> >
{
    typedef UnaryMatrixOp<ExprT,OpT> expr_type;
    typedef ExprT arg_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    matrix_size size(const expr_type& e) const { return e.size(); }
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

    /* Figure out the expression's resulting (matrix) type: */
    typedef typename left_traits::result_type left_result;
    typedef typename right_traits::result_type right_result;
    typedef typename MatrixPromote<left_result,right_result>::type result_type;
    typedef typename result_type::size_tag size_tag;

    /* Define a size checker: */
    typedef GetCheckedSize<LeftT,RightT,size_tag> checked_size;


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

    /** Return the expression size as a pair. */
    matrix_size size() const {
#if defined(CML_CHECK_MATRIX_EXPR_SIZES)
        return CheckedSize(m_left,m_right,size_tag());
#else
        return left_traits().size(m_left);
#endif
    }

    /** Return number of rows in the result.
     *
     * @note Because this calls size() internally, calling both rows()
     * and cols() with CML_CHECK_MATRIX_EXPR_SIZES defined will cause the size
     * checking code to be executed twice.
     */
    size_t rows() const {
        return this->size().first;
    }

    /** Return number of cols in the result.
     *
     * @note Because this calls size() internally, calling both rows()
     * and cols() with CML_CHECK_MATRIX_EXPR_SIZES defined will cause the size
     * checking code to be executed twice.
     */
    size_t cols() const {
        return this->size().second;
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
        : m_left(left), m_right(right) {}

    /** Copy constructor. */
    BinaryMatrixOp(const expr_type& e)
        : m_left(e.m_left), m_right(e.m_right) {}


  protected:

    left_reference m_left;
    right_reference m_right;


  private:

    /* This ensures that a compile-time size check is executed: */
    typename checked_size::check_type _dummy;


  private:

    /* Cannot be assigned to: */
    expr_type& operator=(const expr_type&);
};

/** Expression traits for BinaryMatrixOp<>. */
template<class LeftT, class RightT, class OpT>
struct ExprTraits< BinaryMatrixOp<LeftT,RightT,OpT> >
{
    typedef BinaryMatrixOp<LeftT,RightT,OpT> expr_type;
    typedef LeftT left_type;
    typedef RightT right_type;

    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef typename expr_type::result_type result_type;
    typedef expr_node_tag node_tag;

    value_type get(const expr_type& e, size_t i, size_t j) const {
        return e(i,j);
    }

    matrix_size size(const expr_type& e) const { return e.size(); }
    size_t rows(const expr_type& e) const { return e.rows(); }
    size_t cols(const expr_type& e) const { return e.cols(); }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
