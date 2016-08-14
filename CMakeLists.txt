cmake_minimum_required(VERSION 3.2.2) # CMake version check

# Create project "libStream"
project(libStream)

# Enable c++14 standard
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14")


# Add subdirectories
add_subdirectory (src)

#set(SOURCE_FILES main.cpp)            # Add main.cpp file of project root directory as source file
#add_executable(simple_example ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable