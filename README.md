# libDori

![alt text](https://img.shields.io/badge/release-0.0.1-green.svg)
[![Build Status](https://travis-ci.org/jomsdev/libDori.svg?branch=master)](https://travis-ci.org/jomsdev/libDori)
[![Coverage Status](https://coveralls.io/repos/github/jomsdev/libDori/badge.svg?branch=master)](https://coveralls.io/github/jomsdev/libDori?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


## Examples

libDori can be used directly in a C++ project or or with the provided shell scripts and good old Unix IO redirection.

- **CLI**:

    The code for the command line programs can be found in the cli folder. They are built on top of the C++ library and expose 
    in a convenient way three of the basic features of libDori: Cardinality, Frequent items and Sampling.

    - *Cardinality:* [Todo] 

    - *Frequent Items:* [Todo] 

    - *Sampling:* [Todo] 

    Run `cmd --help` for more information.

- **C++ API**

    Meanwhile a full API documentation is being developed this can be used as a first contact with the library and its interfaces.

    - *Cardinality:*
        ```cpp
        // ICardinality is the interface for all the cardinality estimators.
        // The algorithms implemented are: DummyCounter, HyperLogLog, KMV and Recordinality
        dori::stream::ICardinality* estimator = new dori::stream::HyperLogLog(size);

        // Process each of the elements with the offer method
        std::string element;
        while (file >> element)
            // If you have the elements already hashed you can use the
            // offerHash(hash) mehtod instead
            estimator->offer(element);

        // The cardinality mehtod offers an estiamtion of the real cardinality of the stream
        std::cout << "Cardinality: " << estimator->cardinality() << std::endl;

        // The elementsOffered is a simple counter of how many elements had been offered
        std::cout << "Total elements: " << estimator->elementsOffered() << std::endl;
        ```

    - *Membership:*
        ```cpp
            // The bloom filter constructor take two params: 
            // - Number of distinct elements expected
            // - Probability of failure
            auto bf = dori::stream::BloomFilter(3000, 0.01);
            
            // We insert each one of the elements to the bloom filter
            std::string element;
            while (file >> element)
                bf.insert(element);

            // At any moment we can ask if one element has been inserted or not in the 
            // BloomFilter (False means always No, meanwhile yes has some failure probabilty) 
            bf.contains("libDori");
        ```
    
    - *Frequency:* [TODO]

## Quick start

## Contributing

## Issue tracker

## License

 LibDori is under the MIT license. See the [LICENSE](https://github.com/jomsdev/libDori/blob/master/LICENSE) file for details.

