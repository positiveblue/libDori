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
            // if you have the elements already hashed you can use the
            // offerHash(hash) mehtod instead
            estimator->offer(element);

        // The cardinality mehtod offers an estiamtion of the real cardinality of the stream
        std::cout << "Cardinality: " << estimator->cardinality() << std::endl;

        // The elementsOffered is a simple counter of how many elements had been offered
        std::cout << "Total elements: " << estimator->elementsOffered() << std::endl;

        ```

    - *Membership:*
        ```cpp
        
        ```
    
    - *Frequency:*
        ```cpp
        
        ```
## Quick start

## Contributing

## Issue tracker

## License
