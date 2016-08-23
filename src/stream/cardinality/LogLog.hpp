//
// Created by jordi on 8/14/2016.
//

#ifndef LIBSTREAM_LOGLOG_H
#define LIBSTREAM_LOGLOG_H

#include <vector>
#include <math.h>         /* pow */
#include <cstddef>        /* size_t */
#include <functional>     /* hash */
#include "ICardinality.hpp"
#include "../../hash/Hasher.hpp"
#include <iostream>


template <typename T>
class LogLog : public ICardinality<T> {

    /**
     * Gamma function computed using Mathematica
     * AccountingForm[
     * N[With[{m = 2^Range[0, 31]},
     * m (Gamma[-1/m]*(1 - 2^(1/m))/Log[2])^-m], 14]]
     */
    std::vector<double> mAlpha {
            0,
            0.44567926005415,
            1.2480639342271,
            2.8391255240079,
            6.0165231584809,
            12.369319965552,
            25.073991603111,
            50.482891762408,
            101.30047482584,
            202.93553338100,
            406.20559696699,
            812.74569744189,
            1625.8258850594,
            3251.9862536323,
            6504.3069874480,
            13008.948453415,
            26018.231384516,
            52036.797246302,
            104073.92896967,
            208148.19241629,
            416296.71930949,
            832593.77309585,
            1665187.8806686,
            3330376.0958140,
            6660752.5261049,
            13321505.386687,
            26643011.107850,
            53286022.550177,
            106572045.43483,
            213144091.20414,
            426288182.74275,
            852576365.81999
    };

    /**
     * Number of bits used as bucket index.
     */
    std::uint8_t k;

    /**
     * Number of elements that has been offered (not distinct elements!!)
     */
    std::uint64_t n;

    /**
     * m represent the number of “small bytes” of auxiliary memory (number of buckets)
     * m = 1 << k
     */
    std::uint32_t m;

    double Ca;

    /**
     * Keep the sum of all the buckets, always updated.
     */
    int Rsum = 0;

    /**
     * Vector with m buckets
     */
    std::vector<std::uint32_t> M;

    /**
     * Hash function used to hash the stream's elements.
     */
    IHasher<std::string> *hasher_ptr;


    /**
     *
     * @param bites
     * @return Number of bucket which it belows
     */
    inline std::uint32_t getIndex(std::uint32_t bites) {
        return bites >> (32 - k);
    }

    /**
     *
     * @param bites
     * @return
     */
    inline std::uint32_t getOffset(std::uint32_t bites){
        return bites & (0xFFFFFFFF >> (this->k));
    }


    /**
     *
     * @param bites
     * @return
     */
    std::uint32_t scan1(std::uint32_t bites) {
        //TODO: Use bitwise algorithm to get the first one
        return (32 - k - log2(getOffset(bites)));
    }

public:

    LogLog(std::uint8_t k=5) {
        this->k = k;
        this->n = 0;
        this->m = 1 << (this->k);
        this->Ca = mAlpha[(this->k)];
        this->M =  std::vector<std::uint32_t> (this->m);
        this->hasher_ptr = new MurmurHash<std::string> (-1);
    }


    bool offerHashed(std::uint32_t hashedValue) {
        ++n;
        bool modified = false;
        std::uint32_t j = getIndex(hashedValue);
        std::uint32_t r =  scan1(hashedValue);
        if (M[j] < r) {
            Rsum += (r - M[j]);
            M[j] = r;
            modified = true;
        }

        return modified;
    }

    std::uint32_t cardinality() {
        double Ravg = Rsum / (double) m;
        return (Ca * pow(2, Ravg));
    }

    bool offer(T o) {
        std::uint32_t x =  hasher_ptr->hash(o);
        return offerHashed(x);
    }

    std::uint64_t elementsOffered() {
        return n;
    }
};

#endif //LIBSTREAM_LOGLOG_H
