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


#ifndef LIBSTREAM_DEFAULT_HASH_HPP
#define LIBSTREAM_DEFAULT_HASH_HPP

#include <cstdint>
#include <random>
#include <string>
#include <unordered_set>

#include "IHasher.hpp"

namespace ls { namespace utils {

class DefaultHash : public IHasher {
 public:
  DefaultHash();

  DefaultHash(std::uint64_t seed_);

  std::uint32_t hash(const char *ptr, std::uint32_t size);

  std::uint32_t hash(const std::string &str);

  std::uint64_t hash64(const char *ptr, std::uint32_t size);

  std::uint64_t hash64(const std::string &str);

  ~DefaultHash();

private:
  std::hash<std::string> hasher;

  std::uint64_t seed;
};

}  // namespace utils
}  // namespace ls

#endif  // LIBSTREAM_DEFAULT_HASH_HPP

