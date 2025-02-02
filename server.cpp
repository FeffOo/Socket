#include "res/common.h"



int main(int argc, char *argv[]){
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));

    listen(serverSocket, 5);
    
    clientSocket = accept(serverSocket, nullptr, nullptr);

    do{
        recv(clientSocket, message, sizeof(message), 0);

        if(message[0] != '\n' || message[0] != '0'){
            cout << "Message from client: " << message;
            memset(message , 0, sizeof(message)); //clear the entire string
        }else{
            cout << "ERROR";
        }
    
    }while(errno == 0);

    close(serverSocket);


    return EXIT_SUCCESS;
}