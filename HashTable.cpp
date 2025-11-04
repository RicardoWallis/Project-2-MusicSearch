//
// Created by ricar on 11/3/2025.
//
#include "HashTable.h"
#include <iostream>

HashTable::HashTable(size_t size) : capacity(size) {
    table.resize(capacity);
}

size_t HashTable::HashFunction(const string& key) const {
    size_t hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % capacity;
    }
    return hash;
}

void HashTable::insert(const Song& song) {
    size_t index = HashFunction(song.getName());
    table[index].push_back(song);
}

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

Song* HashTable::search(const string& name) {
    size_t index = HashFunction(name);
    for (auto& song : table[index]) {
        if (song.getName() == name) {
            return &song;
        }
    }
    return nullptr;
}

void HashTable::display() const {
    for (size_t i = 0; i < capacity; ++i) {
        cout << "[" << i << "]: ";
        for (const auto& song : table[i]) {
            cout << "(" << song.getName() << " by " << song.getArtist() << ") ";
        }
        cout << endl;
    }
}