/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef traits_h
#define traits_h

#include <cml/et/tags.h>

/* XXX This is here temporarily, should be rolled into the traits classes
 * eventually:
 */
#define SCALAR_ARG_TYPE const ScalarT&

namespace cml {
namespace et {

/** The expression traits class.
 *
 * The traits class is used to provide uniform access to expression
 * objects, including scalars, when used in vector and matrix expressions.
 * One especially useful property for scalars is that scalars are
 * implicitly "promoted" to vectors or scalars as necessary via the
 * ExprTraits's get() method.  Without this functionality, a separate
 * expression tree node would be needed to hold a scalar, which would
 * adversely affect performance.
 *
 * @internal This is also currently used for determining traits of scalar
 * types from the scalar operators (+,-,etc.).  Really, a separate traits
 * class should probably be used for this (e.g. ScalarTraits).
 */
template<typename T> struct ExprTraits
#if defined(CML_NO_DEFAULT_EXPR_TRAITS)
/* For testing, don't default to scalar traits: */
#else
{
    /* Standard: */
    typedef T expr_type;
    typedef T value_type;
    typedef T& reference;
    typedef T const_reference;
    typedef scalar_result_tag result_tag;
    typedef fixed_memory_tag memory_tag;
    typedef unit_size_tag size_tag;
    typedef expr_leaf_tag node_tag;

    /** Vector-like access, just returns the value. */
    value_type get(const_reference v, size_t) const { return v; }

    /** Matrix-like access, just returns the value. */
    value_type get(const_reference v, size_t, size_t) const { return v; }

    /** Size is always 1. */
    size_t size(const_reference) const { return 1; }

    /** This always returns true. */
    bool check_sizes(const_reference) const { return true; }
}
#endif
;

#if defined(CML_NO_DEFAULT_EXPR_TRAITS)
template<> struct ExprTraits<double>
{
    /* Standard: */
    typedef double expr_type;
    typedef double value_type;
    typedef double& reference;
    typedef double const_reference;
    typedef scalar_result_tag result_tag;
    typedef fixed_memory_tag memory_tag;
    typedef unit_size_tag size_tag;
    typedef double result_type;
    typedef expr_leaf_tag node_tag;

    /** Vector-like access, just returns the value. */
    value_type get(double v, size_t) const { return v; }

    /** Matrix-like access, just returns the value. */
    value_type get(double v, size_t, size_t) const { return v; }

    /** Size is always 1. */
    size_t size(double) const { return 1; }

    /** This always returns true. */
    bool check_sizes(double) const { return true; }
};
#endif

} // namespace et
} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
