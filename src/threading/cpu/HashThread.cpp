//
// Created by bailey on 5/22/20.
//

#include "HashThread.h"
#include <iostream>

wxThread::ExitCode HashThread::Entry() {
    auto curr = start; // Copy by value
    std::array<byte, md5::WORDS_IN_BLOCK> digest{};
    std::array<byte, Constants::MAX_PASSWORD_LEN> clearText{};

    while (curr != end) {
        unsigned int actualLen = NumberSystem::toBase(curr, clearText);
        md5::getDigest(clearText, digest, actualLen);
        auto digestStr = md5::digestStr(digest);

        if (hashList.find(digestStr) != hashList.end()) { // Hash resolved
            std::string clearStr(clearText.begin(), clearText.end());
            mutex->Lock(); // Enter CS
            resolvedHashes.emplace(digestStr, clearStr);
            mutex->Unlock(); // Exit CS
        }
        ++curr;
    }

    mutex->Lock();
    std::cout << "Finished" << std::endl;
    for (const auto& pair : resolvedHashes)
        std::cout << pair.first << " --> " << pair.second << std::endl;
    mutex->Unlock();
    return 0;
}

void HashThread::SetConstants(int mLen, stringSet set) {
    HashThread::maxLen = mLen;
    HashThread::hashList = set;
}