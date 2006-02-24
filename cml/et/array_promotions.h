/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 *
 * Defines promotions between array types.
 *
 * @todo Not all type combinations are represented here.
 */

#ifndef array_promotions_h
#define array_promotions_h

#include <cml/core/cml_meta.h>
#include <cml/fixed.h>
#include <cml/dynamic.h>

namespace cml {
namespace et {

#define VAL_MAX(_a_,_b_)        ( ((_a_)>(_b_))?(_a_):(_b_) )

/** Class to promote array types.
 *
 * Both argument types must be arrays.
 *
 * @sa fixed_1D
 * @sa fixed_2D
 * @sa dynamic_1D
 * @sa dynamic_2D
 */
template<class AT1, class AT2>
struct ArrayPromote
{
    /* Deduce the proper type based upon the characteristics of AT1 and
     * AT2.  This is the table of type conversions:
     *
     *         AT1               AT2              Result
     *   memory   size     memory   size      memory   size
     *
     *   fixed    fixed    fixed    fixed     fixed    fixed
     *   fixed    fixed    dynamic  dynamic   dynamic  dynamic
     *   fixed    fixed    external fixed     fixed    fixed
     *
     *   dynamic  dynamic  fixed    fixed     dynamic  dynamic
     *   dynamic  dynamic  dynamic  dynamic   dynamic  dynamic
     *   dynamic  dynamic  external fixed     dynamic  dynamic
     *
     *   external fixed    external fixed     fixed    fixed
     *   external fixed    fixed    fixed     fixed    fixed
     *   external fixed    dynamic  dynamic   dynamic  dynamic
     *
     *   Note: Fixed-size results take on the largest dimensions that will
     *   accomodate both argument array types, since there is no way to
     *   deduce the proper size without knowing the expression.  This means
     *   that the array types must be provided to ArrayPromote such that
     *   this behavior is correct.
     *
     *   Note: if one argument is a dynamic array, the result must also be
     *   a dynamic array. The resulting layout and allocator will be taken
     *   from the first dynamic array argument.
     */

    /* Get tags from the arguments into shorthand names: */
    typedef type_pair<
        typename AT1::memory_tag, typename AT1::size_tag> left_type;
    typedef type_pair<
        typename AT2::memory_tag, typename AT2::size_tag> right_type;

    /* Shorthand for the combinations: */
    typedef type_pair<fixed_memory_tag,fixed_size_tag> fixed_fixed;
    typedef type_pair<dynamic_memory_tag,dynamic_size_tag> dynamic_dynamic;
    typedef type_pair<external_memory_tag,fixed_size_tag> external_fixed;

    /* Figure out the layout of the promoted array: */
    typedef typename select_if<
        same_type<typename AT1::layout, typename AT2::layout>::is_true,
        typename AT1::layout,
        CML_DEFAULT_ARRAY_LAYOUT>::result default_layout;

    /* Shorthand for the resulting fixed_fixed type, if matched: */
    typedef cml::fixed<
        VAL_MAX((long)AT1::array_rows, (long)AT2::array_rows),
        VAL_MAX((long)AT1::array_cols, (long)AT2::array_cols),
        default_layout> fixed_fixed_result;

    /* Shorthand for the resulting dynamic_dynamic type, if matched: */
    typedef cml::dynamic<default_layout, typename AT1::allocator_type>
        dynamic_dynamic_result;

    typedef typename select_switch<
        left_type,
        fixed_fixed,       typename select_switch<
                                right_type,
                                fixed_fixed,       fixed_fixed_result,
                                dynamic_dynamic,   dynamic_dynamic_result,
                                external_fixed,    fixed_fixed_result,
                                meta::Default,     void
                           >::result,

        dynamic_dynamic,   typename select_switch<
                                right_type,
                                fixed_fixed,       dynamic_dynamic_result,
                                dynamic_dynamic,   dynamic_dynamic_result,
                                external_fixed,    dynamic_dynamic_result,
                                meta::Default,     void
                           >::result,

        external_fixed,    typename select_switch<
                                right_type,
                                fixed_fixed,       fixed_fixed_result,
                                dynamic_dynamic,   dynamic_dynamic_result,
                                external_fixed,    fixed_fixed_result,
                                meta::Default,     void
                           >::result,


        /* Default is void (an error): */
        meta::Default,     void

    /* The resulting array type: */
    >::result type;
};

} // namespace et
} // namespace cml

/* Cleanup internal macros: */
#undef VAL_MAX
#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
