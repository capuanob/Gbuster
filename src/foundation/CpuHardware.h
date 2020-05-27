//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_CPUHARDWARE_H
#define GBUSTER_CPUHARDWARE_H
#include <string>
#include <thread>
#include <cpuid.h>
#include <cstring>
class CpuHardware {
public:
    /**
     * @return The number of concurrent threads supported by the implementation
     */
    inline static unsigned int getMaximumThreads() {  return std::thread::hardware_concurrency(); }
};


#endif //GBUSTER_CPUHARDWARE_H
