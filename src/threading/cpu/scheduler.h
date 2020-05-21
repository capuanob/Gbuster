//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_SCHEDULER_H
#define GBUSTER_SCHEDULER_H

#include <functional> // Thread pass by reference
#include <mutex>
#include <unordered_set>
#include "CpuHardware.h"
#include "cpustring.h"
#include "md5.h"


using workPerThread = std::pair<hash::string, hash::string>;

class Scheduler {
public:
    /**
     *  Given a character set, fairly divide the work amongst the n workers.
     * @param characterSet Set of all characters that a cleartext can contain
     * @param workerCount Number of workers (n) that will brute force over the character set
     * @param maxLen Maximum length that the cleartext can be
     * @param hashes Collection of hashes to break
     */
    Scheduler(const CharacterSet& characterSet, unsigned int workerCount,
            unsigned int maxLen, std::unordered_set<std::string>  hashes);

    /**
     * Thread driver functions. Creates and starts threads.
     */
    void dispatchWorkers();

    /**
     * Actual function for breaking hashes
     * @param start First string to attempt
     * @param end  Last string to attempt
     */
    static void work(
            const hash::string& start,
            const hash::string& end,
            const std::unordered_set<std::string>& hash_list,
            std::unordered_map<std::string, std::string>& resolved_hashes
    );
    inline static std::mutex mtx; // Mutex for critical section
private:
    std::vector<std::thread> thread_pool;
    std::unordered_set<std::string> hash_list;
    std::unordered_map<std::string, std::string> resolved_hashes;
    std::vector<workPerThread> workDistribution;
};


#endif //GBUSTER_SCHEDULER_H
