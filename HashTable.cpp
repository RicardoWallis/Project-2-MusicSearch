//
// Created by ricar on 11/3/2025.
//
#include "HashTable.h"
#include <iostream>

static string normalize(const string& s) {
    string t = s;
    for (char& c : t)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return t;
}

//Constructor
HashTable::HashTable(size_t size) : capacity(size) {
    table.resize(capacity);
}
//Hashing Function; hashes keys (names) before adding them
size_t HashTable::HashFunction(const string& key) const {
    size_t hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % capacity;
    }
    return hash;
}
//Insert a song by name
void HashTable::insert(const Song& song) {
    size_t index = HashFunction(normalize(song.getName()));
    bool dupe = false;
    for (const auto& song_ : table[index]) {
        if (song_ == song) {
            //cout << "Duplicate found" << endl;
            dupe = true;
            break;
        }
    }
    if (!dupe) {
        //cout << "Inserting: " << song.getName() << " by " << song.getArtist() << endl;
        table[index].push_back(song);
    }
}
//Remove song by name
bool HashTable::remove(const string& name) {
    size_t index = HashFunction(name);
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->getName() == name) {
            chain.erase(it);
            return true;
        }
    }
    return false;
}
//Search for all songs with a specific name
vector<Song*> HashTable::searchName(const std::string& name) {
    std::vector<Song*> results;
    size_t index = HashFunction(name);
    for (auto& song : table[index]) {
        if (normalize(song.getName()) == normalize(name)) {
            results.push_back(&song);
        }
    }
    return results;
}

// Search for all songs by a specific artist
vector<Song*> HashTable::searchArtist(const string& artist) {
    vector<Song*> songs;
    for (auto& bucket : table) {
        for (auto& song : bucket) {
            if (song.getArtist() == artist) {
                songs.push_back(&song);
            }
        }
    }
    return songs;
}
//Search for all songs with a specific genre
vector<Song*> HashTable::searchGenre(const string& genre) {
    vector<Song*> songs;
    for (auto& bucket : table) {
        for (auto& song : bucket) {
            if (song.getGenre() == genre) {
                songs.push_back(&song);
            }
        }
    }
    return songs;
}
// Display all entries in the Table
void HashTable::display() const {
    for (size_t i = 0; i < capacity; ++i) {
        cout << "[" << i << "]: ";
        for (const auto& song : table[i]) {
            cout << "(" << song.getName() << " by " << song.getArtist() << ") ";
        }
        cout << endl;
    }
}