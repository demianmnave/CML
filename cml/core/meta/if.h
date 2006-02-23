/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef meta_if_h
#define meta_if_h

#include <cml/core/meta/common.h>

/** Select argument type based upon truth value. */
template<bool yn, typename TrueT, typename FalseT> struct select_if;

/** Result is TrueT if true. */
template<typename TrueT, typename FalseT>
struct select_if<true,TrueT,FalseT> {
    typedef TrueT result;
    enum { is_true = true };
};

/** Result is FalseT if false. */
template<typename TrueT, typename FalseT>
struct select_if<false,TrueT,FalseT> {
    typedef FalseT result;
    enum { is_true = false };
};

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp
