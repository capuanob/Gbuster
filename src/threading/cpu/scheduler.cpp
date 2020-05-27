//
// Created by bailey on 5/18/20.
//

#include "scheduler.h"

#include <utility>

Scheduler::Scheduler(int workerCount,
                     unsigned int maxLen, std::unordered_set<std::string>&& hashes)
        : hash_list(hashes), maxLen(maxLen){
    // Build distribution

    // Establish cleartext range
    ull lastString = std::pow(NumberSystem::getBase(), maxLen);
    ull singleWorkLoad = static_cast<ull>(lastString / workerCount);

    for (ull curr = 0; curr < lastString; curr += singleWorkLoad + 1) {
        workDistribution.emplace_back(curr, ((curr + singleWorkLoad) > lastString) ? lastString : (curr + singleWorkLoad));
    }
}

void Scheduler::dispatchWorkers() {
    // Create the provided number of threads
    thread_pool.reserve(workDistribution.size());

    // Set up hash thread constants
    HashThread::SetConstants(maxLen, hash_list);
    // Dispatch the thread
    thread_pool.clear();
    for (const auto& distr : workDistribution) {
        thread_pool.emplace_back(std::make_unique<HashThread>(std::cref(distr.first), std::cref(distr.second)));
    }

    for (auto& thread : thread_pool) {
        thread->Run();
    }

}