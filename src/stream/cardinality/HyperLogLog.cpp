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

#include <iostream>
#include "stream/cardinality/HyperLogLog.hpp"

namespace dori { namespace stream {
  HyperLogLog::HyperLogLog(std::uint64_t size_) : _size(size_) {
    _registerSet = new dori::stream::RegisterSet(size_);
    _hasher = new dori::utils::DefaultHash();

    this->setAlpha(size_);
  }

  bool HyperLogLog::offer(const std::string &str) {
    std::uint64_t hashValue = (_hasher)->hash64(str);
    this->offerHash(hashValue);
  }

  bool HyperLogLog::offerHash(std::uint64_t hashValue) {
    _registerSet->offer(hashValue);
  }

  std::uint64_t HyperLogLog::cardinality() {
    double numerator = (_alpha) * (_size) * (_size);
    double denominator = 0;

    for (int i = 0; i < _size; ++i) {
      denominator+= (1.0/pow(2, ((_registerSet)->getPosition(i))));
    }
    
    double estimation = numerator/denominator;

    // Correcting bias
    if (estimation <= (5/2*(_size))) {
      std::uint64_t numberOfZeros = _registerSet->getZerosCounter();
      estimation = _size * log(_size/numberOfZeros);
    } else if (estimation > 1.0/30*log(1-estimation/pow(2,32))) {
      estimation = -pow(2,32)*log2(1-estimation/pow(2,32));
    }
    
    return (1.0/_alpha) * estimation;
  }

  std::uint64_t HyperLogLog::elementsOffered() {
    return (_registerSet)->getCounter();
  }

  void HyperLogLog::setAlpha(std::uint64_t size) {
    switch (size) {
      case 16: (_alpha) = 0.673;
               break;
      case 32: (_alpha) = 0.697;
               break;
      case 64: (_alpha) = 0.709;
               break;
      default: (_alpha) = (0.7213 / (1.0 + 1.079/size));
    }
  }

  HyperLogLog::~HyperLogLog() {
    delete _registerSet;
    delete _hasher;
  }

}  // namespace stream
}  // namespace dori