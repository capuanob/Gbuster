//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_CPUHARDWARE_H
#define GBUSTER_CPUHARDWARE_H
#include <string>
#include <thread>
#include <cpuid.h>
#include <cstring>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs =  std::filesystem;
class CpuHardware {
public:
    static constexpr const int MAX_CORES_ON_MARKET = 48; // At least the maximum I'll support when walking the file tree
    static inline const fs::path tempPath = "/sys/class/thermal/";
    /**
     * @return The number of concurrent threads supported by the implementation
     */
    inline static auto getMaximumThreads() -> unsigned int {  return std::thread::hardware_concurrency(); }

    template <class T>
    inline auto static fileContainsSubstring(const T& file, const std::string& substr) -> bool {
        return std::string(file.path().filename()).find(substr) != std::string::npos;
    }

    static void findTemperatureFilesAt(std::vector<fs::path>& tempPaths, const fs::path& rootDirPath = tempPath);
    static auto getCoreTemperatures(const std::vector<fs::path>& temperatureFilePaths) -> std::vector<double>;

};


#endif //GBUSTER_CPUHARDWARE_H
