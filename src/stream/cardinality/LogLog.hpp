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

    int k;
    int m;
    double Ca;
    int Rsum = 0;
    std::vector<std::size_t> M;
    std::hash<std::size_t> hasher;


    inline int getIndex(std::size_t hashedValue) {
        hashedValue >> (sizeof(std::size_t) - k);
    }

    std::size_t getOffset(std::size_t bites){
        int zeros = 1 << k;
        return bites & (0xFFFFFFFFFFFFFFFF >> zeros);
    }


    int scan1(std::size_t bites) {
        //TODO: Use bitwise algorithm to get the first one
        std::size_t offset = getOffset(bites);
        std::size_t aux = log2(offset);
        return sizeof(std::size_t) - k - aux;
    }

public:

    LogLog(int k) {
        if (k >= (mAlpha.size() - 1)) {
            throw std::string("Max k (%d) exceeded: k=%d", mAlpha.size() - 1, k);
        }

        this->k = k;
        this->m = 1 << k;
        this->Ca = mAlpha[k];
        this->M =  std::vector<std::size_t> (m);
    }

    bool offerHashed(std::size_t hashedValue) {
        bool modified = false;

        int j = getIndex(hashedValue);
        std::size_t r =  scan1(hashedValue);
        if (M[j] < r) {
            Rsum += r - M[j];
            M[j] = r;
            modified = true;
        }

        return modified;
    }

    std::size_t cardinality() {
        double Ravg = Rsum / (double) m;
        return (long) (Ca * pow(2, Ravg));
    }

    bool offer(T o) {
        std::size_t x =  hasher(o);
        return offerHashed(x);
    }
};

#endif //LIBSTREAM_LOGLOG_H
