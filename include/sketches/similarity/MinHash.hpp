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
#include<cstdint>
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
    _minHashes.resize(size_, INT64_MAX);
    _values.resize(size_);

    for (auto &x : _hashFunctions) {
      x = Hasher{gen()};
    }
  }

  MinHash(std::vector<std::uint64_t> seeds_) : _size(seeds_.size()) {
    _init = false;

    _hashFunctions.resize(seeds_.size());
    _minHashes.resize(seeds_.size(), INT64_MAX);
    _values.resize(seeds_.size());

    for (int i = 0; i < seeds_.size(); ++i) {
      _hashFunctions[i] = Hasher{seeds_[i]};
    }
  }

  bool offer(const T &element) {
    for (auto i = 0; i < _size; ++i) {
      auto hash = _hashFunctions[i].hash64(element);
      offer(element, i, hash);
    }
    _init=true;
  }


  bool initialized() const {
    return _init;
  }

  std::uint64_t size() const {
    return _size;
  }

  std::vector<std::uint64_t> hashValues() const {
    return _minHashes;
  }

  double compare(const MinHash<T> &mh ) const {    
    if (mh.size() != _size || !mh.initialized() || !this->initialized())
      return 0.0;
    
    auto mhValues = mh.hashValues();
    int common = 0;

    for (int i = 0; i < _size; ++i)
      if (mhValues[i] == _minHashes[i])
        ++common;

    int total = (_size << 1) - common;
    return ((double)common)/total;
  }

  void clear() {}

  ~MinHash() {}

 private:
  bool offer(const T &element, std::uint64_t position_, std::uint64_t hash_) {
    if (!_init) {
      _minHashes[position_] = hash_;
      _values[position_] = std::move(element);
    } else {
      if (hash_ < _minHashes[position_]) {
        _minHashes[position_]= hash_;
        _values[position_] = std::move(element);
      }
    }  
  }

  // Have we processed some element or not
  bool _init;

  // How many hash functions
  std::uint64_t _size;
  std::vector<Hasher> _hashFunctions;

  // hash(_values[i]) == _minHashes[i]
  std::vector<std::uint64_t> _minHashes;
  std::vector<T> _values;
};

}  // namespace sketches
}  // namespace dori

#endif //DORI_MINHASH_HPP
