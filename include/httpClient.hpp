#include <sys/socket.h>
#include <iostream>
#include <sys/socket.h>
#include "constants.hpp"
#include <netinet/in.h>

#include "httputils.hpp"

class HttpClient
{
private:
    /* data */
public:
    HttpClient(/* args */);
    ~HttpClient();
    int makeRequest( Request , bool);
};
