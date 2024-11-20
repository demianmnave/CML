/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#pragma once

#include <stdexcept>

/** Throw exception _e_ with message _msg_ if _cond_ is false. */
#define cml_require(_cond_, _e_, _msg_)                                        \
  if((_cond_)) {                                                               \
  } else throw _e_(_msg_)
