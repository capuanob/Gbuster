//
// Created by bailey on 5/22/20.
//

#ifndef GBUSTER_HASHTHREAD_H
#define GBUSTER_HASHTHREAD_H
#include <wx/thread.h>
#include <wx/panel.h>
#include <unordered_set>
#include <unordered_map>
#include "numberSystem.h"
#include "md5.h"

using stringSet = std::unordered_set<std::string>;
using stringMap = std::unordered_map<std::string, std::string>;

constexpr int THREAD_DELETE_ID = 10000000;
class HashThread : public wxThread {
public:
    // Constructors
    HashThread(unsigned int identifier, const ull start, const ull end, wxPanel* parent)
     :wxThread(wxTHREAD_DETACHED), identifier(identifier), start(start), end(end), parent(parent), count{} {};

    // Destructor
    ~HashThread() override;
    static void initSet(stringSet &&set);
    static void ResetHashThreads(); // Deletes current hashList and resolvedHashes
    inline unsigned int getCount() const { return count; }
    inline static auto getCracked() -> const stringMap& { return resolvedHashes; }
    inline static auto getHashList() -> const stringSet& { return hashList; }
    inline static auto complete() -> bool { return hashList.size() == resolvedHashes.size(); }
private:
    inline static wxMutex* mutex = new wxMutex(); // Mutex used by all threads to control access to critical section of resolved hashes.
    unsigned int identifier; // index in scheduler's thread pool, used for communicating with scheduler
    const ull start; // First string to hash
    const ull end; // Last string to hash
    wxPanel* parent;
    inline static stringSet hashList; // List of hashes fed into program
    inline static stringMap resolvedHashes; // List of hashes resolved by all threads
    unsigned long long count; // Track number of altered

    // Overrides
    auto Entry() -> ExitCode override; // Entry point of thread, where execution begins
};


#endif //GBUSTER_HASHTHREAD_H
