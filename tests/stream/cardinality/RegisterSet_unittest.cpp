#include "catch/catch_lib.hpp"
#include "stream/cardinality/RegisterSet.hpp"

TEST_CASE( "Creating RegisterSet object", "[RegisterSet]" ) {
  dori::stream::RegisterSet RS = dori::stream::RegisterSet(64);
}