/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef vector_comparison_h
#define vector_comparison_h

#include <cml/core/cml_assert.h>
#include <cml/et/size_checking.h>
#include <cml/et/scalar_ops.h>

/* This is used below to create a more meaningful compile-time error when
 * vector_comparison is not provided with vector or VectorExpr arguments:
 */
struct vector_comparison_expects_vector_args_error;

#define CML_VEC_VEC_COMPARE(_op_, _OpT_)                                \
template<typename E1, class AT1, typename E2, class AT2>                \
inline bool                                                             \
_op_ (                                                                  \
        const vector<E1,AT1>& left,                                     \
        const vector<E2,AT2>& right)                                    \
{                                                                       \
    return detail::vector_comparison(left, right, _OpT_ <E1,E2>());     \
}

#define CML_VEC_VECXPR_COMPARE(_op_, _OpT_)                             \
template<typename E, class AT, class XprT>                              \
inline bool                                                             \
_op_ (                                                                  \
        const vector<E,AT>& left,                                       \
        VECXPR_ARG_TYPE right)                                          \
{                                                                       \
    return detail::vector_comparison(left, right,                       \
            _OpT_ <E, typename XprT::value_type>());                    \
}

#define CML_VECXPR_VEC_COMPARE(_op_, _OpT_)                             \
template<class XprT, typename E, class AT>                              \
inline bool                                                             \
_op_ (                                                                  \
        VECXPR_ARG_TYPE left,                                           \
        const vector<E,AT>& right)                                      \
{                                                                       \
    return detail::vector_comparison(left, right,                       \
            _OpT_ <typename XprT::value_type, E>());                    \
}

#define CML_VECXPR_VECXPR_COMPARE(_op_, _OpT_)                          \
template<class XprT1, class XprT2>                                      \
inline bool                                                             \
_op_ (                                                                  \
        VECXPR_ARG_TYPE_N(1) left,                                      \
        VECXPR_ARG_TYPE_N(2) right)                                     \
{                                                                       \
    return detail::vector_comparison(left, right,                       \
            _OpT_ <                                                     \
                typename XprT1::value_type,                             \
                typename XprT2::value_type>());                         \
}


namespace cml {
namespace detail {

/** Vector element-wise comparison implementation. */
template<typename LeftT, typename RightT, typename OpT>
inline bool
vector_comparison(const LeftT& left, const RightT& right, OpT)
{
    /* Shorthand: */
    typedef et::ExprTraits<LeftT> left_traits;
    typedef et::ExprTraits<RightT> right_traits;

    /* vector_comparison() requires vector expressions: */
    CML_STATIC_REQUIRE_M(
            (et::VectorExpressions<LeftT,RightT>::is_true),
            vector_comparison_expects_vector_args_error);
    /* Note: parens are required here so that the preprocessor ignores the
     * commas:
     */

    typedef typename et::VectorPromote<
        typename left_traits::result_type,
        typename right_traits::result_type
    >::type result_type;
    typedef typename result_type::size_tag size_tag;

    /* Verify expression size: */
    ssize_t N = (ssize_t) et::CheckedSize(left,right,size_tag());

    /* Apply op to each element, and return false on false comparison: */
    for(ssize_t i = 0; i < N; ++ i) {
        if(!OpT().apply(
                    left_traits().get(left,i),
                    right_traits().get(right,i)))
            return false;
    }
    /* XXX Can this be unrolled in any reasonable way? */

    return true;
}

}

CML_VEC_VEC_COMPARE(       operator==, et::OpEquals)
CML_VECXPR_VEC_COMPARE(    operator==, et::OpEquals)
CML_VEC_VECXPR_COMPARE(    operator==, et::OpEquals)
CML_VECXPR_VECXPR_COMPARE( operator==, et::OpEquals)

CML_VEC_VEC_COMPARE(        operator<, et::OpLess)
CML_VECXPR_VEC_COMPARE(     operator<, et::OpLess)
CML_VEC_VECXPR_COMPARE(     operator<, et::OpLess)
CML_VECXPR_VECXPR_COMPARE(  operator<, et::OpLess)

CML_VEC_VEC_COMPARE(        operator>, et::OpGreater)
CML_VECXPR_VEC_COMPARE(     operator>, et::OpGreater)
CML_VEC_VECXPR_COMPARE(     operator>, et::OpGreater)
CML_VECXPR_VECXPR_COMPARE(  operator>, et::OpGreater)

CML_VEC_VEC_COMPARE(        operator<=, et::OpLessEqual)
CML_VECXPR_VEC_COMPARE(     operator<=, et::OpLessEqual)
CML_VEC_VECXPR_COMPARE(     operator<=, et::OpLessEqual)
CML_VECXPR_VECXPR_COMPARE(  operator<=, et::OpLessEqual)

CML_VEC_VEC_COMPARE(        operator>=, et::OpGreaterEqual)
CML_VECXPR_VEC_COMPARE(     operator>=, et::OpGreaterEqual)
CML_VEC_VECXPR_COMPARE(     operator>=, et::OpGreaterEqual)
CML_VECXPR_VECXPR_COMPARE(  operator>=, et::OpGreaterEqual)

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
