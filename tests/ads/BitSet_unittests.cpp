#include "catch/catch_lib.hpp"
#include "ads/BitSet.hpp"


TEST_CASE( "Creating BitSet object", "[BitSet]" ) {
  dori::stream::BitSet BS = dori::stream::BitSet(66);
}

TEST_CASE( "Checking the BitSet object", "[BitSet]" ) {
  auto bs = dori::stream::BitSet(66);

  REQUIRE(bs.size() == 66);

  REQUIRE(bs.getValue(0) == false);

  bs.flip(0);

  REQUIRE(bs.getValue(0) == true);

  bs.flip(0);

  REQUIRE(bs.getValue(0) == false);
  
  bs.setOne(55);
  bs.setOne(45);
  bs.setOne(32);

  REQUIRE(bs.getValue(54) == false);
  REQUIRE(bs.getValue(55) == true);
  REQUIRE(bs.getValue(56) == false);

  REQUIRE(bs.getValue(45) == true);
  REQUIRE(bs.getValue(32) == true);

  bs.clear();

  REQUIRE(bs.getValue(55) == false);
  REQUIRE(bs.getValue(45) == false);
  REQUIRE(bs.getValue(32) == false);
}
