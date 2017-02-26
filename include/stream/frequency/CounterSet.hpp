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

#ifndef DORI_COUNTER_SET_HPP
#define DORI_COUNTER_SET_HPP


#include <cstdint>
#include <vector>
#include <string>

#include "../../utils/hash/hash.hpp"

namespace dori { namespace stream {

class CounterSet {
 public:
  CounterSet(std::uint64_t w_, std::uint64_t d_);

  std::uint64_t get(std::uint64_t i, std::uint64_t j);
  void update(std::uint64_t i, std::uint64_t j, std::uint64_t value);

  std::uint64_t w();
  std::uint64_t d();
  std::uint64_t size();

  ~CounterSet();

 private:

  std::uint64_t _w;
  std::uint64_t _d;
  std::uint64_t _size;

  std::vector<std::vector<std::uint64_t> > _M;

};

}  // namespace stream
}  // namespace dori

#endif //DORI_COUNTER_SET_HPP
