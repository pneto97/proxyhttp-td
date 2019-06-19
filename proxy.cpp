#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "httputils.h"

#define HTTP_OK_MSG	"HTTP/1.1 200 OK\r\n\r\n"
#define MAX_BUFFER_SIZE 10000

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
            if((sent = send(sock, (void*) (sendBuf + sentTotal), size - sentTotal,0)) <0){
                
                fprintf(stderr,"Erro ao enviar ao servidor!\n");
                exit(1);
            }

            sentTotal = sentTotal + sent;
        }
        free(sendBuf);
        return sentTotal;
}

int main(int argc, char *argv[]){
    
    int sockfd, newsockfd;
    int clilen = sizeof(struct sockaddr);
    int opt = 1;
    char buffer[MAX_BUFFER_SIZE];
    const string ok_msg = "HTTP/1.0 200 OK\r\n\r\n";
    string request = "";
    string reply = "";


    struct sockaddr_in serv_addr;
    struct sockaddr cli_addr;

    if(argc<2){
        fprintf(stderr,"Insira uma porta!\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //cria o socket

    if(sockfd < 0){

        fprintf(stderr,"Socket não foi criado\n");
        return 1;
    }

    // Set the socket options
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		&opt, sizeof(opt))) {

        fprintf(stderr,"Erro na configuracao do socket\n");
		exit(1);
	}

    memset(&serv_addr , 0 , sizeof(serv_addr));

    int portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;     // ip4 family 
  	serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1 
 	serv_addr.sin_port = htons(portno); 

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        fprintf(stderr,"Erro no binding");
        return 1; 
    }

    if(listen(sockfd, 100) < 0){

        fprintf(stderr,"Erro no listen\n");
        return 1; 
    }
    
    while(1){

        int received_bits = 0;
        int recvd = 0;
        request = "";
        reply = "";

        newsockfd = accept(sockfd, &cli_addr, (socklen_t*) &clilen);

        if(newsockfd < 0){
            fprintf(stderr,"Erro ao aceitar o request\n");
        }

        while(request.find("\r\n\r\n") == std::string::npos){
            
            memset(buffer, 0 , sizeof(buffer));

            recvd = recv(newsockfd, buffer , MAX_BUFFER_SIZE, 0);

            if(recvd < 0){
                fprintf(stderr,"Erro ao receber");
                exit(1); 
            } else if( recvd == 0){
                break;
            } else{
                received_bits += recvd;

                buffer[recvd] = '\0';
            }

            request.append(buffer);
        }

        Request myReq(request);

        
        // cout << myReq.getMethod() << endl;
        // cout <<  myReq.getUri() << endl;
        // cout << myReq.getVersion() << endl;
        // cout << myReq.getHost() << endl;
        // cout << myReq.getRequest() << endl; 

        cout << endl << myReq.getRequest() << endl << endl;

        const char *connection_established = "HTTP/1.1 200 Connection established\r\n\r\n";
        //se for https
        if(myReq.getMethod() == "CONNECT"){
            //sendData(ok_msg, newsockfd);
            //cout << "https" << endl;
            //send(newsockfd, connection_established, 39, 0);

            continue;
        }
        int serverFd = initServerSocket(myReq.getHost());
        
        
        sendData(myReq.getRequest(), serverFd);
        
        int recvTotal = 0;
        int received = 0;
        char recvBuf[MAX_BUFFER_SIZE];
        memset(recvBuf, 0 , sizeof(recvBuf));

    //     struct timeval timeout;      
    //     timeout.tv_sec = 10;
    //     timeout.tv_usec = 0;

    // setsockopt (serverFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
    //             sizeof(timeout));

        while((received = recv(serverFd, recvBuf, MAX_BUFFER_SIZE, 0)) > 0){
    //        printf("%d ",received);
            recvBuf[received] = '\0';
            reply.append(recvBuf);
         //   fputs(recvBuf,stdout);
            //sendDataChar(recvBuf, received,newsockfd );
            memset(recvBuf, 0 , sizeof(recvBuf));
        }

        if(received < 0){
            fprintf (stderr,"Erro ao receber do servidor. \n");
            exit (1); 
        }

        //cout << reply;
        
        //sendDataChar(char* data, int size, int sock){
        sendData(reply,newsockfd);

        cout << endl;
        
//        cout << request << endl;
/*
        for(int i = 0 ; i < request.size() ; i++){
            if(request[i] == '\n'){
                cout << "\\n";
                cout << endl;
            } else if(request[i] == '\r'){
                cout << "\\r";
            } else{
                cout << request[i];
            }
        }*/

         

        close(newsockfd);
        close(serverFd);
    }
    
    close(sockfd);

}
