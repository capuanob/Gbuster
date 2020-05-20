//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_HASHTHREAD_H
#define GBUSTER_HASHTHREAD_H

#include <map>
#include <thread>
#include "cpustring.h"

/**
 * Used by a HashThread to add a discovered clear text to the global mapping
 * @warning MUST USE A MUTEX
 * @param hash Hash that the cleartext resolves [key]
 * @param clear Cleartext that was discovered [value]
 */
void addClearText(std::string hash, std::string clear) noexcept;

/**
 * Actual function for breaking hashes
 * @param start First string to attempt
 * @param end  Last string to attempt
 */
void work(const hash::string& start, const hash::string& end);

/**
 * Function object used to store data local to a thread
 */
class HashThread {
    hash::string startString; // First string to hash
    hash::string endString; // Last string to hash
};


#endif //GBUSTER_HASHTHREAD_H
