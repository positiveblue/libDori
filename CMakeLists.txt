cmake_minimum_required(VERSION 3.0.0) # CMake version check

# we don't allow libStream to be build in the source directory
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set (DORI_VERSION_MAJOR 0)
set (DORI_VERSION_MINOR 1)


# Create project "libDori"
project(libDori)

# Include Directories
# ================

# LibDori files
include_directories("${PROJECT_SOURCE_DIR}/include")

# Third party libraries
include_directories("${PROJECT_SOURCE_DIR}/third_party")


# LibDori's combined list of source files
# ================
file(GLOB_RECURSE LDORI_C_CPP_SOURCE RELATIVE "${PROJECT_SOURCE_DIR}"
  "src/*.cpp" "include/*.hpp")


# Compiler configuration
# ==================
include (${CMAKE_SOURCE_DIR}/CMake/cmake_compiler_flags.cmake)


# Build as Shared Library
# ==================
# include (${CMAKE_SOURCE_DIR}/CMake/cmake_build_shared_library.cmake)


# Build Tests and examples
# ==================
# include (${CMAKE_SOURCE_DIR}/CMake/cmake_build_tests.cmake)

# Build CLI tools
# ==================
# include (${CMAKE_SOURCE_DIR}/CMake/cmake_build_cli_tools.cmake)

# libDori installation
# ==================
# include (${CMAKE_SOURCE_DIR}/CMake/cmake_libDori_installation.cmake)





