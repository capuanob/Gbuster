//
// Created by bailey on 5/29/20.
// Used to track user provided data for use during and directly following a cracking session
//

#ifndef GBUSTER_SESSION_H
#define GBUSTER_SESSION_H

#include <array>
#include <vector>
#include <chrono>
#include <filesystem>

using namespace std::chrono;
namespace fs = std::filesystem;

constexpr const double DEFAULT_TEMP = 10000; // Used as temperature before it is explicitly set.
/**
 * Used to store data concerning the current crack session
 */
struct Session {
    bool terminatedEarly{false};
    double maxCoreTemp{DEFAULT_TEMP};
    unsigned int threadCount{};
    HashType hashUsed{};
    std::array<bool, 4> characterSets{}; // Character sets used for this session
    std::vector<fs::path> temperatureFilePaths; // Where to find core temps in file system
    unsigned int chosenPasswordLen{}; // Maximum password length provided via UI
    time_point<high_resolution_clock> start; // Start of hashing
    time_point<high_resolution_clock> end; // End of hashing
};


#endif //GBUSTER_SESSION_H
