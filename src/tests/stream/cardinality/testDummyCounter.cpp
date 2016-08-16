//
// Created by jordi on 8/15/2016.
//

#ifndef LIBSTREAM_TESTDUMMYCOUNTER_HPP
#define LIBSTREAM_TESTDUMMYCOUNTER_HPP

#include "DummyCounter.hpp"

TEST_CASE( "DummyCounter can be created", "[DummyCounter]" ) {
    DummyCounter<int> iCounter();
    DummyCounter<char> cCounter();
    DummyCounter<std::string> sCounter();
}

TEST_CASE( "DummyCounter count how many elements", "[DummyCounter]" ) {
    DummyCounter<int> iCounter();
    DummyCounter<char> cCounter();
    DummyCounter<std::string> sCounter();
}

#endif //LIBSTREAM_TESTDUMMYCOUNTER_HPP
