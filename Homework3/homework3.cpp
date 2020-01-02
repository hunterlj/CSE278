/* 
 * File:   exercise6.cpp
 * Author: ulmeslj
 *
 * Copyright (C) 2019 ulmeslj@miamiOH.edu
 */

#include <unordered_map>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "Movie.h"

using namespace std;

// A shortcut to a map of Movie. The key into this map is the 
// movie's numeric ID
using MovieMap = std::unordered_map<int, Movie>;

/**
 * Method to movie entries from a given file into an 
 * unordered map.
 * 
 * @param filePath Path to the file from where data is to be read.
 * @return An unordered map containing the data.
 */
MovieMap load(const std::string& filePath) {
    // Create the entry for the file to be read
    std::ifstream data(filePath);
    if (!data.good()) {
        throw std::runtime_error("Unable to read file " + filePath);
    }
    // Create the map to be populated and returned
    MovieMap db;
    // Load movie information into the DB by reading 
    // entry-by-entry and then add them to the unordered_map using
    // operator[].  Use the ID of the movie as the key.
    Movie move;  // temporary object
    while (data >> move) {
        // Implement rest of the method here. 
        auto moveId = move.getMovieID();
        db[moveId] = move;       
    }
    // Return the map of movies back
    return db;
}

/**
 * Read ID and print information about a movie, if the ID is valid.
 * 
 * This method uses the find method in unordered_map to quickly
 * find if the ID is valid. Note that the find method can be used
 * only to search based on the key/index (or "first") for the
 * unordered_map.  This method has O(1) time complexity!
 * 
 * @param db The unordered_map of movies to be used by this method.
 */
void findMovie(const MovieMap& db, int moveId) {
    // Prompt and obtain ID from the user.
    
    // Use the find method to find entry and print it. The find method
    // is covered in lecture slides!
    if (db.find(moveId) != db.end()) {
        std::cout << db.at(moveId) << std::endl;
    } else {
        std::cout << "Move with ID " << moveId << " not found in database.\n";
    } 
}
/**
 * This method search for a given sub-string in all movie entries
 * and prints matching entries. Since this method has to iterate
 * over each entry it has a O(n) time complexity.
 * 
 * @param db The unordered_map of movies to be used by this method.
 */
void searchMovie(const MovieMap& db, std::string strSearch) {
    // Search the full info of a movie to see if data is in there.
    // use the range-based for loop (as discussed in lecture slides)!
    for (const auto& entry : db) {
        // For each entry convert the value (i.e., second) for each element 
        // using the to_string method and then use std::string::find method 
        // to see if searchStr is a substring. If so, print the value.
        std::string info = to_string(entry.second);
        std::cout << info;
        if (info.find(strSearch) != std::string::npos) {
            std::cout << entry.second << std::endl;
        }
    }
}
/*
 * A simple main method to load and list of movies into a given 
 */
int main(int argc, char** argv) {
    // First load the person database from a given file.
    MovieMap db = load("./movies_db.txt");
    std::cout << "Enter a command: ";
    std::string command;
    std::string strSearch;
    std::cin >> command >> quoted(strSearch);

    if (command == "search") {
        searchMovie(db, strSearch);
    }
    if (command == "find") {
        stringstream in(strSearch);
        int moveId = 0;
        in >> moveId;
        findMovie(db, moveId);
    }

    return 0;
}





