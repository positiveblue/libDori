
#----------------------------------------------------------------------------
# Install libDori
#TODO: global recurse is evil (cmake install does not get notified when new
#      files are added). We should compile the header list differently (e.g.
#      install an individual CMakeList files in directories).
file (GLOB_RECURSE HEADER_LIST RELATIVE "${PROJECT_SOURCE_DIR}" "include/*.hpp")
foreach (HEADER ${HEADER_LIST})
  string (REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
  string(REGEX REPLACE "include/" "" OUTPUT_DIR ${DIR})
  install (FILES ${HEADER} DESTINATION include/libDori/${OUTPUT_DIR})
endforeach (HEADER)
