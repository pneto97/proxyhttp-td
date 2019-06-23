#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include "constants.hpp"
#include <netinet/in.h>

#include "httputils.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "cache.hpp"

class HttpClient
{
private:
    /* data */
public:
    HttpClient(/* args */);
    ~HttpClient();
    Response makeRequest( Request reques, int sock=-1 , bool verbose = false );
};
