//
// Created by bailey on 5/22/20.
//

#ifndef GBUSTER_HASHTHREAD_H
#define GBUSTER_HASHTHREAD_H
#include <wx/thread.h>
#include <unordered_set>
#include <unordered_map>
#include "numberSystem.h"
#include "md5.h"

using stringSet = std::unordered_set<std::string>;
using stringMap = std::unordered_map<std::string, std::string>;

class HashThread : public wxThread {
public:
    // Constructors
    HashThread(const ull start, const ull end) :wxThread(wxTHREAD_DETACHED), start(start), end(end) {}

    static void SetConstants(int maxLen, stringSet set);
private:
    inline static wxMutex* mutex = new wxMutex(); // Mutex used by all threads to control access to critical section of resolved hashes.
    const ull start; // First string to hash
    const ull end; // Last string to hash
    inline static int maxLen = 0; // Maximum password length
    inline static stringSet hashList; // List of hashes fed into program
    inline static stringMap resolvedHashes; // List of hashes resolved by all threads
    // Overrides
    ExitCode Entry() override; // Entry point of thread, where execution begins
};


#endif //GBUSTER_HASHTHREAD_H
