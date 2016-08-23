//
// Created by Jordi Sanabria on 8/22/16.
//

#ifndef LIBSTREAM_IHASHER_HPP
#define LIBSTREAM_IHASHER_HPP

template <typename T>
class IHasher {
public:

    // Hash for strings
    virtual std::uint32_t hash(const std::string &str) = 0;
    virtual std::uint64_t hash64(const std::string &str) = 0;

};
#endif //LIBSTREAM_IHASHER_HPP
