//
// Created by bailey on 5/17/20.
//

#ifndef GBUSTER_HASHMODEL_H
#define GBUSTER_HASHMODEL_H

#include <unordered_set>

/**
 * This class serves as the model in the application's MVC architecture. It handles storage of properties
 * needed to carry out the application's hashing
 * @author: Bailey Capuano
 */
class HashModel {
public:

    /**
     * Add the given hash to the hashes map
     *
     * @param hash Hash to be added
     */
    inline void add_hash(const std::string& hash) { hashes.insert(hash); }
    inline unsigned long size() const noexcept { return hashes.size(); }

    inline std::unordered_set<std::string> getHashes() const noexcept { return hashes; }
    HashModel() = default;
    ~HashModel() = default;
private:
    std::unordered_set<std::string> hashes; // Stores all hashes to be cracked.
};


#endif //GBUSTER_HASHMODEL_H
