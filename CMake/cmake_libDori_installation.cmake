
#----------------------------------------------------------------------------
# Install libDori
#TODO: global recurse is evil (cmake install does not get notified when new
#      files are added). We should compile the header list differently (e.g.
#      install an individual CMakeList files in directories).
file (GLOB_RECURSE HEADER_LIST RELATIVE ${CMAKE_SOURCE_DIR}/include *.hpp )
foreach (HEADER ${HEADER_LIST})
  string (REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
  install (FILES include/${HEADER} DESTINATION include/libDori/${DIR})
endforeach (HEADER)
