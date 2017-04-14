# Cli Tools
# ==================

option (BUILD_CLI_TOOLS "Whether we should build cli tools or not" ON)
if(BUILD_CLI_TOOLS)

  # Build cardinality estimator
  set(LDORI_SIMILARITY_SOURCE "${PROJECT_SOURCE_DIR}/cli/similarity.cpp")
  add_executable(similarity ${LDORI_SIMILARITY_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})
  install_targets(/bin similarity)

endif()