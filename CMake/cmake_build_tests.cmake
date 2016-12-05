option (BUILD_TESTS "Whether we should build the tests" ON)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif (BUILD_TESTS)