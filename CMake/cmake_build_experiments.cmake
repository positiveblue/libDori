# Experiments
# ==================

option (BUILD_EXPERIMENTS "Whether we should build experiments or not" ON)
if(BUILD_EXPERIMENTS)

  set(LDORI_EXP_CARDINALITY_SOURCE "${PROJECT_SOURCE_DIR}/experiments/exp_cardinality.cpp")

  add_executable(exp_cardinality ${LDORI_EXP_CARDINALITY_SOURCE} ${LDORI_C_CPP_SOURCE} ${LSTREAM_THIRD_PARTY})

endif()