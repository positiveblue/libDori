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


#include "stream/cardinality/DummyCounter.hpp"

namespace dori { namespace stream {
  DummyCounter::DummyCounter() {
    _counter = 0;
    _hasher = new dori::utils::DefaultHash();
  }

  bool DummyCounter::offer(const std::string &str) {
    ++_counter;

    bool modified = (_stringSet.find(str) == _stringSet.end());
    if (modified) {
      _stringSet.insert(str);
      std::uint64_t hashValue = (_hasher)->hash(str);
      _hashSet.insert(hashValue);
    }
    
    return modified;
  }

  bool DummyCounter::offerHash(std::uint64_t hashValue) {
    ++_counter;
    _hashSet.insert(hashValue);
  }

  std::uint64_t DummyCounter::cardinality() {
    return _stringSet.size();
  }

  std::uint64_t DummyCounter::elementsOffered() {
    return _counter;
  }

  DummyCounter::~DummyCounter() {
    delete _hasher;
  }

}  // namespace stream
}  // namespace dori
