//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_SCHEDULER_H
#define GBUSTER_SCHEDULER_H

#include "CpuHardware.h"
#include "HashThread.h"
#include <wx/panel.h>
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
    Scheduler(int workerCount, int maxLen, std::unordered_set<std::string>&& hashes, wxPanel* parent);
    /**
     * Thread driver functions. Creates and starts threads.
     */
    void dispatchWorkers();

    inline auto getDistribution() -> const std::vector<workPerThread>& { return workDistribution; }

    inline auto getThreads() const -> const std::vector<HashThread*>& { return thread_pool; }

    void deleteThread(int threadIdx);

    inline auto completed() -> bool { return deadThreads >= thread_pool.size(); }
private:
    std::vector<HashThread*> thread_pool;
    unsigned int deadThreads; // Track how many threads have been deleted
    std::unordered_set<std::string> hash_list;
    std::vector<workPerThread> workDistribution;
    wxPanel* parent;
    const int maxLen;
};


#endif //GBUSTER_SCHEDULER_H
