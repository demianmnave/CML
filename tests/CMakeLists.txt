# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

# Need the test macros:
include(CMLTestMacros)
include_directories(${Boost_INCLUDE_DIRS})

# Disable Boost auto-linking on MSVC
if(MSVC)
  add_definitions(-DBOOST_ALL_NO_LIB)
endif()

# Common functionality tests:
add_subdirectory(common)

# Storage tests:
add_subdirectory(storage)

# cml::vector<> tests:
add_subdirectory(vector)

# cml::matrix<> tests:
add_subdirectory(matrix)

# cml::quaternion<> tests:
add_subdirectory(quaternion)

# mathlib tests:
add_subdirectory(mathlib)

# util tests:
add_subdirectory(util)

# --------------------------------------------------------------------------
# vim:ft=cmake
