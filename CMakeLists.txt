cmake_minimum_required(VERSION 3.2.2) # CMake version check

# we don't allow libStream to be build in the source directory
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set (SKYLARK_VERSION_MAJOR 0)
set (SKYLARK_VERSION_MINOR 1)


# Create project "libStream"
project(libStream)


# Git and date info
include (${CMAKE_SOURCE_DIR}/CMake/cmake_git_version.cmake)
include (${CMAKE_SOURCE_DIR}/CMake/cmake_date.cmake)

# Compiler configuration
include (${CMAKE_SOURCE_DIR}/CMake/cmake_compiler_flags.cmake)
message (STATUS "Building on ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR} on $ENV{HOSTNAME}")


#--------------------------------------------------------------------------
# Includes
# Add the include directory path for libStream. Remember that only the top dir
# is added for the include, meaning that all the subdirs have to be explictly
# referred.
include_directories (${CMAKE_SOURCE_DIR})
include_directories (${CMAKE_BINARY_DIR})


include (${CMAKE_SOURCE_DIR}/CMake/cmake_build_tests.cmake)

#add_subdirectory (${CMAKE_SOURCE_DIR}/src/tests)

#include (${CMAKE_SOURCE_DIR}/CMake/cmake_libstream_install.cmake)
