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
  auto rs = ls::stream::RecordSet(8);
  auto bigger_rs = ls::stream::RecordSet(64);
  
  // Checking the default destructor
  {
    auto rs = ls::stream::RecordSet(12);
  }

  auto biggest_rs = ls::stream::RecordSet(1024);

}

TEST_CASE( "Max size of a RecordSet object", "[RecordSet]" ) {
  auto rs = ls::stream::RecordSet(64);
  REQUIRE(rs.getSize() == 64);

  auto rs2 = ls::stream::RecordSet(128);
  REQUIRE(rs2.getSize() == 128);
}


TEST_CASE( "offer elements to a RecordSet object", "[RecordSet]" ) {
  auto rs = ls::stream::RecordSet(64);
  auto small_rs = ls::stream::RecordSet(8);
  
  std::set<std::string> unique_words;

  for (auto s : words) {
    rs.offer(s);
    small_rs.offer(s);
    unique_words.insert(s);
  }

  // With the big RecordSet the counter and the unique counter have to match
  REQUIRE(rs.getCounter() == words.size());
  REQUIRE(rs.getRecordCounter() == unique_words.size());

  // With the small RecordSet the counter has to match but not the RecordCounter
  REQUIRE(small_rs.getCounter() == words.size());
  REQUIRE(small_rs.getRecordCounter() <= unique_words.size());

}

TEST_CASE( "Sampling with a RecordSet object", "[RecordSet]" ) {
  auto rs = ls::stream::RecordSet(64);
  auto rs_with_sampling = ls::stream::RecordSet(64, true);
  std::set<std::string> unique_words;

  for (auto s : words) {
    rs.offer(s);
    rs_with_sampling.offer(s);
    unique_words.insert(s);
  }

  // RecordSet is not sampling by default
  auto sample = rs.getSample();
  REQUIRE(sample.size() == 0);

  // RecordSet is sampling here
  sample = rs_with_sampling.getSample();
  REQUIRE(sample.size() == unique_words.size());

}