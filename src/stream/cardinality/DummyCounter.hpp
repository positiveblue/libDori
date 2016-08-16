//
// Created by jordi on 8/15/2016.
//

#ifndef LIBSTREAM_DUMMYCOUNTER_HPP
#define LIBSTREAM_DUMMYCOUNTER_HPP

#include <unordered_set>
#include "ICardinality.hpp"


template <typename T>
class DummyCounter : public ICardinality<T> {


    int n;
    std::unordered_set<std::size_t> itemSet;
    std::hash<std::size_t> hasher;
    const int MAX_SET_SIZE = 1 << 16;



public:

    DummyCounter() : n{0} {}

    bool offerHashed(std::size_t hashedValue) {
        ++n;
        int old_size = itemSet.size();
        itemSet.insert(hashedValue);
        return (itemSet.size() != old_size);
    }

    std::size_t cardinality() {
        return itemSet.size();
    }

    boolean offer(T o) {
        std::size_t x =  hasher(o);
        return offerHashed(x);
    }

    std::size_t elementsOffered() {
        return n;
    }
};

#endif //LIBSTREAM_DUMMYCOUNTER_HPP
