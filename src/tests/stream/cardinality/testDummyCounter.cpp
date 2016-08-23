//
// Created by jordi on 8/15/2016.
//

#ifndef LIBSTREAM_TESTDUMMYCOUNTER_HPP
#define LIBSTREAM_TESTDUMMYCOUNTER_HPP

#include <iostream>
#include <fstream>
#include "../../../stream/cardinality/DummyCounter.hpp"

std::string DATA_FILE_4096 = "../datasets/test_4096_16384.txt";

int consume(std::string fname, ICardinality<std::string> *Counter) {
    std::string line;
    std::ifstream _file (fname);
    int n;
    if (_file.is_open()) {
        //Remove the first line (n and m values)
        //using line like a trash
        _file >> line >> n >> line >> line >> line;
        getline(_file,line);
        while ( getline(_file,line) )
        {
            Counter->offer(line);
        }
        _file.close();
    } else {
        CHECK(false);
    }
    return n;
}



TEST_CASE( "DummyCounter can be created", "[DummyCounter]" ) {
    DummyCounter<int> iCounter;
    DummyCounter<char> cCounter;
    DummyCounter<std::string> sCounter;
}

TEST_CASE( "DummyCounter estimate cardinality", "[DummyCounter]" ) {
    DummyCounter<std::string> sCounter;
    int rcardinality = consume(DATA_FILE_4096, &sCounter);
    std::cout << "n: " << rcardinality << std::endl;
    std::cout << "approx: " << sCounter.cardinality() << std::endl;
    CHECK( rcardinality == sCounter.cardinality());
}

#endif //LIBSTREAM_TESTDUMMYCOUNTER_HPP
