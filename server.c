#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include "Practical.h"

// the numer of clients that can connect at any one time 
#define BACKLOG 10

int main(int argc, char **argv){
    if ( argc != 2 ){
         DieWithUserMessage("Parameter(s)", "<Server Port>");
    }
    
    // server port
    in_port_t servPort = atoi(argv[1]);
    // number of client connections
    int num_clients = 0;

    // create the socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(servPort);
    
    // bind the socket
    bind(sockfd, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
    printf("[+]BINDING\n");

    // listen for the client
    listen(sockfd, BACKLOG);
    printf("[-]LISTENING FOR THE CLIENT\n");

    // event loop
    int i = 1;
    while(i){
        int client_socket = accept(sockfd, NULL, NULL);
        num_clients++;
        time_t currentTime;
        time(&currentTime);
        printf("Client %d is request the time at %s", num_clients, ctime(&currentTime));
        // Send the time to the client 
        send(client_socket, ctime(&currentTime), 30, 0);
    }
}
