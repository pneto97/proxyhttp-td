#include "httpClient.hpp"

HttpClient::HttpClient(/* args */)
{
}

HttpClient::~HttpClient()
{
}

int HttpClient::makeRequest( Request reques, bool verbose = false ) {
    int sockfd, clientsockfd;
    int opt = 1;
    char buffer[MAX_BUFFER_SIZE];

    // Abrir socket para realizar a requisicao
    int serverFd = initServerSocket(reques.getHost());

    // Enviar requisicao ao servidor
    sendData(reques.getRequest(), serverFd);

    ssize_t received = 0;
    char recvBuf[MAX_BUFFER_SIZE];
    std::string reply;

    while((received = recv(serverFd, recvBuf, MAX_BUFFER_SIZE, 0)) > 0 ) {
        recvBuf[received] = '\0';
        reply.append(recvBuf);
        //   fputs(recvBuf,stdout);
        // sendDataChar(recvBuf, received, clientsockfd );
        memset(recvBuf, 0 , sizeof(recvBuf));
    }

    if(received == -1){
        std::cerr << "Erro ao receber do servidor. \n" << std::endl;
        exit (1); 
    }

    // Depois de recebido tudo, fechar conexao

    if (verbose)
    {
        std::cout << "Recebido do servidor" << std::endl << reply << std::endl;
    }
    

    close(serverFd);
}
