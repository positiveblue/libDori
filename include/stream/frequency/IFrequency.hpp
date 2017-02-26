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


#ifndef DORI_IFREQUENCY_HPP
#define DORI_IFREQUENCY_HPP

#include <cstdint>
#include <string>
#include <map>

namespace dori { namespace stream {

class IFrequency {
 public:
  virtual bool offer(const std::string &str, std::uint64_t count) = 0;

  virtual std::uint64_t estimateCounter(const std::string &str) = 0;

  virtual std::map<std::string, std::uint64_t> topK() = 0;

  virtual std::uint64_t elementsOffered() = 0;

  virtual std::uint64_t size() = 0;

};

}  // namespace stream
}  // namespace dori

#endif  // DORI_IFREQUENCY_HPP
