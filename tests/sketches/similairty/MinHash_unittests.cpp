#include "catch/catch_lib.hpp"
#include "sketches/similarity/MinHash.hpp"


TEST_CASE( "Creating MinHash object", "[MinHash]" ) {
  dori::sketches::MinHash<std::string> MH {10};
}