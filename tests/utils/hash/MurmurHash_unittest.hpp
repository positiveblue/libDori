#include "catch/catch.hpp"
#include "utils/hash/hash.hpp"

TEST_CASE( "Creating Murmurhash object", "[Murmurhash3]" ) {
  ls::utils::IHasher* hasher = new ls::utils::MurmurHash();
}