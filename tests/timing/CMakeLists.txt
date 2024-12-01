#*-------------------------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Timing)

macro(cml_add_timing _name)
  set(ExecName "${_name}")
  cml_add_executable(${_name} ${ARGN})
  set_target_properties(${ExecName} PROPERTIES FOLDER "cml-tests/timing")
  target_link_libraries(${ExecName} cml cml_timing)
endmacro()

# Support lib:
set(cml_timing_HEADERS
  timing.h
  uniform_random_rotation.h
  make_rotation_matrix_pairs.h
)

set(cml_timing_SOURCES
  timing.cpp
)

set(cml_timing_INLINES
  uniform_random_rotation.tpp
  make_rotation_matrix_pairs.tpp
)

add_library(cml_timing STATIC
  ${cml_timing_HEADERS}
  ${cml_timing_INLINES}
  ${cml_timing_SOURCES}
)
cml_default_compile_options(cml_timing)
target_include_directories(cml_timing
  PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(cml_timing PUBLIC cml)
set_source_files_properties(${cml_timing_INLINES} PROPERTIES
  HEADER_FILE_ONLY 1)
set_target_properties(cml_timing PROPERTIES FOLDER "cml-tests/timing")
get_target_property(_path cml_timing SOURCE_DIR)
get_target_property(_sources cml_timing SOURCES)
source_group(TREE "${_path}" FILES ${_sources})

# Naive C-array mxm timing:
cml_add_timing(cmatrix_mxm_timing
  matrix_mxm_timing.cpp
  cmatrix.h cmatrix_mxm.inl
)
target_compile_definitions(cmatrix_mxm_timing
  PRIVATE
  CML_TIMING_MxM_INL="cmatrix_mxm.inl"
)

# Naive expression template mxm timing:
cml_add_timing(expr_mxm_timing
  matrix_mxm_timing.cpp
  expr_mxm.inl
)
target_compile_definitions(expr_mxm_timing
  PRIVATE
  CML_TIMING_MxM_INL="expr_mxm.inl"
)

# SIMD C-array mxm timing:
cml_add_timing(cmatrix_simd_mxm_timing
  matrix_mxm_timing.cpp
  cmatrix.h cmatrix_simd_mxm.inl
)
target_compile_definitions(cmatrix_simd_mxm_timing
  PRIVATE
  CML_TIMING_MxM_INL="cmatrix_simd_mxm.inl"
)
if(MSVC)
  target_compile_options(cmatrix_simd_mxm_timing
    PRIVATE
    "/arch:AVX2"
  )
endif()

# SIMD expression mxm timing:
cml_add_timing(expr_simd_mxm_timing
  matrix_mxm_timing.cpp
  expr_simd_mxm.inl
)
target_compile_definitions(expr_simd_mxm_timing
  PRIVATE
  CML_TIMING_MxM_INL="expr_simd_mxm.inl"
)
if(MSVC)
  target_compile_options(expr_simd_mxm_timing
    PRIVATE
    "/arch:AVX2"
  )
endif()
