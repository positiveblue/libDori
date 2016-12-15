# Cli Tools
# ==================

option (BUILD_CARDINALITY "Whether we should build cardinality cli or not" ON)
if(BUILD_CARDINALITY)

  set(LSTREAM_CARDINALITY_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/cardinality.cpp")

  add_executable(cardinality ${LSTREAM_CARDINALITY_SOURCE} ${LSTREAM_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

endif()