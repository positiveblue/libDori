

option (BUILD_SHARED_LIBS "Whether we should build it as a shared library or not" ON)
if(BUILD_SHARED_LIBS)
  set(LIBRARY_TYPE SHARED)

  # Define the shared library for LibStream
  # -------------------------------------
  add_library(stream ${LSTREAM_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

  # Compiler flags
  # -------------------------------------
  if(CMAKE_CXX_FLAGS)
    set_target_properties(stream PROPERTIES LINK_FLAGS ${CMAKE_CXX_FLAGS})
  endif()
endif()



