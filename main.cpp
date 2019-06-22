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

        Response resp = httpClient.makeRequest(req, false);
        if(!resp.getResponse().empty()) {
            sendData(resp.getResponse(), req.getClientSockFd());
        }
        // std::cout << resp.getResponse() << std::endl;

        close(req.getClientSockFd());
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

    serverSock = httpServer.openServer(4331, 1);

    while(n) {
        std::thread s1 (executeTask, serverSock, &httpServer);
        std::thread s2 (executeTask, serverSock, &httpServer);
        
        s1.join();
        s2.join();
        n--;
    }

    close(serverSock);
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
