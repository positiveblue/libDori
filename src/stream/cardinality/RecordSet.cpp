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

namespace dori { namespace stream {

  RecordSet::RecordSet(std::uint64_t size_, bool isSampling_) : _size(size_), 
    _isSampling(isSampling_), _counter(0), _recordCounter(0) {
      this->_hasher = new dori::utils::DefaultHash();
    }

  bool RecordSet::offer(const std::string &str) {
    bool modified = false;
    ++this->_counter;
    std::uint64_t hashValue = (this->_hasher)->hash64(str);

    if (this->_records.find(hashValue) == this->_records.end()) {
      if ((this->_records.size() < (this->_size)) ||
         (*(this->_records.begin()) < hashValue)) {
        
        modified = true;
        ++this->_recordCounter;

        this->_records.insert(hashValue);

        if (this->_isSampling) {
            this->_sample[hashValue] = str;
        }

        if (this->_records.size() > this->_size) {
          std::uint64_t smallestRecord = *(this->_records.begin());
          this->_records.erase(smallestRecord);
          this->_sample.erase(smallestRecord);
        }
      }
    }
    return modified;
  }

  std::uint64_t RecordSet::getSize() {
    return this->_size;
  }

  std::uint64_t RecordSet::getCounter() {
    return this->_counter;
  }

  std::uint64_t RecordSet::getRecordCounter() {
    return this->_recordCounter;
  }

  std::set<std::uint64_t> RecordSet::getRecords() {
    return std::set<std::uint64_t> (this->_records);
  }

  std::set<std::string> RecordSet::getSample() {
    std::set<std::string> sample;

    for (auto it=this->_sample.begin(); it != this->_sample.end(); ++it) {
      sample.insert(it->second);
    }
    return sample;
  }

  dori::utils::IHasher* RecordSet::hasher() {
    return new dori::utils::DefaultHash {this->_hasher->seed()};
  }

  void RecordSet::hasher(dori::utils::IHasher* hasher_) {
    delete this->_hasher;
    this->_hasher = new dori::utils::DefaultHash {hasher_->seed()};
  }

  RecordSet::~RecordSet() {
    delete this->_hasher;
  }

}  // namespace stream
}  // namespace dori