#include <iostream>
#include <fstream>
#include "catch/catch_lib.hpp"
#include "sketches/similarity/MinHash.hpp"
#include "../../helpers/reader.hpp"



TEST_CASE( "Creating MinHash object", "[MinHash]" ) {
  dori::sketches::MinHash<std::string> MH10 {10};
  dori::sketches::MinHash<std::string> MH100 {100};

  std::vector<std::uint64_t> seeds {0,1,2,3,4};
  dori::sketches::MinHash<std::string> MHSeeds {seeds};

  REQUIRE(MH10.size() == 10);
  REQUIRE(MH100.size() == 100);

  REQUIRE(MHSeeds.size() == 5);

}

TEST_CASE( "Comparing Documents with MinHash", "[MinHash Similarity]" ) {
  std::vector<std::uint64_t> seeds {100, 0};

  for (int i = 0; i < seeds.size(); ++i)
    seeds[i] = i;


  std::string word;

  // MinHash king henry IV
  dori::sketches::MinHash<std::string> kingHenryIV {seeds};
  std::ifstream file = openFile("../datasets/Shakespeare/king_henry_IV.txt");
  while (file >> word) {
    kingHenryIV.offer(word);
  }

  // MinHash king henry V
  dori::sketches::MinHash<std::string> kingHenryV {seeds};
  file = openFile("../datasets/Shakespeare/king_henry_V.txt");
  while (file >> word) {
    kingHenryV.offer(word);
  }

  // MinHash richard II 
  dori::sketches::MinHash<std::string> richardII {seeds};
  file = openFile("../datasets/Shakespeare/richard_II.txt");
  while (file >> word) {
    richardII.offer(word);
  }

 REQUIRE(richardII.compare(kingHenryV) == 5);



  


}
