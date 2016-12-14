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


#include <math.h> 
#include "stream/cardinality/Recordinality.hpp"
#include "stream/cardinality/RecordSet.hpp"

namespace ls { namespace stream {

  Recordinality::Recordinality(std::uint64_t size_, bool isSampling_) {
    this->recordSet = new ls::stream::RecordSet(size_, isSampling_);
  }

  bool Recordinality::offer(const std::string &str) {
    this->recordSet->offer(str);
  }

  bool Recordinality::offerHash(std::uint64_t hashValue) {}

  std::uint64_t Recordinality::cardinality() {
    int k = this->recordSet->getSize();
    int rk = this->recordSet->getRecordCounter();

    double base = 1.0 + 1.0/k;
    double exp = rk - k + 1;

    double res = k * pow(base, exp) - 1;

    return res;
  }

  std::uint64_t Recordinality::elementsOffered() {
    return this->recordSet->getCounter();
  }

  Recordinality::~Recordinality() {
    delete this->recordSet;
  }

}  // namespace stream
}  // namespace ls
