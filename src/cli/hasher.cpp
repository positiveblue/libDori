//
// Created by Jordi Sanabria on 8/22/16.
//


#include <iostream>
#include <cstddef> /* size_t */
#include "../hash/Hasher.hpp"

int main() {
    IHasher<std::string> *hasher_ptr = new MurmurHash<std::string> (-1);

    std::string s;
    while(std::cin >> s) {
        std::cout << hasher_ptr->hash(s) << std::endl;
    }




    //std::cout << counter_ptr->cardinality() << ' ' << counter_ptr->elementsOffered() << std::endl;

    return 0;
}