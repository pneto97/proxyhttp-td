#include "Response.hpp"

Response::Response( std::string response )
{
    this->createResponse(response);
}

Response::Response()
{
}

Response::~Response()
{
}

VALOR_RETORNO Response::createResponse(std::vector<char> response) {
    this->binaryResponse = response;
}

VALOR_RETORNO Response::createResponse(std::string response) {

    this->response = response;

    std::stringstream s(response);
    std::string word;

    s >> word;
    this->protocol = word;

    s >> word;
    this->reponseCode = word;

    s >> word;
    this->messageReponse = word;

    return VALOR_RETORNO::SUCCES_ON_EXECUTION;
}

std::string Response::getResponse() {
    return this->response;
}

std::string Response::getProtocol() {
    return this->protocol;
}

std::string Response::getResponseCode() {
    return this->reponseCode;
}

std::string Response::getMessageReponse() {
    return this->messageReponse;
}

std::vector<char> Response::getBinaryResponse() {
    return this->binaryResponse;
}