#include "httpServer.hpp"

HttpServer::HttpServer(/* args */)
{
}

HttpServer::~HttpServer()
{
}

Request HttpServer::openServer(short portNumber, short numberOfParalelConnections) {

    int sockfd, clientsockfd;
    int clilen = sizeof(struct sockaddr);
    int opt = 1;
    char buffer[MAX_BUFFER_SIZE];
    std::string request = "";
    std::string reply = "";


    struct sockaddr_in serv_addr;
    struct sockaddr cli_addr;


    sockfd = socket(AF_INET, SOCK_STREAM, 0); //cria o socket

    if(sockfd < 0){
        throw "Socket não foi criado" ;
    }

    // Set the socket options
	// if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
	// 	&opt, sizeof(opt))) {

    //     fprintf(stderr,"Erro na configuracao do socket\n");
	// }

    memset(&serv_addr , 0 , sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;     // ip4 family 
  	serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1 
 	serv_addr.sin_port = htons(portNumber); 

    if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        close(sockfd);
        throw "Erro no binding";
    }

    if(listen(sockfd, numberOfParalelConnections) < 0){
        close(sockfd);
        throw "Erro no listen";
    }

    clientsockfd = accept(sockfd, &cli_addr, (socklen_t*) &clilen);

    if(clientsockfd < 0){
        close(sockfd);
        throw "Erro ao aceitar o request";
    }

    int recvd;

    // Melhorar a condicao desse loop
    while( request.find("\r\n\r\n") == std::string::npos ){
        
        memset(buffer, 0 , sizeof(buffer));

        recvd = recv(clientsockfd, buffer , MAX_BUFFER_SIZE, 0);

        if(recvd < 0) {
            close(sockfd);
            throw "Erro ao receber requisicao"; 
        } else if ( recvd == 0) {
            break;
        }

        buffer[recvd] = '\0';
        request.append(buffer);
    }
    close(clientsockfd);
    std::cout << request << std::endl;

    return Request(request);
}
