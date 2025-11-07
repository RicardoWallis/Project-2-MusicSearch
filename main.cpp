//
// Created by Ethan Wilen on 11/3/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include "Song.h"
#include "Trie.h"
#include "HashTable.h"

using namespace std;

string normalize(const string& s) {
    string t;
    for (char c : s)
        t += static_cast<char>(tolower(static_cast<unsigned char>(c)));

    // remove extra spaces
    size_t start = t.find_first_not_of(" \t\r\n\"");
    size_t end = t.find_last_not_of(" \t\r\n\"");
    if (start == string::npos) return "";
    return t.substr(start, end - start + 1);
}

// Load songs from CSV file
vector<Song> loadSongs(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        exit(1);
    }
    vector<Song> songs;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, artist, genre;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');

        songs.emplace_back(name, artist, genre);
    }

    return songs;
}

int main() {
    cout << "Loading dataset..." << endl;
    vector<Song> songs = loadSongs("songs_clean.csv");
    cout << "Loaded " << songs.size() << " songs.\n" << endl;

    Trie trie;
    HashTable hashTable;

    cout << "Building Trie and HashTable..." << endl;
    for (auto& song : songs) {
        trie.insert(&song);   // Trie stores pointer
        hashTable.insert(song); // HashTable stores full copy
    }
    cout << "Build complete!\n" << endl;

    while (true) {
        cout << "\n--------------------------------------------------\n";
        cout << "                Music Search Application           \n";
        cout << "--------------------------------------------------\n";
        cout << "1. Search by Song Name\n";
        cout << "2. Search by Artist\n";
        cout << "3. Search by Genre\n";
        cout << "4. Compare Trie vs Hash Table Search Time\n";
        cout << "5. Exit\n";
        cout << "--------------------------------------------------\n";
        cout << "What would you like to do?: \n";

        int choice;
        cin >> choice;
        cin.ignore();

        // -------- EXIT ----------
        if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        }

        // -------- SONG SEARCH ----------
        if (choice == 1) {
            cout << "Enter Song Name: ";
            string query;
            getline(cin, query);

            bool foundTrie = trie.containsExact(normalize(query));
            vector<Song*> foundHash = hashTable.searchName(normalize(query));

            cout << "\nTrie:       " << (foundTrie ? "FOUND" : "NOT FOUND") << endl;
            cout << "HashTable:  " << (foundHash.empty() ? "NOT FOUND" : "FOUND") << endl;

            if (foundHash.size() != 0) {
                cout << "\nSong Details:\n";
                for (int i = 0; i < foundHash.size(); i++)
                {
                 foundHash[i]->display();
                }
            }
        }

        // -------- ARTIST SEARCH ----------
        else if (choice == 2) {
            cout << "Enter Artist Name: ";
            string query;
            getline(cin, query);
            query = normalize(query);

            cout << "\nSongs by this artist:\n";
             bool any = false;
             for (const auto& s : songs) {
                 if (normalize(s.getArtist()) == query) {
                     s.display();
                     any = true;
                 }
             }
             if (!any) cout << "No songs found for that artist.\n";
            //vector<Song*> foundHash = hashTable.searchArtist(normalize(query));
            //if (foundHash.size() != 0) {
                //for (int i = 0; i < foundHash.size(); i++)
                //{
                    //foundHash[i]->display();
                //}
            //}
           // else cout << "No songs found for that artist.\n";
        }

        // -------- GENRE SEARCH ----------
        else if (choice == 3) {
            cout << "Enter Genre: ";
            string query;
            getline(cin, query);
            query = normalize(query);

            cout << "\nSongs in this genre:\n";
             bool any = false;
             for (const auto& s : songs) {
                 if (normalize(s.getGenre()) == query) {
                     s.display();
                     any = true;
                 }
             }
             if (!any) cout << "No songs found for that genre.\n";
/*
            vector<Song*> foundHash = hashTable.searchGenre(normalize(query));
            if (foundHash.size() != 0) {
                for (int i = 0; i < foundHash.size(); i++)
                {
                    foundHash[i]->display();
                }
            }
            else cout << "No songs found for that genre.\n";
            */
        }

        // -------- PERFORMANCE COMPARISON ----------
        else if (choice == 4) {
            cout << "Enter Song Name to Compare Search Time: ";
            string query;
            getline(cin, query);

            auto t1 = chrono::high_resolution_clock::now();
            trie.containsExact(query);
            auto t2 = chrono::high_resolution_clock::now();
            auto trieTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

            t1 = chrono::high_resolution_clock::now();
            hashTable.searchName(query);
            t2 = chrono::high_resolution_clock::now();
            auto hashTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

            cout << "\nTrie Search Time:      " << trieTime << " microseconds\n";
            cout << "Hash Table Search Time: " << hashTime << " microseconds\n";
        }
        else {
            cin.clear();
            cin.ignore();
            cout << "Invalid selection. Try again.\n";
        }
    }

    return 0;
}

/*
using namespace std;

string normalize(const string& s) {
    string result = s;
    for (char& ch : result)
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    return result;
}

// Load songs from CSV
vector<Song> loadSongs(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        exit(1);
    }
    vector<Song> songs;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, artist, genre;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');

        songs.emplace_back(name, artist, genre);
    }

    return songs;
}

int main() {
    vector<Song> songs = loadSongs("songs_clean.csv");

    Trie trie;
    HashTable hashTable;

    for (auto& song : songs) {
        trie.insert(&song);   // Trie: pointer
        hashTable.insert(song); // HashTable: full copy
    }

    while (true) {
        cout << "\n--------------------------------------------------\n";
        cout << "                Music Search Application           \n";
        cout << "--------------------------------------------------\n";
        cout << "1. Search by Song Name\n";
        cout << "2. Search by Artist\n";
        cout << "3. Search by Genre\n";
        cout << "4. Compare Trie vs Hash Table Search Time\n";
        cout << "5. Exit\n";
        cout << "--------------------------------------------------\n";
        cout << "What would you like to do?: ";

        int choice;
        cin >> choice;
        //cin.ignore();

        //  EXIT
        if (choice == 5) {
            cout << "Goodbye! 🎶" << endl;
            break;
        }

        // SONG SEARCH
        if (choice == 1) {
            cout << "Enter Song Name: ";
            string query;
            getline(cin, query);

            bool foundTrie = trie.containsExact(query);
            Song* foundHash = hashTable.search(query);

            cout << "\nTrie:       " << (foundTrie ? "FOUND ✅" : "NOT FOUND ❌") << endl;
            cout << "HashTable:  " << (foundHash ? "FOUND ✅" : "NOT FOUND ❌") << endl;

            if (foundHash) {
                cout << "\nSong Details:\n";
                foundHash->display();
            }
        }

        // ARTIST SEARCH
        else if (choice == 2) {
            cout << "Enter Artist Name: ";
            string query;
            getline(cin, query);
            query = normalize(query);

            cout << "\nSongs by this artist:\n";
            bool any = false;
            for (const auto& s : songs) {
                if (normalize(s.getArtist()) == query) {
                    s.display();
                    any = true;
                }
            }
            if (!any) cout << "No songs found for that artist.\n";
        }

        //  GENRE SEARCH
        else if (choice == 3) {
            cout << "Enter Genre: ";
            string query;
            getline(cin, query);
            query = normalize(query);

            cout << "\nSongs in this genre:\n";
            bool any = false;
            for (const auto& s : songs) {
                if (normalize(s.getGenre()) == query) {
                    s.display();
                    any = true;
                }
            }
            if (!any) cout << "No songs found for that genre.\n";
        }

        // PERFORMANCE COMPARISON
        else if (choice == 4) {
            cout << "Enter Song Name to Compare Search Time: ";
            string query;
            getline(cin, query);

            auto t1 = chrono::high_resolution_clock::now();
            trie.containsExact(query);
            auto t2 = chrono::high_resolution_clock::now();
            auto trieTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

            t1 = chrono::high_resolution_clock::now();
            hashTable.search(query);
            t2 = chrono::high_resolution_clock::now();
            auto hashTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

            cout << "\nTrie Search Time:      " << trieTime << " microseconds\n";
            cout << "Hash Table Search Time: " << hashTime << " microseconds\n";
        }
        else {
            cout << "Invalid selection. Try again.\n";
        }
    }

    return 0;
}
*/