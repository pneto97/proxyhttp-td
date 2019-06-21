#pragma once

#include <string>
#include <sstream>

class Request{
    public:
        std::string getUri();
        std::string getVersion(); 
        std::string getMethod();
        std::string getHost();
        std::string getRequest();
   //     string getHeaderFields();
        Request(std::string req); //parse request
    private:
        std::string method;
        std::string uri;
        std::string version;
        std::string host;
        std::string req;
    //    string headerFields; 
};