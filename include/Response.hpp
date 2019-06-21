#pragma once

#include <string>
#include <sstream>
#include "constants.hpp"

class Response
{
private:
    /* data */
    std::string response;
    std::string protocol;
    std::string reponseCode;
    std::string messageReponse;
    // std::string ;
    // std::string protocol;
public:
    Response( std::string );
    Response( );
    ~Response();

    VALOR_RETORNO makeRequest(std::string);
    std::string getResponse();
    std::string getProtocol();
    std::string getResponseCode();
    std::string getMessageReponse();
};
