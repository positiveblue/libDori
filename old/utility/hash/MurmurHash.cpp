#include "IHasher.hpp"

namespace ls { namespace utility {

MurmurHash::MurmurHash() {
  // TODO(Jordi): Check if the random generator is well done for 32 and 64!
  unsigned int mt19937Seed =
    std::chrono::system_clock::now().time_since_epoch().count();

  // mt19937 is a standard mersenne_twister_engine
  std::mt19937 generator (mt19937Seed);
  
  seed32 = generator();
  seed64 = generator();
  
}

MurmurHash::MurmurHash(std::uint32_t _seed) : seed32 (_seed) {}

MurmurHash::MurmurHash(std::uint64_t _seed) : seed64 (_seed) {}

std::uint32_t MurmurHash::hash(const char *ptr, std::uint32_t size) {
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  uint32_t r1 = 15;
  uint32_t r2 = 13;
  uint32_t m = 5;
  uint32_t n = 0xe6546b64;
  uint32_t h = 0;
  uint32_t k = 0;
  uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
  const uint32_t *chunks = NULL;
  const uint8_t *tail = NULL; // tail - last 8 bytes
  int i = 0;
  int l = len / 4; // chunk length

  h = seed32;

  chunks = (const uint32_t *) (d + l * 4); // body
  tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

  // for each 4 byte chunk of `key'
  for (i = -l; i != 0; ++i) {
    // next 4 byte chunk of `key'
    k = chunks[i];

    // encode next 4 byte chunk of `key'
    k *= c1;
    k = (k << r1) | (k >> (32 - r1));
    k *= c2;

    // append to hash
    h ^= k;
    h = (h << r2) | (h >> (32 - r2));
    h = h * m + n;
  }

  k = 0;

  // remainder
  switch (len & 3) { // `len % 4'
    case 3: k ^= (tail[2] << 16);
    case 2: k ^= (tail[1] << 8);

    case 1:
      k ^= tail[0];
      k *= c1;
      k = (k << r1) | (k >> (32 - r1));
      k *= c2;
      h ^= k;
  }

  h ^= len;

  h ^= (h >> 16);
  h *= 0x85ebca6b;
  h ^= (h >> 13);
  h *= 0xc2b2ae35;
  h ^= (h >> 16);

  return h;
}

std::uint64_t MurmurHash::hash(const std::string &str) {}

std::uint64_t MurmurHash::hash64(const char *ptr, std::size_t length) {}

std::uint64_t MurmurHash::hash64(const std::string &str) {}
};

}  // namespace utility
}  // namespace ls