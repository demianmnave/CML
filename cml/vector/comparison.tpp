/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#ifndef __CML_VECTOR_COMPARISON_TPP
#error "vector/comparison.tpp not included correctly"
#endif

#include <cml/vector/size_checking.h>

namespace cml {

template<class Sub1, class Sub2> inline bool operator<(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  cml::check_same_size(left, right);
  for(int i = 0; i < left.size(); i ++) {
    /**/ if(left[i] < right[i]) return true;	// Strictly less.
    else if(left[i] > right[i]) return false;	// Strictly greater.
    else continue;				// Equal.
  }

  /* Equal. */
  return false;
}

template<class Sub1, class Sub2> inline bool operator>(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  cml::check_same_size(left, right);
  for(int i = 0; i < left.size(); i ++) {
    /**/ if(left[i] > right[i]) return true;	// Strictly greater.
    else if(left[i] < right[i]) return false;	// Strictly less.
    else continue;				// Equal.
  }

  /* Equal. */
  return false;
}

template<class Sub1, class Sub2> inline bool operator==(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  cml::check_same_size(left, right);
  for(int i = 0; i < left.size(); i ++) {
    if(!(left[i] == right[i])) return false;	// Not equal.
  }
  return true;
}

template<class Sub1, class Sub2> inline bool operator<=(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  return !(left > right);
}

template<class Sub1, class Sub2> inline bool operator>=(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  return !(left < right);
}

template<class Sub1, class Sub2> inline bool operator!=(
  const readable_vector<Sub1>& left, const readable_vector<Sub2>& right
  )
{
  return !(left == right);
}

} // namespace cml

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2
