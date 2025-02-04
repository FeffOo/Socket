#include "res/common.h"

int main(int argc, char *argv[]){
    UserData user;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    tempError = connect(clientSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));
    

    if(tempError == -1){
        cout<<"Couldn't Connect to the server. Error N:"<<errno<<endl;
    }else{
        cout<<"Connection Established"<<endl;
    }
    if(argc == 0){
        cout<<"Insert an Username:";
        do{
            fgets(user.Username, MAX_USERNAME_LENGHT, stdin);
            if(user.Username[0] == '\n'){
                cout<<"Enter a valid username;"<<endl;
            }
        }while(strlen(user.Username) < 1);
        send(clientSocket, user.Username, strlen(user.Username), MSG_MORE);
        fgets(user.Password, MIN_PASSWD_LEN, stdin);
    }else{
        if(argc == 2){
            strcpy(user.Username, argv[2]);
            fgets(user.Password, MIN_PASSWD_LEN, stdin);
        }else if(argc == 4){
            strcpy(user.Username, argv[2]);
            strcpy(user.Password, argv[4]);
        }// CHANGE WITH A SWITCH
    }

    while(1){
        do{
            fgets(message, DEFAULT_BUFFER_SIZE, stdin);
            if(strlen(message) >= DEFAULT_BUFFER_SIZE || strlen(message) == -1){
                cout<<"Input Error"<<endl;
            }
        }while(strlen(message) >= DEFAULT_BUFFER_SIZE || strlen(message) == -1);
        if(message[0] == '!'){
            switch(str2int((const char*)message)){        
                case str2int("!help\n"):
                    cout<<"Help Menu"<<endl;
                    break;
                case str2int("!\n"):
                    cout<<"Invalid Command"<<endl;
                    break;
            }
        }else if(strlen(message) > 1){
            send(clientSocket, message, strlen(message), MSG_MORE);
            message[strcspn(message, "\n")] = ' ';
            message[0] = '\0';
        }
    
    }
    // closing socket
    close(clientSocket);

    return EXIT_SUCCESS;
}
