//
// Created by ricar on 11/3/2025.
//
#ifndef PROJECT2_SONG_H
#define PROJECT2_SONG_H
#include <iostream>
#include <string>
using namespace std;

class Song {
private:
    string name;
    string artist;
    string genre;

public:
    // Constructor
    Song(const string& songName, const string& songArtist, const string& songGenre)
        : name(songName), artist(songArtist), genre(songGenre) {}

    // Getter for name
    string getName() const {
        return name;
    }

    // Getter for artist
    string getArtist() const {
        return artist;
    }

    // Getter for genre
    string getGenre() const {
        return genre;
    }

    // Setter for name
    void setName(const string& newName) {
        name = newName;
    }
    // Setter for artist
    void setArtist(const string& newArtist) {
        artist = newArtist;
    }

    // Setter for genre
    void setArtist(const string& newGenre) {
        genre = newGenre;
    }

    // Display function
    void display() const {
        cout << "Song: " << name << " by " << artist << endl;
    }
};

#endif //PROJECT2_SONG_H