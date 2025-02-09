#include "res/common.cpp"
#include "res/ThreadPool.cpp"

//Need to install manually in windows and linux --> https://www.geeksforgeeks.org/introduction-to-sqlite/
#include "res/sqlquerys.h"
#include <sqlite3.h>

static void clientListen(int clientSocket);
static void SQLQueryMenu(void *);

static int callback(void* data, int argc, char** argv, char** azColName);

int main(int argc, char* argv[]){

    ThreadPool Client_Thread(DEFAULT_N_CONN + 2);
    Client_Thread.enqueue(SQLQueryMenu, nullptr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, message, sizeof(message));
    
    if(serverSocket == 0){
        perror("Errore nella creazioen del socket");
        return EXIT_FAILURE;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        perror("Errore di binding");
        return EXIT_FAILURE;
    }
        
    listen(serverSocket, DEFAULT_N_CONN);
    cout<<"In Attesa di connessione"<<endl;
    socklen_t srvAddrSize = sizeof(serverAddress);
    

    if((clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddress, &srvAddrSize)) < 0){
        perror("Errore nella accettazione");
        return EXIT_FAILURE;
    }

    cout<<"Connessione Effettuata"<<endl;
    Client_Thread.enqueue(clientListen, clientSocket);


    close(serverSocket);
    return EXIT_SUCCESS;
}

static void clientListen(int clientSocket){
    while(1){
        recv(clientSocket, message, sizeof(message), 0);
        if(strlen(message) > 0){
            if(strcmp(message, "!disconnect") == true){
                break;
            }
            cout<<"[THREAD:"<<this_thread::get_id()<<"]Client:"<<message;
            memset(message, 0, DEFAULT_BUFFER_SIZE);     
        }
    }
}

static void SQLQueryMenu(void *){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char serverShell[DEFAULT_BUFFER_SIZE];
    if(sqlite3_open(dbLocalPath, &db) != SQLITE_OK){
        perror("DB Error");
    }
    while(1){
        sqlite3_exec(db, TABLE_INIT, callback, NULL, NULL);
    
        //ADMIN INPUT
        do{
            fgets(serverShell, DEFAULT_BUFFER_SIZE, stdin);
        }while(serverShell[0] == '\n');
        switch(str2int(serverShell)){
            default:
                cout<<"Invalid Command"<<endl;
                break;
        }
        memset(serverShell, 0, DEFAULT_BUFFER_SIZE);
    }
}

static int callback(void* data, int argc, char** argv, char** azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}