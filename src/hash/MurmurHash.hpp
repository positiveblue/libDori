//
// Created by Jordi Sanabria on 8/22/16.
//

#ifndef LIBSTREAM_MURMURHASH_HPP
#define LIBSTREAM_MURMURHASH_HPP
#include "IHasher.hpp"
#include "utils.cpp"
template <typename T>
class MurmurHash : public IHasher<T> {

    std::uint64_t seed;
public:

    MurmurHash() {
        this->seed = uint64RandomNumber();
    }

    MurmurHash(std::uint64_t _seed) : seed{_seed} {}

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
        std::uint64_t m = 0xc6a4a7935bd1e995L;
        int r = 47;

        std::uint64_t h = (seed & 0xffffffffl) ^ (length * m);

        int length8 = length / 8;

        for (int i = 0; i < length8; i++) {
            int i8 = i * 8;
            std::uint64_t k = ((std::uint64_t) str[i8 + 0] & 0xff) + (((std::uint64_t) str[i8 + 1] & 0xff) << 8)
                     + (((std::uint64_t) str[i8 + 2] & 0xff) << 16) + (((std::uint64_t) str[i8 + 3] & 0xff) << 24)
                     + (((std::uint64_t) str[i8 + 4] & 0xff) << 32) + (((std::uint64_t) str[i8 + 5] & 0xff) << 40)
                     + (((std::uint64_t) str[i8 + 6] & 0xff) << 48) + (((std::uint64_t) str[i8 + 7] & 0xff) << 56);

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        switch (length % 8) {
            case 7:
                h ^= (std::uint64_t) (str[(length & ~7) + 6] & 0xff) << 48;
            case 6:
                h ^= (std::uint64_t) (str[(length & ~7) + 5] & 0xff) << 40;
            case 5:
                h ^= (std::uint64_t) (str[(length & ~7) + 4] & 0xff) << 32;
            case 4:
                h ^= (std::uint64_t) (str[(length & ~7) + 3] & 0xff) << 24;
            case 3:
                h ^= (std::uint64_t) (str[(length & ~7) + 2] & 0xff) << 16;
            case 2:
                h ^= (std::uint64_t) (str[(length & ~7) + 1] & 0xff) << 8;
            case 1:
                h ^= (std::uint64_t) (str[length & ~7] & 0xff);
                h *= m;
        }
        ;

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
    }
};



#endif //LIBSTREAM_MURMURHASH_HPP
