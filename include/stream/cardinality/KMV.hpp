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


#ifndef LIBSTREAM_KMV_HPP
#define LIBSTREAM_KMV_HPP

#include <cstdint>
#include <string>
#include <set>
#include "./ICardinality.hpp"
#include "./RecordSet.hpp"


namespace ls { namespace stream {

class KMV : public ICardinality {
 public:
  KMV(std::uint64_t size, bool isSampling_=false);

  bool offer(const std::string &str);

  bool offerHash(std::uint64_t hashValue);

  std::uint64_t cardinality();

  std::uint64_t elementsOffered();

  ~KMV();

 private:
  RecordSet* recordSet;

};

}  // namespace stream
}  // namespace ls

#endif  // LIBSTREAM_KMV_HPP
