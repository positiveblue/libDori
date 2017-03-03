message(STATUS "Building with ${CMAKE_CXX_COMPILER_ID} compiler")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

    set (CXX14_COMPILER_FLAGS "-std=c++14")

    set (COMPILER_SPEC_FLAGS "-w"
        # "-W -Wall -Wno-return-type -Wno-write-strings -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-unused-local-typedef"
    )

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

    set (CXX14_COMPILER_FLAGS "-std=c++14")

    set (COMPILER_SPEC_FLAGS "-w"
        # "-W -Wall -Wno-return-type -Wno-write-strings -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-unused-local-typedef"
    )

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    set (CXX14_COMPILER_FLAGS "-std=c++1y")
    set (COMPILER_SPEC_FLAGS "-w"
        # "-W -Wall -Wno-return-type -Wno-write-strings -Wno-strict-aliasing -Wno-format -Wno-deprecated -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-unused-local-typedefs"
    )

else()

    message (FATAL " Unsupported compiler!")

endif()

message (STATUS "CXX11_COMPILER_FLAGS=${CXX14_COMPILER_FLAGS}")
set (CMAKE_CXX_FLAGS "${CXX14_COMPILER_FLAGS} ${COMPILER_SPEC_FLAGS}")

message (STATUS "Building on ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR} on $ENV{HOSTNAME}")