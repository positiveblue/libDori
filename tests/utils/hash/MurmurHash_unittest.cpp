#include "catch/catch_lib.hpp"
#include "utils/hash/hash.hpp"

TEST_CASE( "Creating Murmurhash object", "[Murmurhash3]" ) {
  dori::utils::IHasher* hasher = new dori::utils::MurmurHash();
}