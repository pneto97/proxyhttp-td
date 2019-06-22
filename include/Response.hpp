#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "constants.hpp"

class Response
{
private:
    /* data */
    std::vector<char> binaryResponse;
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

    VALOR_RETORNO createResponse(std::string);
    VALOR_RETORNO createResponse(std::vector<char>);
    std::string getResponse();
    std::vector<char> getBinaryResponse();
    std::string getProtocol();
    std::string getResponseCode();
    std::string getMessageReponse();
};
