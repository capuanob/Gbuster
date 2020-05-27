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
    inline void addHash(const std::string& hash) { hashes.insert(hash); }
    inline auto size() const noexcept -> unsigned long { return hashes.size(); }

    inline auto getHashes() noexcept -> std::unordered_set<std::string>& { return hashes; }

    // Constructors and move operators
    HashModel() = default; // constructor
    ~HashModel() = default; // destructor
    HashModel(const HashModel& other) { // copy constructor
        this->hashes = other.hashes;
    }
    auto operator=(const HashModel& other) -> HashModel& { // copy assignment constructor
        if (this != &other) {
            this->hashes = other.hashes;
        }
        return *this;
    }
    HashModel(HashModel&& other)  noexcept { // Move constructor
        this->hashes = other.hashes;
    }
    auto operator=(HashModel&& other)  noexcept -> HashModel& { // Move assignment constructor
        if (this != &other) {
            this->hashes = other.hashes;
        }
        return *this;
    }
private:
    std::unordered_set<std::string> hashes; // Stores all hashes to be cracked.
};


#endif //GBUSTER_HASHMODEL_H
