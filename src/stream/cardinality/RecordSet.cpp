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

  RecordSet::RecordSet(std::uint64_t size_, bool isSampling_, bool isGrowing_) 
    : _size(size_), _isSampling(isSampling_), _isGrowing(isGrowing_), 
    _counter(0), _recordCounter(0) {
      _hasher = new dori::utils::DefaultHash();
  }

  bool RecordSet::modify(std::uint64_t hashValue) {

    if (_records.find(hashValue) == _records.end()) {
      if (_records.size() < _size) {
        _records.insert(hashValue);

        if (_records.size() == _size) {
          _breaker = _records.begin();
        }

        return true;
      } else if (*(_breaker) < hashValue) {
        
        _records.insert(hashValue);
        ++_size;
        ++_breaker;
        return true;
      } else if (*(_records.begin()) < hashValue) {
        _records.insert(hashValue);
        return true;
      }
    }

    return false;
  }

  bool RecordSet::offer(const std::string &str) {
    
    ++_counter;

    std::uint64_t hashValue = (_hasher)->hash64(str);
    
    bool modified = this->modify(hashValue); 

    if (modified) {
      ++_recordCounter;

      if (_isSampling) {
        _sample[hashValue] = str;
      }

      if (_records.size() > _size) {
        std::uint64_t smallestRecord = *(_records.begin());
        _records.erase(smallestRecord);
        _sample.erase(smallestRecord);
      }
    }

    return modified;
  }

  std::uint64_t RecordSet::size() {
    return _size;
  }

  std::uint64_t RecordSet::counter() {
    return _counter;
  }

  std::uint64_t RecordSet::recordCounter() {
    return _recordCounter;
  }

  std::set<std::uint64_t> RecordSet::records() {
    return std::set<std::uint64_t> (_records);
  }

  std::set<std::string> RecordSet::sample() {
    std::set<std::string> sample;

    for (auto it=_sample.begin(); it != _sample.end(); ++it) {
      sample.insert(it->second);
    }
    return sample;
  }

  dori::utils::IHasher* RecordSet::hasher() {
    return new dori::utils::DefaultHash {_hasher->seed()};
  }

  void RecordSet::hasher(dori::utils::IHasher* hasher_) {
    delete _hasher;
    _hasher = new dori::utils::DefaultHash {hasher_->seed()};
  }

  RecordSet::~RecordSet() {
    delete _hasher;
  }

}  // namespace stream
}  // namespace dori