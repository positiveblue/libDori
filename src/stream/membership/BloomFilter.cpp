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

#include "stream/membership/BloomFilter.hpp"

namespace dori { namespace stream {

  BloomFilter::BloomFilter(std::uint64_t n_, double precision_) : nValues(n_),
    precision(precision_) {

    this->nBits = -n_*log(precision_) / pow(log(2),2);
    double hashFunc = this->nBits/precision_ * log(2);
    this->nHashFunctions = ceil(hashFunc);

    
  }

  bool BloomFilter::contains(const std::string &str) {}

  void BloomFilter::insert(const std::string &str) {}

  void BloomFilter::clear() {}

  std::uint64_t BloomFilter::getSize() {}

}  // namespace stream
}  // namespace dori
