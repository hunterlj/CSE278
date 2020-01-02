/* 
 * File:   homework5.cpp
 * Copyright (C) 2019 ulmeslj@miamioh.edu
 * 
 */

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "Movie.h"

// A couple of namespaces to streamline code
using namespace std;
using namespace boost::asio::ip;

// Alias to a vector-of-strings
using StrVec = std::vector<std::string>;

/** Helper method to split a given string into separate words based on spaces.
 * Note that this method does the following 1 extra operations:
 *    2. Removes all commas (',') characters
 */
StrVec split(std::string str) {
    // Change all ',' to spaces
    std::replace(str.begin(), str.end(), ',', ' ');
    // Now use a istringstream to extract words into a vector
    std::istringstream is(str);
    StrVec wordList;
    std::string word;
    while (is >> std::quoted(word)) {
        wordList.push_back(word);
    }
    // Return the list of words back to the caller.
    return wordList;
}
