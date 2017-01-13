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

#include "stream/cardinality/KMV.hpp"
#include <iostream>

namespace dori { namespace stream {

  KMV::KMV(std::uint64_t size_, bool isSampling_) {
    _recordSet = new dori::stream::RecordSet(size_, isSampling_);
  }

  bool KMV::offer(const std::string &str) {
    _recordSet->offer(str);
  }

  bool KMV::offerHash(std::uint64_t hashValue) {}

  std::uint64_t KMV::cardinality() {
    std::set<std::uint64_t> records = _recordSet->getRecords();

    double smallestRecord = *(records.begin());

    double distance = 0xFFFFFFFFFFFFFFFF - smallestRecord;

    double m = distance/records.size();

    return 0xFFFFFFFFFFFFFFFF/m;
  }

  std::uint64_t KMV::elementsOffered() {
    return _recordSet->getCounter();
  }

  KMV::~KMV() {
    delete _recordSet;
  }

}  // namespace stream
}  // namespace dori
