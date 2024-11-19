# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

# Allow finding Catch2 locally first:
find_package(Catch2 3.7.1 CONFIG QUIET)

# If not found or already pulled, pull Catch2 at v3.7.1
if(NOT Catch2_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
  )

  FetchContent_MakeAvailable(Catch2)
endif()

add_library(cml_test_main INTERFACE catch_runner.h)
target_include_directories(cml_test_main
  INTERFACE ${CMAKE_CURRENT_LIST_DIR} ${CML_ROOT}
)
target_link_libraries(cml_test_main
  INTERFACE Catch2::Catch2WithMain
)

set_target_properties(cml_test_main
  PROPERTIES FOLDER "cml-tests/main"
)

get_target_property(_path cml_test_main SOURCE_DIR)
get_target_property(_sources cml_test_main SOURCES)
source_group(TREE "${_path}" FILES ${_sources})