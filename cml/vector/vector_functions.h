/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef vector_functions_h
#define vector_functions_h

namespace cml {

/** Squared length of a vector. */
template<typename E, class AT>
inline typename vector<E,AT>::value_type
length_squared(const vector<E,AT>& arg)
{
    return arg.length_squared();
}

/** Squared length of a vector expr. */
template<typename XprT>
inline typename XprT::value_type
length_squared(VECXPR_ARG_TYPE arg)
{
    return arg.length_squared();
}

/** Length of a vector. */
template<typename E, class AT>
inline typename vector<E,AT>::value_type
length(const vector<E,AT>& arg)
{
    return arg.length();
}

/** Length of a vector expr. */
template<typename XprT>
inline typename XprT::value_type
length(VECXPR_ARG_TYPE arg)
{
    return arg.length();
}

/** Normalize a vector. */
template<typename E, class AT>
inline vector<E, AT>&
normalize(vector<E,AT>& arg)
{
    return arg.normalize();
}

/** Normalize a vector expr. */
template<typename XprT>
inline typename XprT::result_type
normalize(VECXPR_ARG_TYPE arg)
{
    return arg.normalize();
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
