cmake_minimum_required(VERSION 3.2.2) # CMake version check

# we don't allow libStream to be build in the source directory
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set (LIBSTREAM_VERSION_MAJOR 0)
set (LIBSTREAM_VERSION_MINOR 1)


# Create project "libStream"
project(libStream)

# Compiler configuration
include (${CMAKE_SOURCE_DIR}/CMake/cmake_compiler_flags.cmake)
message (STATUS "Building on ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR} on $ENV{HOSTNAME}")

# Build as SharedLibrary
option (BUILD_SHARED_LIBS "Whether we should build it as a shared library or not" ON)
if(BUILD_SHARED_LIBS)
  set(LIBRARY_TYPE SHARED)
else()
  set(LIBRARY_TYPE STATIC)
endif()


# The main library
# ================

message(STATUS 
  "Appending ${PROJECT_SOURCE_DIR}/include for LibStream's source includes")
include_directories("${PROJECT_SOURCE_DIR}/include")

# Get the combined list of source files for LibStream
# ---------------------------------------------------
file(GLOB_RECURSE LSTREAM_C_CPP_SOURCE RELATIVE "${PROJECT_SOURCE_DIR}"
  "src/*.cpp" "include/*.hpp")


# Define the main library for LibStream
# -------------------------------------
add_library(stream ${LSTREAM_C_CPP_SOURCE})


# Dependency libraries
# -------------------------------------
target_link_libraries(stream ${LINK_LIBS})


# Compiler flags
# -------------------------------------
if(CMAKE_CXX_FLAGS)
  set_target_properties(stream PROPERTIES LINK_FLAGS ${CMAKE_CXX_FLAGS})
endif()



# Tests and examples
# ==================
include(CTest)

option (BUILD_TESTS "Whether we should build it as a shared library or not" ON)
if(BUILD_TESTS)

  file(GLOB_RECURSE LSTREAM_TEST_SOURCE RELATIVE "${PROJECT_SOURCE_DIR}"
    "tests/*.hpp" "tests/*.cpp" )

  add_executable(libstream-tests ${LSTREAM_TEST_SOURCE} ${LSTREAM_C_CPP_SOURCE})

endif()