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

#include "stream/cardinality/IKMV.hpp"
#include <iostream>

namespace dori { namespace stream {

  IKMV::IKMV(std::uint64_t size_, bool isSampling_) {
    this->recordSet = new dori::stream::RecordSet(size_, isSampling_);
  }

  bool IKMV::offer(const std::string &str) {
    this->recordSet->offer(str);
  }

  bool IKMV::offerHash(std::uint64_t hashValue) {}

  std::uint64_t IKMV::cardinality() {
    std::set<std::uint64_t> records = this->recordSet->getRecords();

    double smallestRecord = *(records.begin());

    double normal_m = (0xFFFFFFFFFFFFFFFF - smallestRecord)/records.size();


    std::vector<std::uint64_t> distances;

    auto fst = records.begin();
    auto snd = records.begin();
    ++snd;

    while(snd != records.end()) {
      distances.push_back((*snd) - (*fst));
      ++fst;
      ++snd;
    }

    distances.push_back(0xFFFFFFFFFFFFFFFF - *fst);

    std::sort(distances.begin(), distances.end());


    std::vector<std::uint64_t> clean_distances;

    for (std::uint64_t i = 0; i < distances.size(); ++i) {
      if ( (distances[i] > (0.9*normal_m)) and
           (distances[i] < (1.1*normal_m)) ) {
        clean_distances.push_back(distances[i]);
      }
    }

    double sum = 0;
    for (auto x : clean_distances) {
      sum+=x;
    }
    
    double m;

    double median_m = (sum/clean_distances.size());

    if(median_m < normal_m*2) {
      m = (median_m + normal_m)/2;
    } else {
      m = normal_m;
    }

    return 0xFFFFFFFFFFFFFFFF/m;
  }

  std::uint64_t IKMV::elementsOffered() {
    return this->recordSet->getCounter();
  }

  IKMV::~IKMV() {
    delete this->recordSet;
  }

}  // namespace stream
}  // namespace dori
