#include "Request.hpp"

Request::Request(std::string req, int sockfd){
    this->sockfd = sockfd;

    this->req = req; 

    std::stringstream s(req);
    std::string word;

    s >> word;
    this->method = word;
    s >> word;
    this->uri = word;
    s >> word;
    this->version = word;
    
    this->host = "";
    while( s >> word){
        if(word == "Host:"){
            s >> word;
            this->host = word;
            break;
        }
    }
}

Request::Request()
{
}

std::string Request::getUri(){
    return this->uri;
}

std::string Request::getVersion(){
    return this->version;
}

std::string Request::getMethod(){
    return this->method;
}

std::string Request::getHost(){
    return this->host;
}

std::string Request::getRequest(){
    return this->req;
}

std::string Request::getFileRequestSemBarra() {
    std::string temp = "";
    temp += this->uri;
    std::replace (temp.begin(), temp.end(), '/' , '-');
    std::replace (temp.begin(), temp.end(), ':' , '-');
    return temp;
}

int Request::getClientSockFd() {
    return this->sockfd;
}

bool Request::isPersistentConnection() {
    return this->req.find("Connection: keep-alive") != this->req.npos;
}