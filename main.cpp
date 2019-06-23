#include "Request.hpp"
#include "constants.hpp"
#include "httpClient.hpp"
#include "httpServer.hpp"
#include <fstream>
#include <thread>

void executeTask(int serverSock, HttpServer *httpServer){
    Request req;

    try
    {
        req = httpServer->acceptRequest( serverSock, true);
    }
    catch(char const *e)
    {
        close(serverSock);
        std::cerr << e << std::endl;
    }

    HttpClient httpClient;

    Response resp = httpClient.makeRequest(req, -1, false);
    if (!resp.getBinaryResponse().empty()) {
        sendDataChar(resp.getBinaryResponse().data(), resp.getBinaryResponse().size(), req.getClientSockFd());
    } else {
        std::string request;
        std::ifstream requestExample ("../ReponseErrorExample.txt");

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

    bool cont = req.isPersistentConnection();
    // Que codigo feio, jesus santo
    while ( cont ) {
        try {
            req = httpServer->recvFromPrevious ( req.getClientSockFd(), true );
            if (req.getRequest().empty()) break;

            resp = httpClient.makeRequest(req, resp.getServerFd(), false);
            if (!resp.getBinaryResponse().empty()) {
                sendDataChar(resp.getBinaryResponse().data(), resp.getBinaryResponse().size(), req.getClientSockFd());
            } else {
                std::string request;
                std::ifstream requestExample ("../ReponseErrorExample.txt");

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
    int serverSock, n = 10;
    HttpServer httpServer;

    serverSock = httpServer.openServer(4331, 10);

    while(n) {
        std::thread s1 (executeTask, serverSock, &httpServer);
        std::thread s2 (executeTask, serverSock, &httpServer);
        std::thread s3 (executeTask, serverSock, &httpServer);
        std::thread s4 (executeTask, serverSock, &httpServer);
        std::thread s5 (executeTask, serverSock, &httpServer);
        std::thread s6 (executeTask, serverSock, &httpServer);
        std::thread s7 (executeTask, serverSock, &httpServer);
        std::thread s8 (executeTask, serverSock, &httpServer);
        std::thread s9 (executeTask, serverSock, &httpServer);
        std::thread s10 (executeTask, serverSock, &httpServer);

        s1.join();
        s2.join();
        s3.join();
        s4.join();
        s5.join();
        s6.join();
        s7.join();
        s8.join();
        s9.join();
        s10.join();

        n--;
    }

    close(serverSock);
    return 0;
}
