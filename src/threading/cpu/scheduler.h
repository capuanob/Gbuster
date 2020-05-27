//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_SCHEDULER_H
#define GBUSTER_SCHEDULER_H

#include "CpuHardware.h"
#include "HashThread.h"
#include <memory>

using workPerThread = std::pair<ull, ull>;

class Scheduler {
public:
    /**
     *  Given a character set, fairly divide the work amongst the n workers.
     * @param workerCount Number of workers (n) that will brute force over the character set
     * @param maxLen Maximum length that the cleartext can be
     * @param hashes Collection of hashes to break
     */
    Scheduler(int workerCount,
              unsigned int maxLen, std::unordered_set<std::string>&& hashes);
    /**
     * Thread driver functions. Creates and starts threads.
     */
    void dispatchWorkers();

private:
    std::vector<std::unique_ptr<HashThread>> thread_pool;
    std::unordered_set<std::string> hash_list;
    std::vector<workPerThread> workDistribution;
    const unsigned int maxLen;
};


#endif //GBUSTER_SCHEDULER_H
