# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

# Search for Boost.Test:
set(Boost_USE_STATIC_LIBS TRUE)
set(Boost_USE_STATIC_RUNTIME TRUE)
find_package(Boost COMPONENTS unit_test_framework)

# Link to Boost:
link_directories(${Boost_LIBRARY_DIR})

# Common functionality tests:
add_subdirectory(common)

# Storage tests:
add_subdirectory(storage)

# cml::vector<> tests:
add_subdirectory(vector)

# cml::matrix<> tests:
add_subdirectory(matrix)

# --------------------------------------------------------------------------
# vim:ft=cmake
