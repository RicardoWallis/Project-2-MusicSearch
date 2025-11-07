//
// Created by ricar on 11/3/2025.
//

#pragma once
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
    HashTable(size_t size = 87803);
    void insert(const Song& song);
    bool remove(const string& name);
    vector<Song*> searchName(const string& name);
    vector<Song*> searchArtist(const string& name);
    vector<Song*> searchGenre(const string& name);
    void display() const;
};
