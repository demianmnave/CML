# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------
# @file
# @brief

PROJECT(CML)

# Add the toplevel directory to all includes:
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR})

# Setup the timing tests:
ADD_SUBDIRECTORY(tests)

# --------------------------------------------------------------------------
# vim:ft=cmake
