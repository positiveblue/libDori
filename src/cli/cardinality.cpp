
#include <iostream>
#include "../stream/cardinality/Cardinality.hpp"

int main() {
    ICardinality<std::string> *counter_ptr = new LogLog<std::string>();

    std::string s;
    while(std::cin >> s)
        counter_ptr->offer(s);

    std::cout << counter_ptr->cardinality() << ' ' << counter_ptr->elementsOffered() << std::endl;

    return 0;
}