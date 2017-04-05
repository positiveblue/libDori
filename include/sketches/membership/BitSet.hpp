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

#ifndef DORI_BIT_SET_HPP
#define DORI_BIT_SET_HPP

#include <cstdint>
#include <math.h> 
#include <vector>

namespace dori { namespace stream {

class BitSet {
 public:
  BitSet(std::uint64_t size_);

  bool value(std::uint64_t position_);

  void setZero(std::uint64_t position_);

  void setOne(std::uint64_t position_);

  void flip(std::uint64_t position_);

  std::uint64_t size();

  void clear();

  ~BitSet();

 private:
    char mask(char position);

    std::uint64_t _size;
    std::vector<char> _bitSet; 
};

}  // namespace stream
}  // namespace dori

#endif //DORI_BLOOM_FILTER_HPP