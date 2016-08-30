
#include <iostream>
#include <cstddef> /* size_t */
#include "../stream/cardinality/Cardinality.hpp"

int main() {
    ICardinality<std::string> *counter_ptr = new DummyCounter<std::string>();

    std::string s;
    while(std::cin >> s)
        counter_ptr->offer(s);

    std::cout << "All the stream procesed..." << std::endl;

    std::cout << counter_ptr->cardinality() << ' ' << counter_ptr->elementsOffered() << std::endl;

    return 0;
}