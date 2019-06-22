#include "httputils.hpp"

using namespace std;


int initServerSocket(string host){

    int serverFd;
    struct addrinfo hints, *res;
    // int https = 0;
    //string porta = "80";
    //const char* port = "80";
    //const char*portHttps = "443";
    const char* port = "80";
    // const char* portHttps = "443";

    
    // if(host.find(":443") != std::string::npos){
    //     https = 1;
    //     cout << "EH HTTPS" << endl;
    // }
    //cout << host << endl;
    // if(strstr(host,":443") != NULL){
    //     printf("HTTPS\n");
    // }


    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::cout << host << "|abcd" << std::endl;
    if (getaddrinfo(host.c_str(), port, &hints, &res) != 0) {
    //if (getaddrinfo("linuxhowtos.org", porta, &hints, &res) != 0) {
        throw "Erro ao tentar buscar informações sobre o servidor!";
    }
    
    if ((serverFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        freeaddrinfo(res);
        throw "Erro ao criar socket para o servidor!";
    }

    if (connect(serverFd, res->ai_addr, res->ai_addrlen) < 0) {
        close(serverFd);
        freeaddrinfo(res);
        throw "Erro ao conectar com o servidor!";
    }

    freeaddrinfo(res);
//    free(addr);
    
    return serverFd;
}


int sendData(string data, int sock){

        int sendSize = data.size();
        int sentTotal = 0;
        //char sendBuf[MAX_BUFFER_SIZE];
        char* sendBuf = (char*) malloc((sendSize+1)*sizeof(char)); 
        // memset(sendBuf, 0 , sizeof(sendBuf));
        sendBuf[sendSize] = '\0';
        strcpy(sendBuf, data.c_str());
        
        //string a(sendBuf);
        //cout << a << endl;
        while(sentTotal < sendSize){
            int sent = 0;
            if((sent = send(sock, (void*) (sendBuf + sentTotal), sendSize - sentTotal,0)) <0){
                
                std::cerr << "Erro ao enviar ao/para servidor/cliente!\nFechando Socket" << std::endl;
                close(sock);
                free(sendBuf);
                return -1;
            }

            sentTotal = sentTotal + sent;
        }
        free(sendBuf);
        return sentTotal;
}

int sendDataChar(char* data, int size, int sock){

        int sentTotal = 0;
        //char sendBuf[MAX_BUFFER_SIZE];
        char* sendBuf = (char*) malloc((size+1)*sizeof(char)); 
        // memset(sendBuf, 0 , sizeof(sendBuf));
        memcpy(sendBuf,data,size);
        //strcpy(sendBuf,data.c_str());
        
        //string a(sendBuf);
        //cout << a << endl;
        while(sentTotal < size){
            int sent = 0;
            if((sent = send(sock, (void*) (sendBuf + sentTotal), size - sentTotal,0)) < 0){
                std::cerr << "Erro ao enviar ao servidor!" << std::endl;
                return -1;
            }

            sentTotal = sentTotal + sent;
        }
        free(sendBuf);
        return sentTotal;
}

