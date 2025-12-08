# Setup the selected compiler.
include_guard()

include(${CMAKE_CXX_COMPILER_ID}-compiler)
cml_configure_compiler()

set(_cml_compiler_ver "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
set(_cml_compiler_info "${_cml_compiler_ver} (${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}-${CML_SIMD})")
message(STATUS "${PROJECT_NAME}: configuring for ${_cml_compiler_info}")