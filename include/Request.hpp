#pragma once

#include <string>
#include <sstream>
#include <algorithm>

class Request{
    public:
        std::string getUri();
        std::string getVersion(); 
        std::string getMethod();
        std::string getHost();
        std::string getRequest();
        std::string getFileRequestSemBarra();
        bool isPersistentConnection();
        int getClientSockFd();
   //     string getHeaderFields();
        Request(std::string req, int sockfd); //parse request
        Request();
    private:
        int sockfd;
        std::string method;
        std::string uri;
        std::string version;
        std::string host;
        std::string req;
    //    string headerFields; 
};