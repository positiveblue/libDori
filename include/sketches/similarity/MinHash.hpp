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
#include <math.h>
#include<iostream>
#include "../../utils/hash/hash.hpp"

using dori::utils::Hasher;

namespace dori { namespace sketches {

template<typename T>
class MinHash {

  typedef std::vector<std::vector<uint64_t> > uint64Matrix_t;

 public:
  MinHash(std::uint64_t nFunctions_, std::uint64_t nBuckets_) : 
   _nFunctions(nFunctions_), _nBuckets(nBuckets_) {

    // Initialize hashFunctions
    std::mt19937 gen;

    _hashFunctions.resize(nFunctions_);
    
    for (auto &x : _hashFunctions) {
      x = Hasher{gen()};
    }

    this->_resizeMatrices();
  }

  MinHash(std::vector<std::uint64_t> seeds_, std::uint64_t nBuckets_) : 
    _nFunctions(seeds_.size()), _nBuckets(nBuckets_) {

    _hashFunctions.resize(_nFunctions);

    for (int i = 0; i < seeds_.size(); ++i) {
      _hashFunctions[i] = Hasher{seeds_[i]};
    }

    this->_resizeMatrices();
  }

  bool offer(const T &element) {
    for (auto i = 0; i < _nFunctions; ++i) {
      auto hash = _hashFunctions[i].hash64(element);
      _offer(element, i, hash);
    }
  }

  // Expose internals
  std::uint64_t size() const {
    return _size;
  }

  std::uint64_t nFunctions() const {
    return _nFunctions;
  }

  std::uint64_t nBuckets() const {
    return _nBuckets;
  }

  uint64Matrix_t minHashValues() const {
    return _minHashes;
  }

  void clear() {

  }

 private:

   void _resizeMatrices() {
    _size = _nFunctions*_nBuckets;

    _indexSize = log2(_nBuckets);

    // Resize _minHashes and _values matrices
    _minHashes.resize(_nFunctions);

    for (auto &x : _minHashes) {
      x.resize(_nBuckets, INT64_MAX);
    }
  }

  std::uint64_t _getIndex(std::uint64_t hash) {
    return hash >> (64 - (_indexSize));
  }

  std::uint64_t _getOffset(std::uint64_t hash) {
    return hash & (INT64_MAX >> (_indexSize));
  }

  bool _offer(const T &element, std::uint64_t function, std::uint64_t hash_) {
    auto bucket = _getIndex(hash_);
    auto x = _getOffset(hash_);

    if (x < _minHashes[function][bucket]) {
        _minHashes[function][bucket] = x;
      }
  }


  // How many hash functions
  std::uint64_t _nFunctions;
  std::uint64_t _nBuckets;
  std::uint64_t _indexSize;
  std::uint64_t _size;
  std::vector<Hasher> _hashFunctions;

  // TODO: Explain this
  uint64Matrix_t _minHashes;
};

}  // namespace sketches
}  // namespace dori

#endif //DORI_MINHASH_HPP
