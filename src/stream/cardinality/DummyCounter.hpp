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

    /*
     * TODO: Description
     */
    DummyCounter() : n{0} {}

    /*
     * TODO: Description
     */
    bool offerHash(std::uint64_t element) {
        throw "Don't use offerHash with the Dummy Counter. Instead use offer";
    }

    /*
     * TODO: Description
     */
    std::uint64_t cardinality() {
        return itemSet.size();
    }

    /*
     * TODO: Description
     */
    bool offer(T o) {
        ++n;
        int old_size = itemSet.size();
        itemSet.insert(o);
        return (itemSet.size() != old_size);
    }

    /*
     * TODO: Description
     */
    std::uint64_t elementsOffered() {
        return n;
    }
};

#endif //LIBSTREAM_DUMMYCOUNTER_HPP
