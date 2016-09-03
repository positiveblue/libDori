//
// Created by Jordi Sanabria on 9/2/16.
//

#ifndef LIBSTREAM_HASH_UTILS_HPP
#define LIBSTREAM_HASH_UTILS_HPP

#include<stdlib.h>
#include<time.h>

std::uint64_t uint64RandomNumber() {

    std::uint64_t  randomNumber;

    srand (time(NULL));

    randomNumber  = (std::uint64_t) rand();
    randomNumber |= (std::uint64_t) rand() << 15;
    randomNumber |= (std::uint64_t) rand() << 30;
    randomNumber |= (std::uint64_t) rand() << 45;
    randomNumber |= (std::uint64_t) rand() << 60;

    return randomNumber;
}

#endif //LIBSTREAM_HASH_UTILS_HPP