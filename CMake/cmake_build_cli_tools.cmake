# Cli Tools
# ==================

option (BUILD_CLI_TOOLS "Whether we should build cli tools or not" ON)
if(BUILD_CLI_TOOLS)

  # Build cardinality estimator
  set(LDORI_CARDINALITY_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/cardinality.cpp")
  add_executable(cardinality ${LDORI_CARDINALITY_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})
  install_targets(/bin cardinality)

  # Build frequency estimator
  set(LDORI_FREQUENCY_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/frequency.cpp")
  add_executable(frequency ${LDORI_FREQUENCY_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})
  install_targets(/bin frequency)

  # Build sampler
  set(LDORI_SAMPLE_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/sample.cpp")
  add_executable(sample ${LDORI_SAMPLE_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})
  install_targets(/bin sample)


  if(CMAKE_CXX_FLAGS)
    set_target_properties(cardinality PROPERTIES LINK_FLAGS ${CMAKE_CXX_FLAGS})
    set_target_properties(frequency PROPERTIES LINK_FLAGS ${CMAKE_CXX_FLAGS})
    set_target_properties(sample PROPERTIES LINK_FLAGS ${CMAKE_CXX_FLAGS})
  endif()
endif()
