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

#include "stream/frequency/DummyFrequency.hpp"

namespace dori { namespace stream {

  DummyFrequency::DummyFrequency() {}

  bool DummyFrequency::offer(const std::string &str, std::uint64_t count) {
    _counter+=count;
    _frequencyCounter[str]+=count;
  }

  std::uint64_t DummyFrequency::estimateCounter(const std::string &str) {
    return _frequencyCounter[str];
  }

  std::map<std::string, std::uint64_t> DummyFrequency::topK() {
    return _frequencyCounter;
  }

  std::uint64_t DummyFrequency::elementsOffered() {
    return _counter;
  }

  std::uint64_t DummyFrequency::size() {
    return _frequencyCounter.size();
  }

  DummyFrequency::~DummyFrequency() {}

}  // namespace stream
}  // namespace dori
