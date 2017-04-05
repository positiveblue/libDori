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

#include "sketches/membership/BitSet.hpp"

namespace dori { namespace sketches {
  BitSet::BitSet(std::uint64_t size_) : _size(size_) {
    _bitSet.resize(ceil(size_/8.0), 0);
  }

  bool BitSet::value(std::uint64_t position_) {
    std::uint64_t bucket = floor(position_/8.0);
    char bucketPosition = position_ - bucket*8;
    
    return (_bitSet[bucket]) & (mask(bucketPosition));
  }

  void BitSet::setZero(std::uint64_t position_) {
    if (value(position_))
      flip(position_);
  }

  void BitSet::setOne(std::uint64_t position_) {
    std::uint64_t bucket = floor(position_/8.0);
    char bucketPosition = position_ - bucket*8;

    _bitSet[bucket] |= (mask(bucketPosition));
  }

  void BitSet::flip(std::uint64_t position_) {
    std::uint64_t bucket = floor(position_/8.0);
    char bucketPosition = position_ - bucket*8;

    _bitSet[bucket] ^= (mask(bucketPosition));
  }

  void BitSet::clear() {
    std::fill(_bitSet.begin(), _bitSet.end(), 0);
  }

  std::uint64_t BitSet::size() {
    return _size;
  }

  BitSet::~BitSet() {}

  char BitSet::mask(char position) {
    return 1 << position;
  }

}  // namespace sketches
}  // namespace dori