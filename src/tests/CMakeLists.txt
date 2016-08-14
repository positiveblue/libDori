
#Setting headers for tests
set(TEST_HEADERS ${TEST_HEADERS} "include")

#Inclueding headers, such as Catch... into the project
include_directories(${TEST_HEADERS})


#Compile tests
set(TEST_SOURCES "tests_main.cpp")
add_executable(tests ${TEST_SOURCES})
