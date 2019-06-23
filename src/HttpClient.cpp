#include "httpClient.hpp"

HttpClient::HttpClient(/* args */)
{
}

HttpClient::~HttpClient()
{
}

Response HttpClient::makeRequest( Request reques, int sock , bool verbose ) {
    int serverFd;
    std::vector<char> reply;
    Response resp;
    Cache cache;

    resp = cache.getFromCache(reques);
    if (!resp.getBinaryResponse().empty()) {
        return resp;
    }
    // Abrir socket para realizar a requisicao
    try {
        serverFd = initServerSocket(reques.getHost());
    } catch( char const *e ) {
        std::cerr << e << '\n';
        return resp;
    }        

    // Enviar requisicao ao servidor
    sendData(reques.getRequest(), serverFd);

    ssize_t received = 0;
    char recvBuf[MAX_BUFFER_SIZE];

    while((received = recv(serverFd, recvBuf, MAX_BUFFER_SIZE, 0)) > 0 ) {
        recvBuf[received] = '\0';
        reply.insert(reply.end(), recvBuf, recvBuf + received);
        //   fputs(recvBuf,stdout);
        // sendDataChar(recvBuf, received, clientsockfd );
        // memset(recvBuf, 0 , sizeof(recvBuf));
    }

    if(received == -1){
        std::cerr << "Erro ao receber do servidor. \n" << std::endl;
        return resp;
    }

    // Depois de recebido tudo, fechar conexao

    resp.createResponse(reply, serverFd);
    if (verbose)
    {
        std::cout << "Recebido do servidor" << std::endl;
        for (auto i : resp.getBinaryResponse())
        {
            std::cout << i;
        }
        
    }

    if (cache.lancarNaCache(resp, reques) == VALOR_RETORNO::ERROR)
    {
        std::cerr << "Erro ao escrever na cache. \n" << std::endl;
    }
    
    close(serverFd);
    return resp;
}
