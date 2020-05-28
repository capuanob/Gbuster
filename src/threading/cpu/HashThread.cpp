//
// Created by bailey on 5/22/20.
//

#include "HashThread.h"
#include <iostream>
#include <utility>

auto HashThread::Entry() -> wxThread::ExitCode {
    auto curr = start; // Copy by value
    std::array<byte, md5::WORDS_IN_BLOCK> digest{};
    std::array<byte, Constants::MAX_PASSWORD_LEN> clearText{};

    while (curr != end + 1) {
        unsigned int actualLen = NumberSystem::toBase(curr, clearText);
        md5::getDigest(clearText, digest, actualLen);
        auto digestStr = md5::digestStr(digest);

        if (hashList.find(digestStr) != hashList.end()) { // Hash resolved
            std::string clearStr(clearText.begin(), clearText.end());
            mutex->Lock(); // Enter CS
            resolvedHashes.emplace(digestStr, clearStr);
            mutex->Unlock(); // Exit CS
        }

        // Ensure the scheduler hasn't asked the thread to terminate...
        if (TestDestroy()) {
            break;
        }
        ++curr;
        ++count;
    }

    return 0;
}

void HashThread::initSet(stringSet &&set) {
    HashThread::hashList = std::move(set);
}

HashThread::~HashThread() {
    // Notify scheduler that work is completed
    wxCommandEvent deletionEvent(wxEVT_THREAD, THREAD_DELETE_ID);
    deletionEvent.SetInt(identifier); // Set identifier
    mutex->Lock();
    parent->GetEventHandler()->AddPendingEvent(deletionEvent);
    mutex->Unlock();
}
