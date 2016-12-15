#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "catch/catch_lib.hpp"
#include "stream/cardinality/DummyCounter.hpp"

TEST_CASE( "Creating DummyCounter object", "[DummyCounter]" ) {
  dori::stream::ICardinality* DC = new dori::stream::DummyCounter();
}

// Testing with 3 datasets provide with the library
TEST_CASE( "DummyCounter cardinality for D1.txt", "[DummyCounter]" ) {
  // Data file path
  std::string data_path = "../datasets/D1.txt";
  dori::stream::ICardinality* DC = new dori::stream::DummyCounter();

  std::ifstream file(data_path);

  if (!file) {
    REQUIRE( false );
  }

  std::string line;
  while (!file.eof()) {
    std::getline(file, line);
    DC->offer(line);
  }

  REQUIRE(DC->cardinality() == 3187);
  REQUIRE(DC->elementsOffered() == 17221);
  
  file.close();
}

TEST_CASE( "DummyCounter cardinality for D2.txt", "[DummyCounter]" ) {
  // Data file path
  std::string data_path = "../datasets/D2.txt";
  dori::stream::ICardinality* DC = new dori::stream::DummyCounter();

  std::ifstream file(data_path);

  if (!file) {
    REQUIRE( false );
  }

  std::string line;
  while (!file.eof()) {
    std::getline(file, line);
    DC->offer(line);
  }

  REQUIRE(DC->cardinality() == 23136);
  REQUIRE(DC->elementsOffered() == 384224);
  
  file.close();
}

TEST_CASE( "DummyCounter cardinality for D3.txt", "[DummyCounter]" ) {
  // Data file path
  std::string data_path = "../datasets/D3.txt";
  dori::stream::ICardinality* DC = new dori::stream::DummyCounter();

  std::ifstream file(data_path);

  if (!file) {
    REQUIRE( false );
  }

  std::string line;
  while (!file.eof()) {
    std::getline(file, line);
    DC->offer(line);
  }

  REQUIRE(DC->cardinality() == 5895);
  REQUIRE(DC->elementsOffered() == 61884);
  
  file.close();
}
