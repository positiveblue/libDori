
# Making CATCH visible
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "include")

# Testing
enable_testing()

add_subdirectory(utility)
