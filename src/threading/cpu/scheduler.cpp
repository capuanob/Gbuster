//
// Created by bailey on 5/18/20.
//

#include "scheduler.h"

#include <utility>

Scheduler::Scheduler(const CharacterSet& characterSet, unsigned int workerCount,
        unsigned int maxLen, std::unordered_set<std::string>  hashes)
        : hash_list(std::move(hashes)) {
    const auto& char_set = characterSet.char_set;
    hash::string::Prepare(characterSet); // Prepare hash::string class for later construction
    unsigned int charCount = char_set.size();
    char lastChar = char_set.back();

    // Initialize workDistribution
    workDistribution.reserve(workerCount);

    if (charCount > workerCount) { // Need to fairly distribute
        // Determine starting and ending first characters for each worker
        auto averageCharsPerWorker = static_cast<unsigned int>(charCount /
                                                               workerCount); // Work for first workerCount - 1
        int remainder = static_cast<int>(charCount % workerCount);

        // Assign each worker a representative pair
        auto charIter = char_set.begin();
        for (int i = 1; i <= workerCount; ++i, charIter += averageCharsPerWorker, --remainder) {
            auto beginChar = charIter;
            auto endChar = charIter + averageCharsPerWorker - 1;
            if (remainder > 0) {
                endChar += 1;
                charIter += 1;
            }
            hash::string str1{std::string(1, *beginChar), maxLen};
            hash::string str2{std::string(1, *endChar) + std::string(maxLen - 1, lastChar), maxLen};

            workDistribution.emplace_back(str1, str2);
        }
    } else { // First char count threads get work
        for (const auto& c: char_set) {
            hash::string str1{std::string(1, c), maxLen};
            hash::string str2{std::string(1, c) + std::string(maxLen - 1, lastChar), maxLen};
            workDistribution.emplace_back(str1, str2);
        }

        workDistribution.resize(char_set.size()); // Resize to free workers without jobs
    }
}

void Scheduler::dispatchWorkers() {
    // Create the provided number of threads
    thread_pool.reserve(workDistribution.size());

    // Dispatch the threads
    for (const auto& distr : workDistribution) {
        thread_pool.emplace_back(&work, std::cref(distr.first), std::cref(distr.second),
                std::cref(hash_list), std::ref(resolved_hashes));
    }

    // Would I launch a thread for GUI updating?
    // Join the threads
    for (auto& thread : thread_pool)
        thread.join();

    hash::string::Reset(); // Prepares string class for next usage

}

void Scheduler::work(const hash::string &start,
                    const hash::string &end,
                    const std::unordered_set<std::string> &hash_list,
                    std::unordered_map<std::string, std::string> &resolved_hashes
) {
    auto curr = start; // Copy by value
    while (curr != end) {
        auto hash = md5::getDigest(std::string(curr));

        if (hash_list.find(hash) != hash_list.end()) { // Hash resolved
            mtx.lock(); // Enter CS
            resolved_hashes.emplace(hash, curr);
            mtx.unlock(); // Exit CS
        }
        ++curr;
    }
}

