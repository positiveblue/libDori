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


#ifndef DORI_DUMMY_FREQUENCY_HPP
#define DORI_DUMMY_FREQUENCY_HPP

#include <cstdint>
#include <string>
#include <map>
#include "./IFrequency.hpp"
#include "../../utils/hash/hash.hpp"

namespace dori { namespace stream {

class DummyFrequency : public IFrequency {
 public:
  DummyFrequency();

  bool offer(const std::string &str, std::uint64_t count=1);

  std::uint64_t estimateCounter(const std::string &str);

  std::map<std::string, std::uint64_t> topK();

  std::uint64_t elementsOffered();

  std::uint64_t size();

  ~DummyFrequency();

 private:
  std::map<std::string, std::uint64_t> _frequencyCounter;
  std::uint64_t _counter;
};

}  // namespace stream
}  // namespace dori

#endif  // DORI_DUMMY_FREQUENCY_HPP
