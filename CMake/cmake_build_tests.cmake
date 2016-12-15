# Tests and examples
# ==================
include(CTest)

option (BUILD_TESTS "Whether we should build it as a shared library or not" ON)
if(BUILD_TESTS)

  file(GLOB_RECURSE LSTREAM_TEST_SOURCE RELATIVE "${PROJECT_SOURCE_DIR}"
    "tests/*.hpp" "tests/*.cpp" )

  add_executable(libstream-tests ${LSTREAM_TEST_SOURCE} ${LSTREAM_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

endif()