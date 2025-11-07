//
// Created by Ethan Wilen on 11/3/25.
//
#pragma once
#include <string>
#include <vector>
#include "Song.h"

using namespace std;
class Trie {
    public:
        Trie();
        ~Trie();
        void insert(const Song* song);
        bool containsExact(const string& songName) const;

    private:
        struct Node {
            bool isEnd;
            Node* child[128];
            Node() : isEnd(false) {
                for (auto &c : child) c = nullptr;
            }
        };
        Node* root;
        static string normalize(const string& s);   // lowercase
        static void freeNode(Node* node);
};
