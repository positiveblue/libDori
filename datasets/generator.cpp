#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <algorithm>

int main(int argc, char* argv[]) {
    static const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    size_t N_STRS = strtol(argv[1], NULL, 10);
    size_t S_LEN = strtol(argv[2], NULL, 10);

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<> dist(0,sizeof(alphabet)/sizeof(*alphabet)-2);

    std::vector<std::string> strs;
    strs.reserve(N_STRS);
    std::generate_n(std::back_inserter(strs), strs.capacity(),
        [&] { std::string str; 
              str.reserve(S_LEN); 
              std::generate_n(std::back_inserter(str), S_LEN,
                   [&]() { return alphabet[dist(rng)];}); 
              return str; });
    std::copy(strs.begin(), strs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return 0;
}