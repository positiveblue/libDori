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

#include "utils/hash/DefaultHash.hpp"

namespace dori { namespace utils {
  DefaultHash::DefaultHash() {
    std::random_device rd;
    std::mt19937_64 gen(rd());

    std::uniform_int_distribution<unsigned long long> dis;

    this->seed = dis(gen);
  }

  DefaultHash::DefaultHash(std::uint64_t seed_) : seed(seed_) {}

  std::uint32_t DefaultHash::hash(const char *ptr, std::uint32_t size) {}

  std::uint32_t DefaultHash::hash(const std::string &str) {
    return (std::hash<std::string>{}(str) ^ this->seed);
  }

  std::uint64_t DefaultHash::hash64(const char *ptr, std::uint32_t size) {}

  std::uint64_t DefaultHash::hash64(const std::string &str) {
    return (std::hash<std::string>{}(str) ^ this->seed);
  }

  DefaultHash::~DefaultHash() {}

}  // namespace utils
}  // namespace dori