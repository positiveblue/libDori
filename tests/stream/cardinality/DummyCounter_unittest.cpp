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
TEST_CASE( "DummyCounter cardinality for 1000.txt", "[DummyCounter]" ) {
  // Data file path
  std::string data_path = "../datasets/1000.txt";
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

  REQUIRE(DC->cardinality() == 1000);
  REQUIRE(DC->elementsOffered() == 1000);
  
  file.close();
}

TEST_CASE( "DummyCounter cardinality for 5000.txt", "[DummyCounter]" ) {
  // Data file path
  std::string data_path = "../datasets/5000.txt";
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

  REQUIRE(DC->cardinality() == 5000);
  REQUIRE(DC->elementsOffered() == 5000);
  
  file.close();
}

TEST_CASE( "DummyCounter cardinality for 10000.txt", "[DummyCounter]" ) {
  // Data file path
  std::string data_path = "../datasets/10000.txt";
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

  REQUIRE(DC->cardinality() == 10000);
  REQUIRE(DC->elementsOffered() == 10000);
  
  file.close();
}
