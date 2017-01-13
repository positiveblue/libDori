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


#include "stream/cardinality/RegisterSet.hpp"

namespace dori { namespace stream {

  RegisterSet::RegisterSet(std::uint64_t size_) {
    _size = size_;
    _M = std::vector<std::uint64_t> (size_, 0);
    _counter = 0;
    _indexSize = log2(size_);
  }

  bool RegisterSet::offer(std::uint64_t bits) {
    ++(_counter);
    bool modified = false;

    std::uint64_t position = this->index(bits);
    std::uint64_t value =  this->scan1(bits);

    if (_M[position] < value) {
        _M[position] = value;
        modified = true;
    }
    return modified;
  }

  std::uint64_t RegisterSet::counter() {
    return _counter;
  }

  std::uint64_t RegisterSet::zerosCounter() {
    std::uint64_t counter = 0;

    for (auto registerValue : _M) {
      if (registerValue == 0) {
        ++counter;
      }
    }

    return counter;
  }

  std::uint64_t RegisterSet::position(std::uint64_t pos) {
    return _M[pos];
  }

  std::uint64_t RegisterSet::index(std::uint64_t bits) {
    return bits >> (64 - (_indexSize));
  }

  std::uint64_t RegisterSet::offset(std::uint64_t bits) {
    return bits & (0xFFFFFFFFFFFFFFFF >> (_indexSize));
  }

  std::uint64_t RegisterSet::scan1(std::uint64_t bits) {
    return (64 - _indexSize - log2(this->offset(bits)));
  }

}  // namespace stream
}  // namespace dori
