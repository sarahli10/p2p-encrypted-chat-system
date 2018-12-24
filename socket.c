#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"

/*
 Function:	setupServer
 Purpose:	this function sets up the server socket 
            (or one of the peer's sockets)
 Parameters:
 in:		none
 return:	the peer's connection
 */
int setupServer() {
    int scServer, scClient;
    struct sockaddr_in saServer, saClient;
    int i, addrSize;

    // create socket
    scServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (scServer < 0) {
        printf("Couldn't open server socket\n");
        exit(-1);
    }

    // setup server address
    memset(&saServer, 0, sizeof(saServer));
    saServer.sin_family = AF_INET;
    saServer.sin_addr.s_addr = htonl(INADDR_ANY);
    saServer.sin_port = htons((unsigned short) SERVER_PORT);

    // bind listen socket
    i = bind(scServer, (struct sockaddr *) &saServer, sizeof(saServer));
    if (i < 0) {
        printf("Couldn't bind server socket\n");
        exit(-1);
    }

    // listen
    i = listen(scServer, 5);
    if (i < 0) {
        printf("Server couldn't listen\n");
        exit(-1);
    }

    // wait for connection request
    printf("Waiting for connection request...\n");
    addrSize = sizeof(saClient);
    scClient = accept(scServer, (struct sockaddr *) &saClient, &addrSize);
    if (scClient < 0) {
        printf("Server couldn't accept the connection\n");
        exit(-1);
    }
    printf("... connection accepted\n\n\n");

    // close server socket
    close(scServer);

    // return the peer connection
    return scClient;
}

/*
 Function:	setupClient
 Purpose:	this function sets up the client socket 
            (or one of the peer's sockets)
 Parameters:
 in:		the IP address the user entered
 return:	the peer's connection
 */
int setupClient(const char *serverIp) {
    int scClient;
    struct sockaddr_in saClient;
    int i;

    // create socket
    scClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (scClient < 0) {
        printf("Couldn't open client socket\n");
        exit(-1);
    }

    // setup client address
    memset(&saClient, 0, sizeof(saClient));
    saClient.sin_family = AF_INET;
    saClient.sin_addr.s_addr = inet_addr(serverIp);
    saClient.sin_port = htons((unsigned short) SERVER_PORT);

    // connect to server
    printf("Connecting to server...\n");
    i = connect(scClient, (struct sockaddr *) &saClient, sizeof(saClient));
    if (i < 0) {
        printf("Client could not connect\n");
        exit(-1);
    }
    printf("... connected\n\n\n");

    // return the peer connection
    return scClient;
}