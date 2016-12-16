# Cli Tools
# ==================

option (BUILD_CARDINALITY "Whether we should build cardinality cli or not" OFF)
if(BUILD_CARDINALITY)

  set(LDORI_CARDINALITY_SOURCE "${PROJECT_SOURCE_DIR}/cli/stream/cardinality.cpp")

  add_executable(cardinality ${LDORI_CARDINALITY_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

endif()