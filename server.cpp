#include "res/common.h"

//Il suo compito principale è stampare i dati della riga, mostrando i nomi delle colonne e i valori associati.
static int callback(void* data, int argc, char** argv, char** azColName);

const char TABLE_INIT[] = "CREATE TABLE users( id_user INT NOT NULL PRIMARY KEY AUTO_INCREMENT, username CHAR(16), passwd CHAR(16) NOT NULL);";
char UserCheck[] = "FROM users SELECT * WHERE username";

int main(int argc, char *argv[]){
    
    sqlite3 *db;

    int tempError;

    tempError = sqlite3_open(dbLocalPath, &db);
    if(tempError != SQLITE_OK){
        cout<<"SQL error: "<<errno<<endl;
        return -1;
    }else{
        cout<<"Database Connected"<<endl;
        sqlite3_exec(db, TABLE_INIT, callback, NULL, NULL); //CREAZIONE DI UNA TABELLA
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));

    tempError = listen(serverSocket, 5);
    if(tempError == -1){
        cout<<"Error while listening. Error N:"<<errno<<endl;
    }else{
        cout<<"Socket is now listening."<<endl;
    }

    clientSocket = accept(serverSocket, nullptr, nullptr);
    if(isUserLogIn == false){
        recv(clientSocket, message, sizeof(message), 0);
        sqlite3_exec(db, (const char *)strcat(UserCheck, message), callback, NULL, NULL);
    }
    while(recv(clientSocket, message, sizeof(message), 0) != 0){
        if(message[0] != '\n' || message[0] != '0'){
            cout << "Message from client: " << message;
            memset(message , 0, sizeof(message)); //clear the entire string
        }else{
            cout << "Error reciving the message";
        }
    }

    close(serverSocket);
    sqlite3_close(db);

    return EXIT_SUCCESS;
}

//Il suo compito principale è stampare i dati della riga, mostrando i nomi delle colonne e i valori associati.
static int callback(void* data, int argc, char** argv, char** azColName){
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
  
    cout<<endl; 
    return 0; 
}