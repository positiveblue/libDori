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


#ifndef DORI_REGISTER_SET_HPP
#define DORI_REGISTER_SET_HPP

#include <cstdint>
#include <vector>
#include <math.h>         /* pow, log2 */

namespace dori { namespace stream {

class RegisterSet {
 public:
  RegisterSet(std::uint64_t size_);

  bool offer(std::uint64_t bits);



 private:

  std::uint64_t getIndex(std::uint64_t bits);
  std::uint64_t getOffset(std::uint64_t bits);

  std::uint64_t scan1(std::uint64_t bits);

  std::uint64_t size; // Num of registers (is 2**indexSize)
  std::uint64_t indexSize;
  std::uint64_t counter;
  std::vector<std::uint64_t> M;
};

}  // namespace stream
}  // namespace dori

#endif //DORI_REGISTER_SET_HPP
