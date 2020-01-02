/*
 * Copyright (C) 2019 ulmeslj@miamioh.edu
 * 
 * 
 * Base case: If command is exit stop. Otherwise, print values for columns (in the
specified order) for all movies. See sample outputs for example queries and
expected outputs. The URL will always begin with http://. However, the
machine name and the path to the file on the server will vary.
 * 
 Additional Functionality: Optionally print entries that match a given condition
– i.e., a column containing a given value in it. The condition will always be in the
format where colName like "substring". The words "where" and
"like" are fixed and will never change. See sample outputs for example queries
and expected outputs.
 * 
 * Each query should retrieve the data from the server at the specified "url". Do not
store it in a local file.
 * 
 * Use the split method in the start code to break the input query into words.
 * 
6. It would be handy to write a find method to locate index of fixed words such as:
"from", "where", etc.
 * 
7. Use the HTTP client (a tcp::iostream) from lecture slides and lab exercises
(as starting point) to download data from the given URL.
 * 
8. Recollect that that the supplied Movie class can extract data from an I/O stream.
9. See the getCol method in Movie.h.
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


// A couple of namespaces to streamline code
using namespace std;
using namespace boost::asio::ip;

// Alias to a vector-of-strings
using StrVec = std::vector<std::string>;

std::string queryString;

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
int  find(StrVec wordList, const char a) {
    for(int i = 0; (i < wordList.size()); i ++) {
        if (wordList[i] == a) {
            return i;
        }
    } 
}
void process(std::istream& is, std::ostream& os){
    Movie mov;
    int fromIndex = find(queryString, "from");

    while (is) {
        std::string output;
        StrVec wordList = is >> mov;
        for (int i = 1; (i < fromIndex); i++) {
            output.append(mov.getCol(StrVec[i]));
            output.append(move.getCol(" "));
        }
        std::cout << output;
    }
}
int main(){

    cin >> queryString;
    if(queryString == "exit"){
        return 0;
    }
    split(queryString);
    int fromIndex = find(queryString, "from");
    std::string url = StrVec[fromIndex+1];

    tcp::iostream stream(url, "80");
    if(!stream.good()){
        std::cout << "Error connecting!\n";
    }
    process(stream, stream);
    return 0;
}



    





