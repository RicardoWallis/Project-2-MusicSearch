//
// Created by Ethan Wilen on 11/3/25.
//

#include "Trie.h"
#include <cctype>

Trie::Trie() {
    root = new Node();
}

Trie::~Trie() {
    freeNode(root);
}

void Trie::freeNode(Node* node) {
    if (!node){
        return;
    }
    for (Node* c : node->child) {
        if (c){
            freeNode(c);
        }
    }
    delete node;
}

string Trie::normalize(const string& s) {
    string lower= s;
    for (char &ch : lower)
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    return lower;
}

void Trie::insert(const Song* song) {
    if (!song){
        return;
    }
    string lower = normalize(song->getName());
    if (lower.empty()){
        return;
    }
    Node* current = root;
    for (char ch : lower){
        unsigned char index = ch;
        if (!current->child[index]){
            current->child[index] = new Node();
        }
        current = current->child[index];
    }
    current->isEnd = true;
}

bool Trie::containsExact(const string& songName) const {
    string lower = normalize(songName);
    Node* current = root;

    for (char ch : lower){
        unsigned char index = ch;
        if (!current->child[index]){
            return false;
        }
        current = current->child[index];
    }
    return current->isEnd;
}


