#include "catch/catch_lib.hpp"
#include "utils/hash/hash.hpp"

TEST_CASE( "Creating Hasher", "[Hasher]" ) {
  auto staticHasher = dori::utils::Hasher();
  auto dynHasher = new dori::utils::Hasher();
}

TEST_CASE( "Hash some arrays", "[Hasher]" ) {
  auto hasher = dori::utils::Hasher();

  char hola [4] = { 'h', 'o', 'l', 'a' };
  char mi [2] = { 'm', 'i' }; 
  char nombre [6] = { 'n', 'o', 'm', 'b', 'r', 'e'}; 
  char es [2] = { 'e', 's' }; 
  char jordi [5] = { 'j', 'o', 'r', 'd', 'i'}; 

  REQUIRE(hasher.hash64(hola, 4) == 0xad9daf762b0a1a35);
  REQUIRE(hasher.hash64(mi, 2) == 0x413d2970f96e78a5);
  REQUIRE(hasher.hash64(nombre, 6) == 0xbb3dc50d63cb3faf);
  REQUIRE(hasher.hash64(es, 2) == 0xe0e589718e2f4d2d);
  REQUIRE(hasher.hash64(jordi, 5) == 0xd538c02e96c7d4f);
  
}

TEST_CASE( "Hash some strings", "[Hasher]" ) {
  auto hasher = dori::utils::Hasher();

  REQUIRE(hasher.hash64("hola") == 0xad9daf762b0a1a35);
  REQUIRE(hasher.hash64("mi") == 0x413d2970f96e78a5);
  REQUIRE(hasher.hash64("nombre") == 0xbb3dc50d63cb3faf);
  REQUIRE(hasher.hash64("es") == 0xe0e589718e2f4d2d);
  REQUIRE(hasher.hash64("jordi") == 0xd538c02e96c7d4f);

}

TEST_CASE( "Checking default seed", "[Hasher]" ) {
  auto hasher = dori::utils::Hasher(42);
  auto defaultHasher = dori::utils::Hasher();
  auto anotherHasher = dori::utils::Hasher(355);

  REQUIRE(hasher.hash64("hola") == defaultHasher.hash64("hola"));
  REQUIRE(anotherHasher.hash64("hola") != defaultHasher.hash64("hola"));
}