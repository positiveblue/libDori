//
// Created by jordi on 8/14/2016.
//

#ifndef LIBSTREAM_LOGLOG_H
#define LIBSTREAM_LOGLOG_H

#include <vector>
#include <math.h>         /* pow */
#include "ICardinality.hpp"
#include "../../hash/Hasher.hpp"
#include <iostream>
#include <bitset>


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
     * k: Number of bits used as index for the bucket (Should we limit the value? example 16?).
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

    double Ca;

    /**
     * Keep the sum of all the buckets, always updated.
     */
    std::uint64_t Rsum = 0;

    /**
     * Vector with m buckets
     */
    std::vector<std::uint64_t> M;

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

public:

    /*
     * TODO: Description
     */
    LogLog(std::uint64_t k) {

        if (k >= 32)
            throw "k should be less than 32";

        this->k = k;
        this->n = 0;
        this->m = 1 << (this->k);
        this->Ca = mAlpha[(this->k+1)];
        this->M =  std::vector<std::uint64_t> (this->m);
        this->hasher_ptr = new MurmurHash<T> ();
    }

    /*
     * TODO: Description
     */
    bool offerHash(std::uint64_t hashValue) {

        ++n;
        bool modified = false;
        std::uint64_t j = getIndex(hashValue);
        std::uint64_t r =  scan1(hashValue);

        if (M[j] < r) {
            Rsum+=r;
            Rsum-=M[j];
            M[j] = r;
            modified = true;
        }

        return modified;
    }

    /*
     * TODO: Description
     */
    std::uint64_t cardinality() {

        double Ravg = (Rsum) / (double) m;

        return (Ca * pow(2, Ravg));
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

#endif //LIBSTREAM_LOGLOG_H
