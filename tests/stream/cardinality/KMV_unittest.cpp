#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "catch/catch_lib.hpp"
#include "stream/cardinality/KMV.hpp"


TEST_CASE( "Creating KMV object", "[KMV]" ) {
  auto KMV_counter = ls::stream::KMV(16);
  auto bigger_KMV_counter = ls::stream::KMV(64);
}

TEST_CASE( "KMV elementsOffered for D1.txt", "[KMV]" ) {
  // Data file path
  std::string data_path = "../datasets/D1.txt";
  ls::stream::ICardinality* kmv = new ls::stream::KMV(32);

  std::ifstream file(data_path);

  if (!file) {
    REQUIRE( false );
  }

  std::string line;
  while (!file.eof()) {
    std::getline(file, line);
    kmv->offer(line);
  }

  REQUIRE(kmv->cardinality() == 17221);
  REQUIRE(kmv->elementsOffered() == 17221);
  
  file.close();
}
