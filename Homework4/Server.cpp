/* 
 * File:   Server.cpp
 * Copyright (C) 2019 ulmeslj@miamiOH.edu
 */

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Server.h"

// The default file to return for "/"
const std::string header;
const std::string str;
const std::string type;
const std::string msg;
    
Server::Server() {
    // Nothing to be done in the constructor (for now).
}

Server::~Server() {
    // Nothing to be done in the destructor.
}
std::string Server::fileType(const std::string str) {
    if (str == "html") {
        return "text/html";
    }
    if (str == "png") {
        return "image/png";
    }
    if (str == "jpeg") {
        return "image/jpeg";
    } else {
        return "text/plain";
    }
}
void Server::notGood(const std::string filePath) {
    const std::string header = "404 Not Found";
    const std::string msg = "The following file was not found: " + filePath;
    const int fileSize = msg.length();
    httpResponse(header, fileSize, type, filePath);
    std::cout << msg;
}
/**
 * Sets up http response
 * @param header
 * @param fileSize
 * @param type
 */
void Server::httpResponse(const std::string header, const int fileSize,
        const std::string type1, const std::string filePath) {
    std::cout << "HTTP/1.1 " << header << "\r\n"
            << "Server: SimpleServer\r\n"
            << "Content-Length: " << fileSize << "\r\n"
            << "Connection: Close\r\n"
            << "Content-Type: " << type << "\r\n\r\n";
    std::ifstream inFile(filePath);
    std::string fileLine;
    while (std::getline(inFile, fileLine) && ((fileLine != "") 
            && (fileLine != "\r"))) {
        std::cout << fileLine << std::endl;
    }
}
// Implement rest of your methods for your class here. Ensure all of your
// methods are associated with the the Server class!
void Server::serveClient(std::istream& is, std::ostream& os) {
    // First extract request line from client
    // The line is in the form GET Path_to_file HTTP/1.1
    std::string line;
    std::getline(is, line);
    const size_t spc1Pos = line.find('/');
    const size_t spc2Pos = line.find(' ', spc1Pos);
    const std::string filePath = line.substr(spc1Pos, spc2Pos - spc1Pos);
    const size_t spc3Pos = filePath.find('.');
    const std::string str = filePath.substr(spc3Pos + 1);
    const std::string type = fileType(str);
    if (filePath == "/") {
        const std::string filePath = "index.html";
    }
    std::ifstream inFile(filePath);
    if (!inFile.good()) {
        notGood(filePath);
    }
    inFile.seekg(0, std::ios::end); 
    const int fileSize = inFile.tellg();
    inFile.seekg(0);   
    httpResponse("200 OK", fileSize, type, filePath);
}
/**
 * Runs the program as a server processing incoming connections/requests
 * for ever.
 * 
 * This method (along with helper methods) performs the following tasks
 *      1. Creates a server port and prints the port it is listening on.
 *      2. Accepts connections from clients and processes requests
 *         by calling the serveClient() method in this class.
 */
void Server::runServer() {
    using namespace boost::asio;
    using namespace boost::asio::ip;
    io_service service;
    // Create end point. 0 == Pick any free port.
    tcp::endpoint myEndpoint(tcp::v4(), 0);
    // Create a socket that accepts connections
    tcp::acceptor server(service, myEndpoint);
    std::cout << "Listening on port " << server.local_endpoint().port()
              << std::endl;
    // Process client connections one-by-one...forever
    while (true) {
        tcp::iostream client;
        // Wait for a client to connect
        server.accept(*client.rdbuf());
        // Process information from client.
        serveClient(client, client);
    }
}

