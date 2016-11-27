//
// Created by jordi on 8/15/2016.
//

#include "catch.hpp"
#include "LogLog.hpp"


TEST_CASE( "LogLog can be created", "[LogLog]" ) {

    LogLog<std::string> counter(7);
    SECTION( "" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
}