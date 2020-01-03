/*
 * Copyright (C) 2019 ulmeslj@miamioh.edu
 * 
 */
#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include "Movie.h"

/** A fixed HTML header that is printed at the beginning of output to ensure
 * the output is displayed correct.
 */
const std::string HTMLHeader = 
    "Content-Type: text/html\r\n\r\n"
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "<link type='text/css' rel='stylesheet' href='movie.css'/>\n"
    "</head>\n"
    "<body>";

/** A fixed HTML footer that is printed at the end of output to ensure
 * correct HTML formatting
 */
const std::string HTMLFooter = "</body>\n</html>";

/** Convenience method to decode HTML/URL encoded strings.

    This method must be used to decode query string parameters
    supplied along with GET request.  This method converts URL encoded
    entities in the from %nn (where 'n' is a hexadecimal digit) to
    corresponding ASCII characters.

    \param[in] str The string to be decoded.  If the string does not
    have any URL encoded characters then this original string is
    returned.  So it is always safe to call this method!

    \return The decoded string.
*/
std::string url_decode(std::string str) {
    // Decode entities in the from "%xx"
    size_t pos = 0;
    while ((pos = str.find_first_of("%+", pos)) != std::string::npos) {
        switch (str.at(pos)) {
            case '+': str.replace(pos, 1, " ");
            break;
            case '%': {
                std::string hex = str.substr(pos + 1, 2);
                char ascii = std::stoi(hex, nullptr, 16);
                str.replace(pos, 3, 1, ascii);
            }
        }
        pos++;
    }
    return str;
}
std::string helper(std::string title, std::string genres, 
        std::string startYear, std::string endYear) {
    if ((title != "") && (genres == "") && (startYear == "") && 
            (endYear == "")) {
        return "WHERE title LIKE '%%%0%%'";
    } else if ((title == "") && (genres != "") && (startYear == "") && 
            (endYear == "")) {
        return "WHERE genres LIKE '%%%1%%'";
    } else if ((title != "") && (genres != "") && (startYear == "") && 
            (endYear == "")) {
        return "WHERE title LIKE '%%%0%%' AND genres LIKE "
                "'%%%1%%'";
    } else if ((title == "") && (genres == "") && (startYear != "") && 
            (endYear == "")) {
        return "WHERE year >= %2;";
    } else if ((title == "") && (genres == "") && (startYear == "") && 
            (endYear != "")) {
        return "WHERE year <= %3;";
    } else if ((title != "") && (genres == "") && (startYear == "") && 
            (endYear != "")) {
        return "WHERE title LIKE '%%%0%%' AND year <= %3;";
    } else {
        return "WHERE title LIKE '%%%0%%' AND genres LIKE '%%%1%%' AND "
                "year >= %2 AND year <= %3;";
    }
}

void helper2(std::string title, std::string genres, std::string startYear,
        std::string endYear) {
    mysqlpp::Connection Movies("cse278s19", "os1.csi.miamioh.edu", "cse278s19", 
            "rbHkqL64VpcJ2ezj");
    
    // create a query
    mysqlpp::Query query = Movies.query();
    query << "SELECT id, title, year, genres, imdb_id, rating, raters FROM "
            << "Movies ";
    
    std::string addOn = helper(title, genres, startYear, endYear);
    query << addOn;
    query.parse();
    mysqlpp::StoreQueryResult result = query.store(title, genres, startYear, 
            endYear);
    std::cout << HTMLHeader << "\n";
    for (size_t i = 0; i < result.size(); i++) {
        Movie m = Movie(result[i][0], result[i][1].c_str(), 
                result[i][2], result[i][3].c_str(), result[i][4], 
                result[i][5], result[i][6]);
        m.printAsHtml(std::cout);
    }
    std::cout << HTMLFooter;
}
int main() {
    std::string param1, value1, param2, value2, param3, value3, param4, value4;
    std::getline(std::cin, param1, '=');
    std::getline(std::cin, value1, '&');
    std::getline(std::cin, param2, '=');
    std::getline(std::cin, value2, '&');
    std::getline(std::cin, param3, '=');
    std::getline(std::cin, value3, '&');
    std::getline(std::cin, param4, '=');
    std::getline(std::cin, value4, '\n');
    std::string title = value1;
    title = (value1 == "") ? "" : url_decode(value1);
    std::string genres = value2;
    genres = (value2 == "") ? "" : url_decode(value2);
    std::string startYear = value3;
    startYear = (value3 == "") ? "" : url_decode(value3);
    std::string endYear = value4;
    endYear = (value4 == "") ? "" : url_decode(value4);
    helper2(title, genres, startYear, endYear);
    return 0;
}

