//
// Created by bailey on 5/18/20.
//

#include "CpuHardware.h"

auto CpuHardware::getCoreTemperatures(const std::vector<fs::path>& temperatureFilePaths) -> std::vector<double> {
    std::ifstream inFile;
    std::vector<double> temps;
    for (const auto& p : temperatureFilePaths) {
        inFile.open(p, std::ifstream::in);

        if (inFile) {
            std::string tempStr;
            getline(inFile, tempStr); // As first line contains temperature, it's all we need
            int thousandsVal = stoi(tempStr); // Holds temperature, to the thousands
            temps.emplace_back(thousandsVal / 1000.0);
            inFile.close();
        }
    }

    return temps;
}

void CpuHardware::findTemperatureFilesAt(std::vector<fs::path>& tempPaths, const fs::path& rootDirPath) {
    for (const auto& child_dir_item : fs::directory_iterator(rootDirPath)) {
        if (child_dir_item.is_directory() && CpuHardware::fileContainsSubstring(child_dir_item, "thermal_zone")) {
            findTemperatureFilesAt(tempPaths, child_dir_item.path());
        } else if (child_dir_item.path().filename().string() == "temp") {
            tempPaths.push_back(child_dir_item.path());
        }
    }
}
