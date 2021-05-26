# -*- cmake -*- -----------------------------------------------------------
# @@COPYRIGHT@@
#*-------------------------------------------------------------------------

project(CML_Testing_Timing)

macro(cml_add_timing _Name)
  set(ExecName "${_Name}")
  add_executable(${ExecName} ${ARGN})
  set_target_properties(${ExecName} PROPERTIES FOLDER "CML-Timing")
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
target_include_directories(cml_timing
  PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_source_files_properties(${cml_timing_INLINES} PROPERTIES
  HEADER_FILE_ONLY 1)
if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
  set(_inlines_group "Inlines\\")
  source_group("${_inlines_group}" FILES ${cml_timing_INLINES})
endif()

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


#if(MSVC)
#set_source_files_properties(matrix_mxm_timing.cpp PROPERTIES COMPILE_OPTIONS "/Fa\$(IntDir)")
#endif()