#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "catch/catch_lib.hpp"
#include "stream/cardinality/Recordinality.hpp"


TEST_CASE( "Creating Recordinality object", "[Recordinality]" ) {
  auto recordinailty_counter = dori::stream::Recordinality(16);
  auto bigger_recordinailty_counter = dori::stream::Recordinality(64);
}

TEST_CASE( "Recordinality elementsOffered for D1.txt", "[Recordinality]" ) {
  // Data file path
  std::string data_path = "../datasets/D1.txt";
  dori::stream::ICardinality* recordinality = new dori::stream::Recordinality(32);

  std::ifstream file(data_path);

  if (!file) {
    REQUIRE( false );
  }

  std::string line;
  while (!file.eof()) {
    std::getline(file, line);
    recordinality->offer(line);
  }

  REQUIRE(recordinality->elementsOffered() == 17221);
  
  file.close();
}
