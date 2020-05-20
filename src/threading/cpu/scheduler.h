//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_SCHEDULER_H
#define GBUSTER_SCHEDULER_H

#include <string>
#include <vector>
using workPerThread = std::pair<char, std::string>;

class Scheduler {
public:
    /**
     *  Given a character set, fairly divide the work amongst the n workers.
     * @param characterSet Set of all characters that a cleartext can contain
     * @param workerCount Number of workers (n) that will brute force over the character set
     * @param maxLen Maximum length that the cleartext can be
     */
    Scheduler(const std::vector<char>& characterSet, unsigned int workerCount, unsigned int maxLen);

    /**
     * Thread driver functions. Creates and starts threads.
     */
    void dispatchWorkers() const;

    [[nodiscard]] constexpr const auto &getWorkDistribution() const noexcept { return workDistribution; }
private:
    std::vector<workPerThread> workDistribution;
};


#endif //GBUSTER_SCHEDULER_H
