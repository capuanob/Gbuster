//
// Created by bailey on 5/18/20.
//

#include "scheduler.h"

Scheduler::Scheduler(int workerCount, int maxLen, std::unordered_set<std::string>&& hashes, wxPanel* parent)
        : deadThreads{}, hash_list(hashes), parent(parent), maxLen(maxLen) {

    // Reset HashThreads for new Scheduler
    HashThread::ResetHashThreads();
    // Establish cleartext range
    ull lastString = std::pow(NumberSystem::getBase(), maxLen);
    ull singleWorkLoad = static_cast<ull>(lastString / workerCount);

    for (ull curr = 1; curr < lastString; curr += singleWorkLoad + 1) {
        workDistribution.emplace_back(curr, ((curr + singleWorkLoad) > lastString) ? lastString : (curr + singleWorkLoad));
    }

}

void Scheduler::dispatchWorkers() {
    // Create the provided number of threads
    thread_pool.reserve(workDistribution.size());

    // Set up hash thread constants
    HashThread::initSet(std::move(hash_list));
    // Dispatch the thread
    thread_pool.clear();
    int i = 0;
    for (const auto& distr : workDistribution) {
        thread_pool.emplace_back(new HashThread(i++, std::cref(distr.first), std::cref(distr.second), std::ref(parent)));
    }

    for (auto& thread : thread_pool) {
        thread->Run();
    }
}

void Scheduler::deleteThread(unsigned long int threadIdx) {
    assert(threadIdx <= thread_pool.size());
    thread_pool.at(threadIdx) = nullptr;
    ++deadThreads;
}

void Scheduler::clean() {
    for (const auto& thread : thread_pool) {
        if (thread != wxNullPtr) {
            thread->Delete();
        }
    }
}

Scheduler::~Scheduler() {
    clean();
}
