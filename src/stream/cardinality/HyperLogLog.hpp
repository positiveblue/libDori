//
// Created by Jordi Sanabria on 9/5/16.
//

#ifndef LIBSTREAM_HYPERLOGLOG_HPP
#define LIBSTREAM_HYPERLOGLOG_HPP

#include <vector>
#include <math.h>         /* pow */
#include "ICardinality.hpp"
#include "../../hash/Hasher.hpp"

template <typename T>
class HyperLogLog : public ICardinality<T> {

    /**
     * Number of bits used as index for the bucket.
     */
    std::uint64_t k;

    /**
     * Number of elements that has been offered (with repetitions)
     */
    std::uint64_t n;

    /**
     * m represent the number of “small bytes” of auxiliary memory (number of buckets)
     * m = 1 << k
     */
    std::uint64_t m;

    /**
     * Vector with m buckets
     */
    std::vector<std::uint64_t> M;

    /*
     * TODO: Description
     */
    double alphaMM;

    /**
     * Hash function used to hash the stream's elements.
     */
    IHasher<T> *hasher_ptr;


    /**
     * Given a 64 bits number we should decide in which bucket it will go. We will use the first k bits for that.
     * @param bites
     * @return Number of bucket which it belows
     */
    inline std::uint64_t getIndex(std::uint64_t bites) {
        //If someday we change the size of the hashes, remember to change the 64
        return bites >> (64 - k);
    }

    /**
     * If getIndex() return the first K bits, getOffset is the rest.
     * @param bites
     * @return
     */
    inline std::uint64_t getOffset(std::uint64_t bites){

        return bites & (0xFFFFFFFFFFFFFFFF >> (k));
    }


    /**
     * Given a 64 bits number, returns the position of the first one which is in the offset
     * @param bites
     * @return position of the first one which is in the offset
     */
    std::uint64_t scan1(std::uint64_t bites) {
        //TODO: Use bitwise algorithm to get the first one
        return (64 - k - log2(getOffset(bites)));
    }

    /*
     * TODO: Description
     */
    int log2m(double rsd) {
        return (int) (log((1.106 / rsd) * (1.106 / rsd)) / log(2));
    }

    /*
     * TODO: Description
     */
    double rsd(int log2m) {
        return 1.106 / sqrt(exp(log2m * log(2)));
    }

    /*
     * TODO: Description
     */
    inline void validateLog2m(std::uint64_t log2m) {
        if (log2m <= 0 || log2m > 30) {
            throw "log2m argument is outside the range [0, 30]";
        }
    }

    /*
     * TODO: Description
     */
    double getAlphaMM(const std::uint64_t p, const std::uint64_t m) {
        return (0.7213 / (1 + 1.079 / m)) * m * m;
    }

    double linearCounting(int m, double V) {
        return m * log(m / V);
    }

public:

    /**
     * Create a new HyperLogLog instance using the number of buckets.
     *
     * @param k - number of buckets.
     */
    HyperLogLog(std::uint64_t k) {
        validateLog2m(k);
        this->k = k;
        this->n = 0;
        this->m = 1 << k;
        this->M =  std::vector<std::uint64_t> (this->m);
        this->hasher_ptr = new MurmurHash<T> ();
        this->alphaMM = getAlphaMM(k, m);
    }

    /**
     * Create a new HyperLogLog instance using the number of buckets.
     *
     * @param k - number of buckets.
     */
    HyperLogLog(int k) : HyperLogLog((std::uint64_t) k) {}

    /**
     * Create a new HyperLogLog instance using the specified standard deviation.
     *
     * @param rsd - the relative standard deviation for the counter.
     *            smaller values create counters that require more space.
     */
    HyperLogLog(double rsd) : HyperLogLog(log2m(rsd)) {}

    /*
     * TODO: Description
     */
    bool offerHash(std::uint64_t hashValue) {

        ++n;
        bool modified = false;
        std::uint64_t j = getIndex(hashValue);
        std::uint64_t r =  scan1(hashValue);
        if (M[j] < r) {
            modified = true;
            M[j] = r;
        }

        return modified;
    }

    /*
     * TODO: Description
     */
    std::uint64_t cardinality() {

        double registerSum = 0;
        double zeros = 0.0;
        for (int i = 0; i < M.size(); ++i) {
            registerSum += 1.0 / (1 << M[i]);
            if (M[i] == 0) {
                ++zeros;
            }
        }

        double estimate = alphaMM * (1 / registerSum);

        if (estimate <= (5.0 / 2.0) * M.size()) {
            // Small Range Estimate
            return linearCounting(M.size(), zeros);
        } else {
            //Hotfix! Why is the program not working withouth the 2* ?
            return (2*estimate);
        }
    }

    /*
     * TODO: Description
     */
    bool offer(T o) {

        std::uint64_t x =  hasher_ptr->hash64(o);

        return offerHash(x);
    }

    /*
     * TODO: Description
     */
    std::uint64_t elementsOffered() {

        return n;
    }
};

#endif //LIBSTREAM_HYPERLOGLOG_HPP
