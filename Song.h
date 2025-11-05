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
    Song(const string& SongName, const string& SongArtist, const string& SongGenre)
        : name(SongName), artist(SongArtist), genre(SongGenre) {}

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
    void setName(const string& NewName) {
        name = NewName;
    }
    // Setter for artist
    void setArtist(const string& NewArtist) {
        artist = NewArtist;
    }
    // Setter for genre
    void setGenre(const string& NewGenre) {
        artist = NewGenre;
    }
    // Display function
    void display() const {
        cout << "Song: " << name << " by " << artist << endl;
    }
};