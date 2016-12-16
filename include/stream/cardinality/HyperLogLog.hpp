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


#ifndef DORI_HYPERLOGLOG_HPP
#define DORI_HYPERLOGLOG_HPP


#include <cstdint>
#include <math.h> 
#include <string>
#include "./ICardinality.hpp"
#include "./RegisterSet.hpp"
#include "../../utils/hash/hash.hpp"


namespace dori { namespace stream {

class HyperLogLog : public ICardinality {
 public:
  HyperLogLog(std::uint64_t size_);
  
  bool offer(const std::string &str);

  bool offerHash(std::uint64_t hashValue);

  std::uint64_t cardinality();

  std::uint64_t elementsOffered();

  ~HyperLogLog();

 private:
  void setAlpha(std::uint64_t size);

  dori::utils::IHasher* hasher;
  dori::stream::RegisterSet* registerSet;

  std::uint64_t size;
  double alpha;

};

}  // namespace stream
}  // namespace dori

#endif  // DORI_HYPERLOGLOG_HPP
