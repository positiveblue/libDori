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


#include "stream/cardinality/RecordSet.hpp"

namespace ls { namespace stream {

  RecordSet::RecordSet(std::uint64_t size_, bool isGrowing_, bool isSampling_)
    : size(size), isGrowing(isGrowing_), isSampling(isSampling_) {}

  bool RecordSet::offer(const std::string &str) {
    bool modified = false;
    ++this->counter;
    std::uint64_t hashValue = (this->hasher)->hash64(str);

    if (this->records.find(hashValue) == this->records.begin()) {
      if ((this->records.size() < (this->size)) ||
         (*(this->records.begin()) < hashValue)) {
        
        modified = true;
        ++this->recordCounter;

        this->records.insert(hashValue);

        if (this->isSampling) {
            this->sample[hashValue] = str;
        }

        if (this->records.size() > this->size) {
          this->records.erase(hashValue);
          this->sample.erase(hashValue);
        }
      }
    }
    return modified;
  }

  std::uint64_t RecordSet::getSize() {
    return this->size;
  }

  std::uint64_t RecordSet::getCounter() {
    return this->counter;
  }

  std::uint64_t RecordSet::getRecordCounter() {
    return this->recordCounter;
  }

  std::set<std::string> RecordSet::getSample() {
    std::set<std::string> sample;

    for (auto it=this->sample.begin(); it != this->sample.end(); ++it) {
      sample.insert(it->second);
    }
    return sample;
  }

}  // namespace stream
}  // namespace ls