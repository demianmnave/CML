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

set(cml_timing_INLINES uniform_random_rotation.tpp)
add_library(cml_timing STATIC
  timing.h timing.cpp
  uniform_random_rotation.h
  ${cml_timing_INLINES}
  )
target_include_directories(cml_timing
 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_source_files_properties(${cml_timing_INLINES} PROPERTIES
 HEADER_FILE_ONLY 1)
if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
  set(_inlines_group "Inlines\\")
  source_group("${_inlines_group}" FILES ${cml_timing_INLINES})
endif()

cml_add_timing(cmatrix_mxm_timing
   cmatrix.h cmatrix_mxm.h cmatrix_mxm.cpp cmatrix_mxm_timing.cpp)