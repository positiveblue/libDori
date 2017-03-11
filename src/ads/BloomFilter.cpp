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

#include "ads/BloomFilter.hpp"
#include <iostream>


namespace dori { namespace stream {

  BloomFilter::BloomFilter(std::uint64_t n_, double precision_) : nValues(n_),
    precision(precision_) {


    this->nBits = ceil((n_ * log(precision_)) / log(1.0 / (pow(2.0, log(2.0)))));

    double hashFunc = round(log(2.0) * (this->nBits / (double)n_));
    
    this->bitSet = new dori::stream::BitSet(this->nBits);
    
    
    this->nHashFunctions = ceil(hashFunc);
    this->hashFunctions = 
      new std::vector<dori::utils::Hasher*> (this->nHashFunctions);

    for (int i = 0; i < this->nHashFunctions; ++i) {
      this->hashFunctions->at(i) = new dori::utils::Hasher(); 
    }
    
  }

  bool BloomFilter::contains(const std::string &str) {
    for (int i = 0; i < this->nHashFunctions; ++i) {
      std::uint64_t hashValue = (this->hashFunctions->at(i))->hash64(str);
      std::uint64_t position = hashValue % this->nBits;
      if (not (this->bitSet->getValue(position))) {
        return false;
      }
    }

    return true;
  }

  void BloomFilter::insert(const std::string &str) {
    for (int i = 0; i < this->nHashFunctions; ++i) {
      std::uint64_t hashValue = (this->hashFunctions->at(i))->hash64(str);
      std::uint64_t position = hashValue % this->nBits;
      this->bitSet->setOne(position);
    }
  }

  void BloomFilter::clear() {
    this->bitSet->clear();
  }

  std::uint64_t BloomFilter::size() {
    return this->nBits;
  }

  BloomFilter::~BloomFilter() {
    delete this->bitSet;

    for (int i = 0; i < this->nHashFunctions; ++i) {
      delete this->hashFunctions->at(i); 
    }
    
    delete this->hashFunctions;
  
  }

}  // namespace stream
}  // namespace dori
