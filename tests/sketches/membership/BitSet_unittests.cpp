#include "catch/catch_lib.hpp"
#include "sketches/membership/BitSet.hpp"


TEST_CASE( "Creating BitSet object", "[BitSet]" ) {
  dori::sketches::BitSet BS = dori::sketches::BitSet(66);
}

TEST_CASE( "Checking the BitSet object", "[BitSet]" ) {
  auto bs = dori::sketches::BitSet(66);

  REQUIRE(bs.size() == 66);

  REQUIRE(bs.value(0) == false);

  bs.flip(0);

  REQUIRE(bs.value(0) == true);

  bs.flip(0);

  REQUIRE(bs.value(0) == false);
  
  bs.setOne(55);
  bs.setOne(45);
  bs.setOne(32);

  REQUIRE(bs.value(54) == false);
  REQUIRE(bs.value(55) == true);
  REQUIRE(bs.value(56) == false);

  REQUIRE(bs.value(45) == true);
  REQUIRE(bs.value(32) == true);

  bs.clear();

  REQUIRE(bs.value(55) == false);
  REQUIRE(bs.value(45) == false);
  REQUIRE(bs.value(32) == false);
}
