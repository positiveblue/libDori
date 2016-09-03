
#include <iostream>
#include <cstddef> /* size_t */
#include "../stream/cardinality/Cardinality.hpp"

int main() {
    ICardinality<std::string> *counter_ptr = new DummyCounter<std::string>();
    ICardinality<std::string> *LogLog_ptr = new LogLog<std::string>(7);
    std::string s;

    while(std::cin >> s) {
        counter_ptr->offer(s);
        LogLog_ptr->offer(s);
    }


    std::cout << "DummyCounter: " << counter_ptr->cardinality() << ' ' << counter_ptr->elementsOffered() \
        << ' ' << counter_ptr->cardinality()/counter_ptr->cardinality() << std::endl;
    std::cout << "LogLog: " << LogLog_ptr->cardinality() << ' ' << LogLog_ptr->elementsOffered() \
        << ' ' << counter_ptr->cardinality()/(double)LogLog_ptr->cardinality() << std::endl;

    return 0;
}