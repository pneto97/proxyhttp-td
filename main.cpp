#include "Request.hpp"
#include "constants.hpp"
#include "httpClient.hpp"
#include "httpServer.hpp"
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>

void fileToVector(std::vector<std::string>& vec, std::string fileName){

    std::string curLine = "";

    std::ifstream infile(fileName);

    while(std::getline(infile, curLine)){
        if(curLine != "\n")
            vec.push_back(curLine);
    }

}

void sendErrorToClient(Request req, std::string page){

    std::string request;
        std::ifstream requestExample (page);

        if( requestExample.is_open() ){
            std::stringstream temp;
            temp << requestExample.rdbuf();
            request = temp.str();
            sendData(request, req.getClientSockFd());
        } else {
            std::cout << "Mate, this is impossible to fix" << std::endl;
        }
        requestExample.close();
}

bool findDenyTerms(Response resp, std::vector<std::string>& denyterms ){

    std::string respString = "";
    for(int i = 0 ; i < resp.getBinaryResponse().size() ; i++){

        respString.push_back(resp.getBinaryResponse()[i]);
    }
    //procura deny terms
    for(std::vector<std::string>::iterator it = denyterms.begin() ; it != denyterms.end() ; it++){
        if(respString.find(*it) != std::string::npos){
            //deny term encontrado
            //sendErrorToClient(req, "../response_errors/ReponseErrorUnauthorizedDeny.txt");
            return true;
        }
    }

    return false;
}

void executeTask(int serverSock, HttpServer *httpServer){
    Request req;

   
    std::vector<std::string> whitelist;
    std::vector<std::string> blacklist;
    std::vector<std::string> denyterms;
    bool whitelisted = false;
    bool blacklisted = false;
    //bool hasDenyTerms = false;

    fileToVector(whitelist , "../whitelist.txt");
    fileToVector(blacklist , "../blacklist.txt");
    fileToVector(denyterms , "../denyterms.txt");

    try
    {
        req = httpServer->acceptRequest( serverSock, true);
    }
    catch(char const *e)
    {
        close(serverSock);
        std::cerr << e << std::endl;
    }

    if(std::find(whitelist.begin(), whitelist.end(), req.getHost()) != whitelist.end()){
        whitelisted = true;
    }

    if(std::find(blacklist.begin(), blacklist.end(), req.getHost()) != blacklist.end()){
        blacklisted = true;

        std::cout << "This website is blacklisted" << std::endl;

        sendErrorToClient(req, "../response_errors/ReponseErrorUnauthorized.txt");

        exit(1);
    }

    HttpClient httpClient;

    Response resp = httpClient.makeRequest(req, -1, true);


    if (!resp.getBinaryResponse().empty()) {
        
        if(whitelisted == false){
            printf("Não está no whitelist\n");

            if(findDenyTerms(resp, denyterms)){
                sendErrorToClient(req, "../response_errors/ReponseErrorUnauthorizedDeny.txt");
                printf("Deny term encontrado.\n");
                exit(1);
            }     
        }

        sendDataChar(resp.getBinaryResponse().data(), resp.getBinaryResponse().size(), req.getClientSockFd());
    } else {
        
        sendErrorToClient(req, "../response_errors/ReponseErrorNotFound.txt");     
    }

    bool cont = req.isPersistentConnection();
    // Que codigo feio, jesus santo
    while ( cont ) {
        try {
            req = httpServer->recvFromPrevious ( req.getClientSockFd(), true );

            if(std::find(whitelist.begin(), whitelist.end(), req.getHost()) != whitelist.end()){
                whitelisted = true;
            }

            if(std::find(blacklist.begin(), blacklist.end(), req.getHost()) != blacklist.end()){
                blacklisted = true;

                std::cout << "This website is blacklisted" << std::endl;

                sendErrorToClient(req, "../response_errors/ReponseErrorUnauthorized.txt");

                exit(1);
            }


            if (req.getRequest().empty() || req.getMethod() == "CONNECT") break;

            resp = httpClient.makeRequest(req, resp.getServerFd(), false);
            if (!resp.getBinaryResponse().empty()) {
                
                if(whitelisted == false){
                    printf("Não está no whitelist\n");

                    if(findDenyTerms(resp, denyterms)){
                        sendErrorToClient(req, "../response_errors/ReponseErrorUnauthorizedDeny.txt");
                        printf("Deny term encontrado.\n");
                        exit(1);
                    }     
                }

                sendDataChar(resp.getBinaryResponse().data(), resp.getBinaryResponse().size(), req.getClientSockFd());
            } else {

                sendErrorToClient(req, "../response_errors/ReponseErrorNotFound.txt");
            }
        } catch(char const *e) {
            cont = false;
            std::cerr << e << std::endl;
        }
    }

    if (!resp.getBinaryResponse().empty()) close (resp.getServerFd());
    if (!req.getRequest().empty()) close( req.getClientSockFd() );
    std::cout << "Terminou thread" << std::endl;
}

int main(int argc, char *argv[]){

    // std::string request;

    // std::ifstream requestExample ("../RequestExample.txt");

    // if( requestExample.is_open() ){
    //     std::stringstream temp;
    //     temp << requestExample.rdbuf();
    //     request = temp.str();
    // }
    // requestExample.close();

    // std::cout << request << "Proceed? 0 - NO, 1 - Yes" << std::endl;
    // int val;
    // std::cin >> val;
    // if (val == 0)
    // {
    //     return 0;
    // }

    int serverSock, n = 2;
    HttpServer httpServer;

    serverSock = httpServer.openServer(4331, 10);



    while(n) {
        std::thread s1 (executeTask, serverSock, &httpServer);
        std::thread s2 (executeTask, serverSock, &httpServer);
        // std::thread s3 (executeTask, serverSock, &httpServer);
        // std::thread s4 (executeTask, serverSock, &httpServer);
        // std::thread s5 (executeTask, serverSock, &httpServer);
        // std::thread s6 (executeTask, serverSock, &httpServer);
        // std::thread s7 (executeTask, serverSock, &httpServer);
        // std::thread s8 (executeTask, serverSock, &httpServer);
        // std::thread s9 (executeTask, serverSock, &httpServer);
        // std::thread s10 (executeTask, serverSock, &httpServer);

        s1.join();
        s2.join();
        // s3.join();
        // s4.join();
        // s5.join();
        // s6.join();
        // s7.join();
        // s8.join();
        // s9.join();
        // s10.join();

        n--;
    }

 


    close(serverSock);
    return 0;
}
