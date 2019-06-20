#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>

#include <string>
#include <iostream>
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

int initServerSocket(std::string host);

int sendData(std::string data, int sock);

int sendDataChar(char* data, int size, int sock);
