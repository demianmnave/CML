# --------------------------------------------------------------------------
# @@COPYRIGHT@@
# --------------------------------------------------------------------------

add_library(cml_test_main STATIC catch_main.cpp catch.hpp catch_runner.h)
target_include_directories(cml_test_main
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}
  PRIVATE ${CML_ROOT}
)

set_target_properties(cml_test_main
  PROPERTIES FOLDER "cml-tests/main"
  MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY}
)

get_target_property(_path cml_test_main SOURCE_DIR)
get_target_property(_sources cml_test_main SOURCES)
source_group(TREE "${_path}" FILES ${_sources})