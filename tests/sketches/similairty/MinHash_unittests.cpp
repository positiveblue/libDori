#include <iostream>
#include <fstream>
#include "catch/catch_lib.hpp"
#include "sketches/similarity/MinHash.hpp"
#include "../../helpers/reader.hpp"



TEST_CASE( "Creating MinHash object", "[MinHash]" ) {
  dori::sketches::MinHash<std::string> MH10 {10, 1};
  REQUIRE(MH10.nFunctions() == 10);
  REQUIRE(MH10.nBuckets() == 1);
  REQUIRE(MH10.size() == 10);


  dori::sketches::MinHash<std::string> MH100 {10, 10};
  REQUIRE(MH100.nFunctions() == 10);
  REQUIRE(MH100.nBuckets() == 10);
  REQUIRE(MH100.size() == 100);

  std::vector<std::uint64_t> seeds {0,1,2,3,4,5,6,7,8,9};
  dori::sketches::MinHash<std::string> MHSeeds {seeds, 5};

  REQUIRE(MHSeeds.nFunctions() == 10);
  REQUIRE(MHSeeds.nBuckets() == 5);
  REQUIRE(MHSeeds.size() == 50);

}

TEST_CASE( "Comparing Documents with MinHash", "[MinHash Similarity]" ) {
  /*
  std::vector<std::uint64_t> seeds {100, 0};

  for (int i = 0; i < seeds.nFunctions(); ++i)
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


*/
  


}
