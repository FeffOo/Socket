#include "res/common.h"

int main(int argc, char *argv[]){
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    
    connect(clientSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));

    while(1){
        fgets(message, DEFAULT_BUFFER_SIZE, stdin);
        send(clientSocket, message, strlen(message), MSG_MORE);
        message[strcspn(message, "\n")] = ' ';
        message[0] = '\0';
    }
    // closing socket
    close(clientSocket);


    return EXIT_SUCCESS;
}