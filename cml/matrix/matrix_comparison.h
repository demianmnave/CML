/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_comparison_h
#define matrix_comparison_h

#include <cml/core/cml_assert.h>
#include <cml/et/size_checking.h>
#include <cml/et/scalar_ops.h>

/* This is used below to create a more meaningful compile-time error when
 * matrix_comparison is not provided with matrix or MatrixExpr arguments:
 */
struct matrix_comparison_expects_matrix_args_error;

#define CML_MAT_MAT_COMPARE(_op_, _OpT_)                                \
template<typename E1, class AT1, typename L1,                           \
         typename E2, class AT2, typename L2, typename BO>              \
inline bool                                                             \
_op_ (                                                                  \
        const matrix<E1,AT1,L1,BO>& left,                               \
        const matrix<E2,AT2,L2,BO>& right)                              \
{                                                                       \
    return detail::matrix_comparison(left, right, _OpT_ <E1,E2>());     \
}

#define CML_MAT_MATXPR_COMPARE(_op_, _OpT_)                             \
template<typename E, class AT, typename L, typename BO, class XprT>     \
inline bool                                                             \
_op_ (                                                                  \
        const matrix<E,AT,L,BO>& left,                                  \
        MATXPR_ARG_TYPE right)                                          \
{                                                                       \
    return detail::matrix_comparison(left, right,                       \
            _OpT_ <E, typename XprT::value_type>());                    \
}

#define CML_MATXPR_MAT_COMPARE(_op_, _OpT_)                             \
template<class XprT, typename E, class AT, typename L, typename BO>     \
inline bool                                                             \
_op_ (                                                                  \
        MATXPR_ARG_TYPE left,                                           \
        const matrix<E,AT,L,BO>& right)                                 \
{                                                                       \
    return detail::matrix_comparison(left, right,                       \
            _OpT_ <typename XprT::value_type, E>());                    \
}

#define CML_MATXPR_MATXPR_COMPARE(_op_, _OpT_)                          \
template<class XprT1, class XprT2>                                      \
inline bool                                                             \
_op_ (                                                                  \
        MATXPR_ARG_TYPE_N(1) left,                                      \
        MATXPR_ARG_TYPE_N(2) right)                                     \
{                                                                       \
    return detail::matrix_comparison(left, right,                       \
            _OpT_ <                                                     \
                typename XprT1::value_type,                             \
                typename XprT2::value_type>());                         \
}


namespace cml {
namespace detail {

/** Matrix element-wise comparison implementation. */
template<typename LeftT, typename RightT, typename OpT>
inline bool
matrix_comparison(const LeftT& left, const RightT& right, OpT)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* matrix_comparison() requires matrix expressions: */
    CML_STATIC_REQUIRE_M(
            (et::MatrixExpressions<LeftT,RightT>::is_true),
            matrix_comparison_expects_matrix_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    typedef typename et::MatrixPromote<
        typename left_traits::result_type,
        typename right_traits::result_type
    >::type result_type;
    typedef typename result_type::size_tag size_tag;

    /* Verify expression size: */
    matrix_size N = et::CheckedSize(left,right,size_tag());

    /* Apply op to each element, and return false on false comparison: */
    for(ssize_t i = 0; i < N.first; ++ i) {
        for(ssize_t j = 0; j < N.second; ++ j) {
            if(!OpT().apply(
                        left_traits().get(left,i,j),
                        right_traits().get(right,i,j)))
                return false;
        }
    }
    /* XXX Can this be unrolled in any reasonable way? */

    return true;
}

}

CML_MAT_MAT_COMPARE(       operator==, et::OpEquals)
CML_MATXPR_MAT_COMPARE(    operator==, et::OpEquals)
CML_MAT_MATXPR_COMPARE(    operator==, et::OpEquals)
CML_MATXPR_MATXPR_COMPARE( operator==, et::OpEquals)

CML_MAT_MAT_COMPARE(        operator<, et::OpLess)
CML_MATXPR_MAT_COMPARE(     operator<, et::OpLess)
CML_MAT_MATXPR_COMPARE(     operator<, et::OpLess)
CML_MATXPR_MATXPR_COMPARE(  operator<, et::OpLess)

CML_MAT_MAT_COMPARE(        operator>, et::OpGreater)
CML_MATXPR_MAT_COMPARE(     operator>, et::OpGreater)
CML_MAT_MATXPR_COMPARE(     operator>, et::OpGreater)
CML_MATXPR_MATXPR_COMPARE(  operator>, et::OpGreater)

CML_MAT_MAT_COMPARE(        operator<=, et::OpLessEqual)
CML_MATXPR_MAT_COMPARE(     operator<=, et::OpLessEqual)
CML_MAT_MATXPR_COMPARE(     operator<=, et::OpLessEqual)
CML_MATXPR_MATXPR_COMPARE(  operator<=, et::OpLessEqual)

CML_MAT_MAT_COMPARE(        operator>=, et::OpGreaterEqual)
CML_MATXPR_MAT_COMPARE(     operator>=, et::OpGreaterEqual)
CML_MAT_MATXPR_COMPARE(     operator>=, et::OpGreaterEqual)
CML_MATXPR_MATXPR_COMPARE(  operator>=, et::OpGreaterEqual)

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
