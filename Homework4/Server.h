/* 
 * File:   Server.h
 * Copyright (C) 2019 ulmeslj@miamiOH.edu
 */

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>

/** A simple Server class that can act as a web-server to process
    simple HTTP GET requests.

    NOTE: Do not modify the public interface for this class. However,
    you may add any private or protected members for your solution.
*/
class Server {
public:
    /**
     * The constructor to have this class operate as a server on a given port.
     * 
     */
    Server();
    
    /**
     * The destructor (should have empty body).
     */
    virtual ~Server();
    
    virtual std::string fileType(const std::string str);
    
    virtual void notGood(const std::string filePath);
    
    virtual void httpResponse(const std::string header, const int fileSize, 
        const std::string type, const std::string filePath); 
    
    
    /**
     * Serves one connection from 1 client by processing HTTP request
     * (ignoring headers) and responding to the request with contents 
     * of a file (specified in the GET request).
     * 
     * @param is The input stream from where the client request is to be read.
     * @param os The output stream where the response is to be written.
     */
    virtual void serveClient(std::istream& is = std::cin, 
                             std::ostream& os = std::cout);
    /**
     * Runs the program as a server processing incoming connections/requests
     * for ever.
     * 
     * This method (along with helper methods) performs the following tasks
     *      1. Creates a server port and prints the port it is listening on.
     *      2. Accepts connections from clients and processes requests
     *         by calling the serveClient() method in this class.
     */
    virtual void runServer();   
};
#endif /* SERVER_H */