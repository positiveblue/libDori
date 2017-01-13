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

#include "utils/hash/MurmurHash.hpp"

namespace dori { namespace utils {

  MurmurHash::MurmurHash() {

    // mt19937 is a standard mersenne_twister_engine
    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<unsigned long long> dis;

    this->_seed = dis(gen);
  }

  MurmurHash::MurmurHash(std::uint64_t seed_) {
    this->_seed = seed_;
  }

  std::uint32_t MurmurHash::hash(const char *ptr, std::uint32_t size) {
    std::uint32_t c1 = 0xcc9e2d51;
    std::uint32_t c2 = 0x1b873593;
    std::uint32_t r1 = 15;
    std::uint32_t r2 = 13;
    std::uint32_t m = 5;
    std::uint32_t n = 0xe6546b64;
    std::uint32_t h = 0;
    std::uint32_t k = 0;
    std::uint8_t *d = (uint8_t *) ptr; // 32 bit extract from `key'
    const std::uint32_t *chunks = NULL;
    const std::uint8_t *tail = NULL; // tail - last 8 bytes
    int i = 0;
    int l = size / 4; // chunk length

    h = this->_seed;

    chunks = (const std::uint32_t *) (d + l * 4); // body
    tail = (const std::uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

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

  std::uint32_t MurmurHash::hash(const std::string &str) {
    return hash(str.data(), str.size());
  }

  std::uint64_t MurmurHash::hash64(const char *ptr, std::uint32_t size) {
    return hash(ptr, size);
  }

  std::uint64_t MurmurHash::hash64(const std::string &str) {
    return hash(str.data(), str.size());
  }

  std::uint64_t  MurmurHash::seed() {
    return this->_seed;
  }

  void  MurmurHash::seed(std::uint64_t seed_) {
    this->_seed = seed_;
  }

}  // namespace utils
}  // namespace dori
