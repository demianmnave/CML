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

add_library(cml_timing STATIC timing.h timing.cpp)
target_include_directories(cml_timing PUBLIC ${CMAKE_CURRENT_LIST_DIR})

cml_add_timing(cmatrix_mxm_timing
   cmatrix.h cmatrix_mxm.h cmatrix_mxm.cpp cmatrix_mxm_timing.cpp)