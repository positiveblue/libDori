//
// Created by jordi on 8/15/2016.
//

#ifndef LIBSTREAM_DUMMYCOUNTER_HPP
#define LIBSTREAM_DUMMYCOUNTER_HPP

#include <unordered_set>
#include "ICardinality.hpp"


template <typename T>
class DummyCounter : public ICardinality<T> {

    /*
     * n: keeps the counter of how many elements has been offered (with repetitions)
     */
    uint64_t n;

    /*
     * itemSet:  keeps all the elements that has been offered (without repetitions)
     */
    std::unordered_set<T> itemSet;

    /*
    * MAX_SET_SIZE:  Upperbound for the itemSet
    */
    // Remember x << y with y > 32 is has an undefined behavior
    const int MAX_SET_SIZE = 1 << 31;

public:

    DummyCounter() : n{0} {}

    bool offerHashed(std::uint64_t element) {
        throw "Dummy Counter does't work with unit64_t type";
    }

    bool offerHashed(T element) {
        ++n;
        int old_size = itemSet.size();
        itemSet.insert(element);
        return (itemSet.size() != old_size);
    }

    std::uint64_t cardinality() {
        return itemSet.size();
    }

    bool offer(T o) {
        return offerHashed(o);
    }

    std::uint64_t elementsOffered() {
        return n;
    }
};

#endif //LIBSTREAM_DUMMYCOUNTER_HPP
