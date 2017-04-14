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

#ifndef DORI_MINHASH_HPP
#define DORI_MINHASH_HPP

#include<map>
#include<vector>
#include<random>

#include "../../utils/hash/hash.hpp"

using dori::utils::Hasher;

namespace dori { namespace sketches {

template<typename T>
class MinHash {
 public:
  MinHash(std::uint64_t size_) : _size(size_) {
    std::mt19937 gen;

    _init = false;

    _hashFunctions.resize(size_);
    _minHashes.resize(size_);
    _values.resize(size_);

    for (auto &x : _hashFunctions) {
      x = Hasher{gen()};
    }
  }

  bool offer(const T &element) {
    for (auto i = 0; i < _size; ++i) {
      auto hash = _hashFunctions[i](element);
      offer(element, i, hash);
    }
  }

  bool offer(const T &element, std::uint64_t position_, std::uint64_t hash_) {
    if (!_init) {
      _init = true;
      _minHashes[position_] = hash_;
      _values[position_] = std::move(element);
    } else {
      if (hash_ < _minHashes[position_].first) {
        _minHashes[position_]= hash_;
        _values[position_] = std::move(element);
      }
    }  
  }

  std::uint64_t size() {
    return _size;
  }

  void clear() {}

  ~MinHash() {}

 private:
  bool _init;
  std::uint64_t _size;

  std::vector<Hasher> _hashFunctions;
  std::vector<std::uint64_t> _minHashes;
  std::vector<T> _values;
};

}  // namespace sketches
}  // namespace dori

#endif //DORI_MINHASH_HPP
