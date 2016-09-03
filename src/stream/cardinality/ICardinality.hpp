//
// Created by Jordi Montes Sanabria on 8/14/2016.
//

#ifndef LIBSTREAM_ICARDINALITY_H
#define LIBSTREAM_ICARDINALITY_H



template <typename T>
class ICardinality {
public:

    /**
    * @param o stream element
    * @return false if the value returned by the cardinality() is unaffected by the appearance of o in the stream.
    */
    virtual bool offer(T o) = 0;

    /**
     * Offer the value as a hashed long value
     *
     * @param hashedInt - the hash of the item to offer to the estimator
     * @return false if the value returned by cardinality() is unaffected by the appearance of hashedInt in the stream
     */
    virtual bool offerHash(std::uint64_t hashValue) = 0;

    /**
     * @return the number of unique elements in the stream or an estimate thereof
     */
    virtual std::uint64_t cardinality() = 0;

    /**
     * How many elements has it processed
     */
    virtual std::uint64_t elementsOffered() = 0;

    /**
     * Defautl destructor for ICardinality
     */
    virtual ~ICardinality(){};
};

#endif //LIBSTREAM_ICARDINALITY_H
