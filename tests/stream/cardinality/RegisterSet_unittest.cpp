#include "catch/catch_lib.hpp"
#include "stream/cardinality/RegisterSet.hpp"

TEST_CASE( "Creating RegisterSet object", "[RegisterSet]" ) {
  ls::stream::RegisterSet RS = ls::stream::RegisterSet(64);
}