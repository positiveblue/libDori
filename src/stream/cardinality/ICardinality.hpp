//
// Created by jordi on 8/14/2016.
//

#ifndef LIBSTREAM_ICARDINALITY_H
#define LIBSTREAM_ICARDINALITY_H

#include <cstddef> /* size_t */


template <typename T>
class ICardinality {
public:

    /**
    * @param o stream element
    * @return false if the value returned by cardinality() is unaffected by the appearance of o in the stream.
    */
    virtual bool offer(T o) = 0;

    /**
     * Offer the value as a hashed long value
     *
     * @param hashedLong - the hash of the item to offer to the estimator
     * @return false if the value returned by cardinality() is unaffected by the appearance of hashedLong in the stream
     */
    virtual bool offerHashed(long hashedLong) = 0;

    /**
     * Offer the value as a hashed long value
     *
     * @param hashedInt - the hash of the item to offer to the estimator
     * @return false if the value returned by cardinality() is unaffected by the appearance of hashedInt in the stream
     */
    virtual bool offerHashed(int hashedInt) = 0;

    /**
     * @return the number of unique elements in the stream or an estimate thereof
     */
    virtual std::size_t cardinality() = 0;

    /**
     * How many elements has it processed
     */
    virtual std::size_t elementsOffered() = 0;

    /**
     * Defautl destructor for ICardinality
     */
    virtual ~ICardinality(){};
};

#endif //LIBSTREAM_ICARDINALITY_H
