#include <vector>
#include <string>
#include "catch/catch_lib.hpp"
#include "stream/cardinality/RecordSet.hpp"

// total words: 15
// total different words: 12
std::vector<std::string> words = {
  "fixed",
  "noisy",
  "lean",
  "ceaseless",
  "fanatical",
  "feigned",
  "cobweb",
  "panicky",
  "kindly",
  "low",
  "screw",
  "halting",
  "halting",
  "halting",
  "halting"
};

TEST_CASE( "Creating RecordSet object", "[RecordSet]" ) {
  auto rs = dori::stream::RecordSet(8);
  auto bigger_rs = dori::stream::RecordSet(64);
  
  // Checking the default destructor
  {
    auto rs = dori::stream::RecordSet(12);
  }

  auto biggest_rs = dori::stream::RecordSet(1024);

}

TEST_CASE( "Max size of a RecordSet object", "[RecordSet]" ) {
  auto rs = dori::stream::RecordSet(64);
  REQUIRE(rs.size() == 64);

  auto rs2 = dori::stream::RecordSet(128);
  REQUIRE(rs2.size() == 128);
}


TEST_CASE( "offer elements to a RecordSet object", "[RecordSet]" ) {
  auto rs = dori::stream::RecordSet(64);
  auto small_rs = dori::stream::RecordSet(8);
  
  std::set<std::string> unique_words;

  for (auto s : words) {
    rs.offer(s);
    small_rs.offer(s);
    unique_words.insert(s);
  }

  // With the big RecordSet the counter and the unique counter have to match
  REQUIRE(rs.counter() == words.size());
  REQUIRE(rs.recordCounter() == unique_words.size());

  // With the small RecordSet the counter has to match but not the RecordCounter
  REQUIRE(small_rs.counter() == words.size());
  REQUIRE(small_rs.recordCounter() <= unique_words.size());

}

TEST_CASE( "Sampling with a RecordSet object", "[RecordSet]" ) {
  auto rs = dori::stream::RecordSet(64);
  auto rs_with_sampling = dori::stream::RecordSet(64, true);
  std::set<std::string> unique_words;

  for (auto s : words) {
    rs.offer(s);
    rs_with_sampling.offer(s);
    unique_words.insert(s);
  }

  // RecordSet is not sampling by default
  auto sample = rs.sample();
  REQUIRE(sample.size() == 0);

  // RecordSet is sampling here
  sample = rs_with_sampling.sample();
  REQUIRE(sample.size() == unique_words.size());

}