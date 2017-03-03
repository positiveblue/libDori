

option (BUILD_SHARED_LIBS "Whether we should build it as a shared library or not" ON)
if(BUILD_SHARED_LIBS)
  set(LIBRARY_TYPE SHARED)
  set(CMAKE_MACOSX_RPATH 1)
  # Define the shared library for Dori
  # -------------------------------------
  add_library(Dori ${LDORI_C_CPP_SOURCE} ${LDORI_THIRD_PARTY})

  # Compiler flags
  # -------------------------------------
  if(CMAKE_CXX_FLAGS)
    set_target_properties(Dori PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS})
  endif()

  install (TARGETS Dori DESTINATION lib/)

endif()



