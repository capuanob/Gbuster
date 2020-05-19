//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_CPUHARDWARE_H
#define GBUSTER_CPUHARDWARE_H
#include <string>
#include <thread>

class CpuHardware {
public:
    /**
     * Determines the number of concurrent threads supported by the implementation
     * @return the above number
     */
    inline static unsigned int getMaximumThreads() {  return std::thread::hardware_concurrency(); }
};


#endif //GBUSTER_CPUHARDWARE_H
