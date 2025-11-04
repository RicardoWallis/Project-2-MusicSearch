//
// Created by ricar on 11/3/2025.
//

#ifndef PROJECT2_HASHTABLE_H
#define PROJECT2_HASHTABLE_H
#include "Song.h"
#include <vector>
#include <list>
#include <string>
using namespace std;

class HashTable {
private:
    vector<list<Song>> table;
    size_t capacity;
    size_t HashFunction(const string& key) const;

public:
    HashTable(size_t size = 211);
    void insert(const Song& song);
    bool remove(const string& name);
    Song* search(const string& name);
    void display() const;
};


#endif //PROJECT2_HASHTABLE_H