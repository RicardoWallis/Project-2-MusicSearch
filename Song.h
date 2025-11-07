//
// Created by ricar on 11/3/2025.
//
#pragma once
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

    //Overload == operator to compare songs against themselves
    bool operator==(const Song& other) const {
        return name == other.name && artist == other.artist;
    }

    // Display function
    void display() const {
        cout << "Song: " << name << " by " << artist << " [" << genre << "]" << endl;
    }
};
