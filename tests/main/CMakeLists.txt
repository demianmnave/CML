# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

# Allow finding Catch2 locally first:
find_package(Catch2 3.8.1 CONFIG QUIET)

# If not found or already pulled, pull Catch2 at v3.8.1
if(NOT Catch2_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
  )

  FetchContent_MakeAvailable(Catch2)
endif()

cml_add_library(cml_test_main INTERFACE
  SOURCES catch_runner.h
  USES Catch2::Catch2WithMain cml
  FOLDER "cml-tests"
  SKIP_INSTALL
  )
target_include_directories(cml_test_main INTERFACE
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
if(DEFINED SIMDE_INCLUDE_DIR)
  target_include_directories(cml_test_main INTERFACE ${SIMDE_INCLUDE_DIR})
endif()