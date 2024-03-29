#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

#include "constants.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <vector>
#include <fstream>

int initServerSocket(std::string host);

int sendData(std::string data, int sock);

int sendDataChar(char* data, int size, int sock);

void sendErrorToClient(Request req, std::string page);

bool findDenyTerms(Response resp, std::vector<std::string>& denyterms );