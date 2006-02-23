/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef matrix_traits_h
#define matrix_traits_h

#include <cml/et/traits.h>

namespace cml {

/* Forward declare for traits class: */
template<typename E, class AT, typename O> class matrix;

/* Promotions belong in the et namespace: */
namespace et {

template<typename E, class AT, typename O>
struct ExprTraits< cml::matrix<E,AT,O> >
{
    typedef typename cml::matrix<E,AT,O> expr_type;
    typedef typename expr_type::value_type value_type;
    typedef typename expr_type::expr_reference reference;
    typedef typename expr_type::expr_const_reference const_reference;
    typedef typename expr_type::result_tag result_tag;
    typedef typename expr_type::size_tag size_tag;
    typedef cml::matrix<E,AT,O> result_type;

    value_type get(const expr_type& m, size_t i, size_t j) const {
        return m(i,j);
    }

    size_t rows(const expr_type& m) const { return m.rows(); }
    size_t cols(const expr_type& m) const { return m.cols(); }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
