# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

# Search for Boost.Test:
set(Boost_USE_STATIC_LIBS TRUE)
set(Boost_USE_STATIC_RUNTIME TRUE)
find_package(Boost COMPONENTS unit_test_framework)

# Link to Boost:
link_directories(${Boost_LIBRARY_DIR})

# cml::vector<> tests:
add_subdirectory(vector)

# --------------------------------------------------------------------------
# vim:ft=cmake
