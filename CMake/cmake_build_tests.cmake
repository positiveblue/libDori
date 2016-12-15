# Tests and examples
# ==================
include(CTest)

option (BUILD_TESTS "Whether we should build it as a shared library or not" ON)
if(BUILD_TESTS)

  file(GLOB_RECURSE LDORI_TEST_SOURCE RELATIVE "${PROJECT_SOURCE_DIR}"
    "tests/*.hpp" "tests/*.cpp" )

  add_executable(dori-tests ${LDORI_TEST_SOURCE} ${LDORI_C_CPP_SOURCE} ${LDORI_THIRD_PARTY})

endif()