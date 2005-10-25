/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef expr_h
#define expr_h

#include <cml/et/traits.h>

namespace cml {
namespace et {

/** A node in the expression tree.
 *
 * This reduces the number of different operators required to combine
 * expressions and objects.
 *
 * @internal There are a variety of optimizations that can be performed via
 * this class.
 */
template<typename ExprT>
class Xpr
{
  public:

    typedef Xpr<ExprT> expr_type;
    typedef expr_type const_reference;
    typedef typename expr_type::value_type value_type;
    typedef typename Traits<ExprT>::const_reference expr_reference;


  public:

    /** Evaluate the contained operator and return the result. */
    result_type operator()(size_t i) const { return m_op(i); }


  public:

    /** Construct from the contained expression. */
    Xpr(const ExprT& e) : m_expr(e) {}


  protected:

    expr_reference m_expr;
};

/** Traits for the Xpr class. */
template<typename ExprT>
struct ExprTraits< Xpr<ExprT> >
{
    result_type get(const expr_type& v, size_t i) { return v[i]; }
    size_t size(const expr_type& v) { return v.size(); }
};

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
