#pragma once

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "constants.hpp"
#include "Request.hpp"

class HttpServer
{
private:
    /* data */
public:
    HttpServer(/* args */);
    ~HttpServer();

    Request openServer( short portNumber, short numberOfParalelConnections );
};