#include "res/common.cpp"

int main(int argc, char* argv[]){

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    while(1){
        fgets(message, DEFAULT_BUFFER_SIZE, stdin);
        if(message[0] != '\n' && message[0] != '!'){
            send(clientSocket, message, strlen(message), 0);
        }else if(message[0] == '!'){
            switch(str2int(message)){
                case str2int("!help"):
                    //HELP MENU SIMILAR TO MAN
                    break;
                case str2int("!disconnect"):
                    send(clientSocket, "!disconnect", strlen(message), 0);
                    break;

                default:
                    cout<<"Invalid Command"<<endl;
                    break;
            }

        }
    
    }
    close(clientSocket);
    return EXIT_SUCCESS;
}
