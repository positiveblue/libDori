// The MIT License (MIT)
//
// Copyright (c) 2017 Jordi Montes Sanabria
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

#include "utils/hash/Hasher.hpp"

namespace dori { namespace utils {

  Hasher::Hasher() {
    _seed = 42;
  }

  Hasher::Hasher(std::uint64_t seed) : _seed(seed) {}

  std::uint64_t Hasher::hash64(const char *ptr, std::uint32_t length) {
    char output[16];
    MurmurHash3_x64_128(ptr, length, _seed, output);
    // We are taking only the first 64 bits
    return *((uint64_t *)output);
  }

  std::uint64_t Hasher::hash64(const std::string &str) {
    return hash64(str.c_str(), str.size());
  }

  std::uint64_t Hasher::seed() {
    return _seed;
  }

  void Hasher::seed(std::uint64_t seed) {
    _seed = seed;
  }

}  // namespace utils
}  // namespace dori
