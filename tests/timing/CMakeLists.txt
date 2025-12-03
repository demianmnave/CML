#*-------------------------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

set(CML_TEST_GROUP "timing")

set(local_cxx_std cxx_std_23)

function(cml_add_timing _name)
  cml_add_executable(${_name}
   SOURCES ${ARGN}
   USES cml cml_test_timing
   FOLDER "cml-tests/${CML_TEST_GROUP}")
  target_compile_features(${_name} PRIVATE ${local_cxx_std})
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

target_compile_features(cml_test_timing INTERFACE ${local_cxx_std})

# Naive C-array mxm timing:
cml_add_timing(cmatrix_mxm_timing matrix_mxm_timing.cpp cmatrix.h cmatrix_mxm.inl)
target_compile_definitions(cmatrix_mxm_timing PRIVATE CML_TIMING_MxM_INL="cmatrix_mxm.inl")

# Naive expression template mxm timing:
cml_add_timing(expr_mxm_timing matrix_mxm_timing.cpp expr_mxm.inl)
target_compile_definitions(expr_mxm_timing PRIVATE CML_TIMING_MxM_INL="expr_mxm.inl")

# SIMD C-array mxm timing:
cml_add_timing(cmatrix_simd_mxm_timing matrix_mxm_timing.cpp cmatrix.h cmatrix_simd_mxm.inl)
target_compile_definitions(cmatrix_simd_mxm_timing PRIVATE CML_TIMING_MxM_INL="cmatrix_simd_mxm.inl")

# SIMD expression mxm timing:
cml_add_timing(expr_simd_mxm_timing matrix_mxm_timing.cpp expr_simd_mxm.inl)
target_compile_definitions(expr_simd_mxm_timing PRIVATE CML_TIMING_MxM_INL="expr_simd_mxm.inl")