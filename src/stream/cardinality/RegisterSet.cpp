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
  this->size = size_;
  this->M = std::vector<std::uint64_t> (size_, 0);
  this->counter = 0;
  this->indexSize = log2(size_);
}

bool RegisterSet::offer(std::uint64_t bits) {
  ++(this->counter);
  bool modified = false;

  std::uint64_t position = getIndex(bits);
  std::uint64_t value =  scan1(bits);

  if (this->M[position] < value) {
      M[position] = value;
      modified = true;
  }
  return modified;
}

std::uint64_t RegisterSet::getIndex(std::uint64_t bits) {
  return bits >> (64 - (this->indexSize));
}

std::uint64_t RegisterSet::getOffset(std::uint64_t bits) {
  return bits & (0xFFFFFFFFFFFFFFFF >> (this->indexSize));
}

std::uint64_t RegisterSet::scan1(std::uint64_t bits) {
  return (64 - this->indexSize - log2(getOffset(bits)));
}

}  // namespace stream
}  // namespace dori
