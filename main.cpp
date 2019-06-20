#include "httputils.hpp"
#include "constants.hpp"
#include "httpClient.hpp"

int main(int argc, char *argv[]){

    std::string req = "GET / HTTP/1.1\r\n";
    req += "Host: www.pudim.com.br\r\n";
    req += "Connection: keep-alive\r\n";
    req += "Upgrade-Insecure-Requests: 1\r\n";
    req += "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36\r\n";
    req += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n";
    req += "Accept-Encoding: gzip, deflate\r\n";
    req += "Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\n";
    req += "Cookie: _ga=GA1.3.427403873.1544050820\r\n\r\n";

    Request myReq(req);
    
    HttpClient httpClient;
    
    httpClient.makeRequest(myReq, true);

    return 0;

//     int sockfd, clientsockfd;
//     int clilen = sizeof(struct sockaddr);
//     int opt = 1;
//     char buffer[MAX_BUFFER_SIZE];
//     const string ok_msg = "HTTP/1.0 200 OK\r\n\r\n";
//     string request = "";
//     string reply = "";


//     struct sockaddr_in serv_addr;
//     struct sockaddr cli_addr;

//     if(argc<2){
//         fprintf(stderr,"Insira uma porta!\n");
//         exit(1);
//     }

//     sockfd = socket(AF_INET, SOCK_STREAM, 0); //cria o socket

//     if(sockfd < 0){

//         fprintf(stderr,"Socket não foi criado\n");
//         return 1;
//     }

//     // Set the socket options
// 	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
// 		&opt, sizeof(opt))) {

//         fprintf(stderr,"Erro na configuracao do socket\n");
// 		exit(1);
// 	}

//     memset(&serv_addr , 0 , sizeof(serv_addr));

//     int portno = atoi(argv[1]);
//     serv_addr.sin_family = AF_INET;     // ip4 family 
//   	serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1 
//  	serv_addr.sin_port = htons(portno); 

//     if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
//         fprintf(stderr,"Erro no binding");
//         return 1; 
//     }

//     if(listen(sockfd, 100) < 0){

//         fprintf(stderr,"Erro no listen\n");
//         return 1; 
//     }
    
//     while(1){

//         int received_bits = 0;
//         int recvd = 0;
//         request = "";
//         reply = "";

//         clientsockfd = accept(sockfd, &cli_addr, (socklen_t*) &clilen);

//         if(clientsockfd < 0){
//             fprintf(stderr,"Erro ao aceitar o request\n");
//         }

//         while(request.find("\r\n\r\n") == std::string::npos){
            
//             memset(buffer, 0 , sizeof(buffer));

//             recvd = recv(clientsockfd, buffer , MAX_BUFFER_SIZE, 0);

//             if(recvd < 0){
//                 fprintf(stderr,"Erro ao receber");
//                 exit(1); 
//             } else if( recvd == 0){
//                 break;
//             } else{
//                 received_bits += recvd;

//                 buffer[recvd] = '\0';
//             }

//             request.append(buffer);
//         }

//         Request myReq(request);

        
//         // cout << myReq.getMethod() << endl;
//         // cout <<  myReq.getUri() << endl;
//         // cout << myReq.getVersion() << endl;
//         // cout << myReq.getHost() << endl;
//         // cout << myReq.getRequest() << endl; 

//         std::cout << endl << myReq.getRequest() << endl << endl;

//         const char *connection_established = "HTTP/1.1 200 Connection established\r\n\r\n";
//         //se for https
//         if(myReq.getMethod() == "CONNECT"){
//             //sendData(ok_msg, clientsockfd);
//             //cout << "https" << endl;
//             //send(clientsockfd, connection_established, 39, 0);

//             continue;
//         }
//         int serverFd = initServerSocket(myReq.getHost());
        
        
//         sendData(myReq.getRequest(), serverFd);
        
//         int recvTotal = 0;
//         int received = 0;
//         char recvBuf[MAX_BUFFER_SIZE];
//         memset(recvBuf, 0 , sizeof(recvBuf));

//     //     struct timeval timeout;      
//     //     timeout.tv_sec = 10;
//     //     timeout.tv_usec = 0;

//     // setsockopt (serverFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
//     //             sizeof(timeout));

//         while((received = recv(serverFd, recvBuf, MAX_BUFFER_SIZE, 0)) > 0){
//     //        printf("%d ",received);
//             recvBuf[received] = '\0';
//             reply.append(recvBuf);
//          //   fputs(recvBuf,stdout);
//             sendDataChar(recvBuf, received, clientsockfd );
//             memset(recvBuf, 0 , sizeof(recvBuf));
//         }

//         if(received < 0){
//             fprintf (stderr,"Erro ao receber do servidor. \n");
//             exit (1); 
//         }

//         //cout << reply;
        
//         //sendDataChar(char* data, int size, int sock){
//        // sendData(reply,newsockfd);

//         std::cout << endl;
        
// //        cout << request << endl;
// /*
//         for(int i = 0 ; i < request.size() ; i++){
//             if(request[i] == '\n'){
//                 cout << "\\n";
//                 cout << endl;
//             } else if(request[i] == '\r'){
//                 cout << "\\r";
//             } else{
//                 cout << request[i];
//             }
//         }*/

         

//         close(clientsockfd);
//         close(serverFd);
//     }
    
//     close(sockfd);

}
