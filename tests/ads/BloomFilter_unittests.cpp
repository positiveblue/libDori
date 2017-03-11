#include "catch/catch_lib.hpp"
#include "utils/hash/Hasher.hpp"
#include "ads/BloomFilter.hpp"

TEST_CASE( "Creating BloomFilter object", "[BloomFilter]" ) {
  dori::stream::BloomFilter BF = dori::stream::BloomFilter(3000, 0.01);
}

TEST_CASE( "Checking the BloomFilter object", "[BloomFilter]" ) {
  auto bf = dori::stream::BloomFilter(3000, 0.01);

  // This comes from the formula of obtining the number of bits and functions
  REQUIRE(bf.size() == 28756);
  
  bf.insert("hello");
  bf.insert("how");
  bf.insert("are");
  bf.insert("you");
  bf.insert("?");

  REQUIRE(bf.contains("hello"));
  REQUIRE(bf.contains("how"));
  REQUIRE(bf.contains("are"));
  REQUIRE(bf.contains("you"));
  REQUIRE(bf.contains("?"));

  // This test is a probabilistic test BUT should pass very often
  bool shoud_be_false = bf.contains("Jordi") & bf.contains("!");
  REQUIRE(not shoud_be_false);
}
