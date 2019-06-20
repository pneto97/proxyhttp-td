#include "httputils.hpp"

using namespace std;


int initServerSocket(string host){

    int serverFd;
    struct addrinfo hints, *res;
    int https = 0;
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
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if (getaddrinfo(host.c_str(), port, &hints, &res) != 0) {
    //if (getaddrinfo("linuxhowtos.org", porta, &hints, &res) != 0) {
        fprintf (stderr," Erro no formato do endereco do servidor! \n");
        exit (1);
    }
    
    
    
    if ((serverFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
        fprintf (stderr," Erro ao criar socket para o servidor! \n");
        exit (1);
    }

    if (connect(serverFd, res->ai_addr, res->ai_addrlen) < 0) {
        fprintf (stderr," Erro ao conectar com o servidor ! \n");
        exit (1);
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
        memset(sendBuf, 0 , sizeof(sendBuf));
        strcpy(sendBuf,data.c_str());
        
        //string a(sendBuf);
        //cout << a << endl;
        while(sentTotal < sendSize){
            int sent = 0;
            if((sent = send(sock, (void*) (sendBuf + sentTotal), sendSize - sentTotal,0)) <0){
                
                fprintf(stderr,"Erro ao enviar ao servidor!\n");
                exit(1);
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
        memset(sendBuf, 0 , sizeof(sendBuf));
        memcpy(sendBuf,data,size);
        //strcpy(sendBuf,data.c_str());
        
        //string a(sendBuf);
        //cout << a << endl;
        while(sentTotal < size){
            int sent = 0;
            if((sent = send(sock, (void*) (sendBuf + sentTotal), size - sentTotal,0)) < 0){
                
                fprintf(stderr,"Erro ao enviar ao servidor!\n");
                exit(1);
            }

            sentTotal = sentTotal + sent;
        }
        free(sendBuf);
        return sentTotal;
}

