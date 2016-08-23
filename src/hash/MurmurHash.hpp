//
// Created by Jordi Sanabria on 8/22/16.
//

#ifndef LIBSTREAM_MURMURHASH_HPP
#define LIBSTREAM_MURMURHASH_HPP
#include "IHasher.hpp"

template <typename T>
class MurmurHash : public IHasher<T> {

    int seed;
public:
    MurmurHash(int _seed) : seed{_seed} {}
    std::uint32_t hash(const std::string &str) {
        return hash(str, str.size());
    }

    std::uint32_t hash(const std::string &str, std::size_t length) {

        int m = 0x5bd1e995;
        int r = 24;

        std::size_t h = seed ^ length;

        int len_4 = length >> 2;

        for (int i = 0; i < len_4; i++) {
            int i_4 = i << 2;
            std::size_t k = str[i_4 + 3];
            k = k << 8;
            k = k | (str[i_4 + 2] & 0xff);
            k = k << 8;
            k = k | (str[i_4 + 1] & 0xff);
            k = k << 8;
            k = k | (str[i_4]  & 0xff);
            k *= m;
            k ^= k >> r;
            k *= m;
            h *= m;
            h ^= k;
        }

        // avoid calculating modulo
        int len_m = len_4 << 2;
        int left = length - len_m;

        if (left != 0) {
            if (left >= 3) {
                h ^= (str[length - 3] << 16);
            }
            if (left >= 2) {
                h ^= (str[length - 2] << 8);
            }
            if (left >= 1) {
                h ^= str[length - 1] ;
            }

            h *= m;
        }

        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;

        return h;
    }

    std::uint64_t hash64(const std::string &str) {
        return hash64(str, str.size());
    }

    std::uint64_t hash64(const std::string &str, std::size_t length) {
        return hash64(str, str.size());
    }
};



#endif //LIBSTREAM_MURMURHASH_HPP
