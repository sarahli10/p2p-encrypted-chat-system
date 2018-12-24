#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"
#include "enc.h"

// forward references
int speaking(int socket);
int listening(int socket);

int main(int argc, char const *argv[]) {
    int scConnect;
    int turns = 0;
    int quit;

    // check for what user entered
    if (argc == 1) {    // running as a server
        scConnect = setupServer();
    } else {    // running as a client
        scConnect = setupClient(argv[1]);
        turns = !turns;
    }

    // chatting
    // take turns speaking and listening
    while (1) {
        if (turns) {
            quit = speaking(scConnect);
        } else {
            quit = listening(scConnect);
        }
        if (quit)
            break;
        turns = !turns;
    }

    // close the peer connection
    close(scConnect);

    return 0;
}

/*
 Function:	speaking
 Purpose:	this function takes a message from one user, 
            encrypts the message, and sends it to the other user
 Parameters:
 in:		the user's socket
 return:	signal for quitting, 1 if user wants to quit, 
            0 otherwise
 */
int speaking(int socket) {
    char inStr[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    char encStr[BUFFER_SIZE];

    printf("Your msg ->  ");
    fgets(inStr, sizeof(inStr), stdin);
    inStr[strlen(inStr) - 1] = 0;
    strcpy(buffer, inStr);

    // encrypt the buffer
    // ok to use strlen here, because it's not encrypted yet
    encryptStr(buffer, encStr, strlen(buffer));

    // send the encrypted message
    send(socket, encStr, strlen(encStr), 0);
    
    if (strcmp(inStr, "quit") == 0)
        return 1;
    return 0;
}

/*
 Function:	listening
 Purpose:	this function receives an encrypted message 
            from one user, decrypts it, and outputs both 
            the encrypted and decrypted messages
 Parameters:
 in:		the user's socket
 return:	signal for quitting, 1 if user wants to quit, 
            0 otherwise
 */
int listening(int socket) {
    int bytesRcv;
    char buffer[BUFFER_SIZE];
    char decStr[BUFFER_SIZE];

    // receive encrypted message
    printf("... waiting to receive ...\n");
    bytesRcv = recv(socket, buffer, sizeof(buffer), 0);
    buffer[bytesRcv] = 0;

    // decrypt the message
    // don't use strlen here, like Christine said
    encryptStr(buffer, decStr, bytesRcv);

    // display the encrypted and decrypted message
    printf("Received ->  %s\n", buffer);    // encrypted
    printf("Received ->  %s\n\n", decStr);  // decrypted

    if (strcmp(decStr, "quit") == 0)
        return 1;
    return 0;
}