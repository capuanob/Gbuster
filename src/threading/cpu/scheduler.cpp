//
// Created by bailey on 5/18/20.
//

#include "scheduler.h"

Scheduler::Scheduler(const std::vector<char>& characterSet, unsigned int workerCount, unsigned int maxLen) {
    unsigned int charCount = characterSet.size();
    char lastChar = characterSet.back();

    workDistribution.reserve(workerCount);

    if (charCount > workerCount) { // Need to fairly distribute
        // Determine starting and ending first characters for each worker
        auto averageCharsPerWorker = static_cast<unsigned int>(charCount /
                                                               workerCount); // Work for first workerCount - 1
        int remainder = static_cast<int>(charCount % workerCount);

        // Assign each worker a representative pair
        auto charIter = characterSet.begin();

        for (int i = 1; i <= workerCount; ++i, charIter += averageCharsPerWorker, --remainder) {
            auto beginChar = charIter;
            auto endChar = charIter + averageCharsPerWorker - 1;
            if (remainder > 0) {
                endChar += 1;
                charIter += 1;
            }
            workDistribution.emplace_back(*beginChar, *endChar + std::string(maxLen, lastChar));
        }
    } else { // First char count threads get work
        for (const auto& c: characterSet)
            workDistribution.emplace_back(c, c + std::string(maxLen, lastChar));

        workDistribution.resize(characterSet.size()); // Resize to free workers without jobs
    }
}

void Scheduler::dispatchWorkers() const {

}
