// The MIT License (MIT)
//
// Copyright (c) 2016 Jordi Montes Sanabria
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef LIBSTREAM_MURMURHASH_HPP
#define LIBSTREAM_MURMURHASH_HPP

#include <chrono>
#include <random>

#include "IHasher.hpp"

namespace ls { namespace utility {

class MurmurHash : public IHasher {
 public:
  MurmurHash() {
  // TODO(Jordi): Check if the random generator is well done for 32 and 64!
  unsigned int mt19937Seed =
    std::chrono::system_clock::now().time_since_epoch().count();

    // mt19937 is a standard mersenne_twister_engine
    std::mt19937 generator (mt19937Seed);

    seed32 = generator();
    seed64 = generator();

  }

  MurmurHash(std::uint32_t _seed) : seed32 (_seed) {}

  MurmurHash(std::uint64_t _seed) : seed64 (_seed) {}

  std::uint32_t hash(const char *ptr, std::uint32_t size) {
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m = 5;
    uint32_t n = 0xe6546b64;
    uint32_t h = 0;
    uint32_t k = 0;
    uint8_t *d = (uint8_t *) ptr; // 32 bit extract from `key'
    const uint32_t *chunks = NULL;
    const uint8_t *tail = NULL; // tail - last 8 bytes
    int i = 0;
    int l = size / 4; // chunk length

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
    switch (size & 3) { // `len % 4'
      case 3: k ^= (tail[2] << 16);
      case 2: k ^= (tail[1] << 8);

      case 1:
        k ^= tail[0];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        h ^= k;
    }

    h ^= size;

    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);

    return h;
  }

  std::uint64_t hash(const std::string &str);

  std::uint64_t hash64(const char *ptr, std::uint32_t size);

  std::uint64_t hash64(const std::string &str);

 private:
  std::uint32_t seed32;
  std::uint64_t seed64;
};

}  // namespace utility
}  // namespace ls

#endif //LIBSTREAM_MURMURHASH_HPP
