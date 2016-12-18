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

#include "stream/membership/BitSet.hpp"

namespace dori { namespace stream {
  BitSet::BitSet(std::uint64_t size_) : _size(size_) {
    double vectorPositions = ceil(size_/8);
    this->bitSet = new std::vector<char>(vectorPositions, 0);
  }

  bool BitSet::getValue(std::uint64_t position) {
    std::uint64_t bucket = floor(position/8.0);
    char bucketPosition = position - bucket*8;
    
    return ((this->bitSet->at(bucket)) & (mask(bucketPosition)));
  }

  void BitSet::flip(std::uint64_t position) {
    std::uint64_t bucket = floor(position/8.0);
    char bucketPosition = position - bucket*8;

    this->bitSet->at(bucket) = this->bitSet->at(bucket)^(mask(bucketPosition));
  }

  void BitSet::setOne(std::uint64_t position) {
    std::uint64_t bucket = floor(position/8.0);
    char bucketPosition = position - bucket*8;

    this->bitSet->at(bucket) = this->bitSet->at(bucket) | (mask(bucketPosition));
  }

  void BitSet::clear() {
    std::fill(this->bitSet->begin(), this->bitSet->end(), 0);
  }

  std::uint64_t BitSet::size() {
    return this->_size;
  }

  BitSet::~BitSet() {
    delete this->bitSet;
  }

  char BitSet::mask(char position) {
    return 1 << position;
  }

}  // namespace stream
}  // namespace dori
