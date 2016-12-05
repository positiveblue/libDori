
# Hash Functions

# Murmurhash3
enable_testing()

add_executable(murmurhash_unittest murmurhash_unittest.cpp)
target_include_directories(murmurhash_unittest PUBLIC ${CMAKE_SOURCE_DIR}/utility/hash)
target_link_libraries(murmurhash_unittest Catch)
add_test(NAME TestBase COMMAND murmurhash_unittest)
