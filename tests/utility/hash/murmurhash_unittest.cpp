#include "catch.hpp"
#include "Hasher.hpp"

namespace lsutils = ls::utility;

TEST_CASE( "Murmurhash3 object created", "[Murmurhash3]" ) {
  lsutils::IHasher* hasher = new lsutils::MurmurHash();
}