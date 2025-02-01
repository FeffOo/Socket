#include "res/common.h"

int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

int main(){
    serverAddress.sin_addr = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

     bind(serverSocket, (struct sockaddr*)&serverAddress,
         sizeof(serverAddress));

    // listening to the assigned socket
    listen(serverSocket, 5);

    // accepting connection request
    int clientSocket
        = accept(serverSocket, nullptr, nullptr);

    // recieving data
    char buffer[DEFAULT_BUFFER_SIZE] = { 0 };
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Message from client: " << buffer
              << endl;

    // closing the socket.
    close(serverSocket);


    return EXIT_SUCCESS;
}