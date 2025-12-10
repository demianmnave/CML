#*-------------------------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

include(${CMAKE_CXX_COMPILER_ID}-compiler)

# Impose c++23 for the timing tests:
list(REMOVE_ITEM CML_PRIVATE_CXX_FEATURES ${CML_CXX_STD})
list(APPEND CML_PRIVATE_CXX_FEATURES cxx_std_23)

# Enable assembly output options for inspection:
if(DEFINED CML_ASSEMBLY_OPTIONS)
  list(APPEND CML_PRIVATE_CXX_OPTIONS ${CML_ASSEMBLY_OPTIONS})
endif()

if(DEFINED CML_SIMD)
  set(_suffix "-${CML_SIMD}")
endif()

function(cml_add_timing _name)
  cml_add_executable(${_name}
   SOURCES ${ARGN}
   USES cml cml_test_timing
   FOLDER "cml-tests/timing")
endfunction()

# Support lib:
set(cml_timing_HEADERS
  timing.h
  uniform_random_rotation.h
  make_rotation_matrix_pairs.h
)

set(cml_timing_INLINES
  uniform_random_rotation.tpp
  make_rotation_matrix_pairs.tpp
)

set_source_files_properties(${cml_timing_INLINES} PROPERTIES
  HEADER_FILE_ONLY 1)

cml_add_library(cml_test_timing INTERFACE
  SOURCES ${cml_timing_HEADERS} ${cml_timing_INLINES} ${cml_timing_SOURCES}
  USES cml
  FOLDER "cml-tests"
  SKIP_INSTALL
)
target_include_directories(cml_test_timing INTERFACE
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
if(DEFINED SIMDE_INCLUDE_DIR)
  target_include_directories(cml_test_timing INTERFACE ${SIMDE_INCLUDE_DIR})
endif()

# Naive C-array mxm timing:
cml_add_timing(cmatrix_mxm_timing${_suffix} matrix_mxm_timing.cpp cmatrix.h cmatrix_mxm.inl)
target_compile_definitions(cmatrix_mxm_timing${_suffix} PRIVATE CML_TIMING_MxM_INL="cmatrix_mxm.inl")

# Naive expression template mxm timing:
cml_add_timing(expr_mxm_timing${_suffix} matrix_mxm_timing.cpp expr_mxm.inl)
target_compile_definitions(expr_mxm_timing${_suffix} PRIVATE CML_TIMING_MxM_INL="expr_mxm.inl")

# SIMD C-array mxm timing:
cml_add_timing(cmatrix_simd_mxm_timing${_suffix} matrix_mxm_timing.cpp cmatrix.h cmatrix_simd_mxm.inl)
target_compile_definitions(cmatrix_simd_mxm_timing${_suffix} PRIVATE CML_TIMING_MxM_INL="cmatrix_simd_mxm.inl")

# SIMD expression mxm timing:
cml_add_timing(expr_simd_mxm_timing${_suffix} matrix_mxm_timing.cpp expr_simd_mxm.inl)
target_compile_definitions(expr_simd_mxm_timing${_suffix} PRIVATE CML_TIMING_MxM_INL="expr_simd_mxm.inl")