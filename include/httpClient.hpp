#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include "constants.hpp"
#include <netinet/in.h>

#include "httputils.hpp"
#include "Response.hpp"
#include "Request.hpp"

class HttpClient
{
private:
    /* data */
public:
    HttpClient(/* args */);
    ~HttpClient();
    Response makeRequest( Request, bool);
};
