# Cli Tools
# ==================

option (BUILD_CARDINALITY "Whether we should build cardinality cli or not" OFF)
if(BUILD_CARDINALITY)

  set(LDORI_CARDINALITY_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/cardinality.cpp")

  add_executable(cardinality ${LDORI_CARDINALITY_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

  install_targets(/bin cardinality)
endif()

option (BUILD_SAMPLE "Whether we should build sample cli or not" OFF)
if(BUILD_SAMPLE)

  set(LDORI_SAMPLE_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/sample.cpp")

  add_executable(sample ${LDORI_SAMPLE_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

  install_targets(/bin sample)
endif()