# CMake functions to query host information.

include_guard()

# Use CMake variables to try to determine the host architecture.
#
# Parameters:
#  OutArch (required) The variable to store the result to.
function(cml_get_host_arch OutArch)
  if(DEFINED CMAKE_CXX_COMPILER_ARCHITECTURE_ID)
    set(${OutArch} ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} PARENT_SCOPE)
  elseif(DEFINED CMAKE_HOST_SYSTEM_PROCESSOR)
    set(${OutArch} ${CMAKE_HOST_SYSTEM_PROCESSOR} PARENT_SCOPE)
  else()
    message(FATAL_ERROR "Cannot determine host architecture")
  endif()
endfunction()