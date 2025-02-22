#include "res/common.cpp"
#include "res/ThreadPool.cpp"

//Need to install manually in windows and linux --> https://www.geeksforgeeks.org/introduction-to-sqlite/
#include "res/sqlquerys.h"
#include <sqlite3.h>

#define DEFAULT_SHELL_BUFFER 128

static void closeServer();
static void clientListen(int clientSocket);
static void usrRegistr(char* usr);
static void* srvShell(void *);

static int callback(void* data, int argc, char** argv, char** azColName);

sqlite3 *db;
sqlite3_stmt *stmt;

int main(int argc, char* argv[]){

    ThreadPool Client_Thread(DEFAULT_N_CONN + 2);

    if(sqlite3_open_v2(dbLocalPath, &db, 0, nullptr) == SQLITE_OPEN_READWRITE){
        cerr<<"ERRORE:"<<sqlite3_errmsg(db);
        return EXIT_FAILURE;
    }
    if(sqlite3_exec(db, TABLE_INIT, callback, 0, 0) == SQLITE_OPEN_READWRITE){
        cerr<<"ERRORE:"<<sqlite3_errmsg(db);
        return EXIT_FAILURE;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, message, sizeof(message));
    
    if(serverSocket == 0){
        cerr<<"Errore nella creazioen del socket"<<endl;
        closeServer();
        return EXIT_FAILURE;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        cerr<<"Errore di Binding"<<endl;
        closeServer();
        return EXIT_FAILURE;
    }
        
    listen(serverSocket, DEFAULT_N_CONN);
    cout<<"In Attesa di connessione"<<endl;
    socklen_t srvAddrSize = sizeof(serverAddress);
    

    if((serverSocket = accept(serverSocket, (struct sockaddr*)&serverAddress, &srvAddrSize)) < 0){
        cerr<<"Errore nella accettazione del Socket";
        closeServer();
        return EXIT_FAILURE;
    }

    //ACCESSO  
    recv(serverSocket, message, DEFAULT_BUFFER_SIZE, 0);
    if(strstr(message, "register") != NULL && message[0] == '!'){
        usrRegistr(message);
    }else if(strcmp(message, "!login") == 1){
        do{
            if(sqlite3_prepare_v2(db, UserLogCrd, -1, &stmt, nullptr) != SQLITE_OPEN_READWRITE){
                cerr<<"Errore nella iniz. della query UserLogCrd:"<<sqlite3_errmsg(db);
            }  
            recv(serverSocket, message, DEFAULT_BUFFER_SIZE, 0);
            sqlite3_bind_text(stmt, 1, message, -1, SQLITE_STATIC);
            recv(serverSocket, message, DEFAULT_BUFFER_SIZE, 0);
            sqlite3_bind_text(stmt, 2, message, -1, SQLITE_STATIC);

            if(sqlite3_step(stmt) != SQLITE_DONE){
                cerr<<"Errore nella query"<<sqlite3_errmsg(db);
                strcpy(message, "false");
                send(serverSocket, message, strlen(message), 0);
            }else 
                isUserLogIn = true;
        }while(isUserLogIn = true);
    }

    strcpy(message, "true");
    send(serverSocket, message, strlen(message), 0);
    
    cout<<"Connessione Effettuata"<<endl;
    Client_Thread.enqueue(clientListen, clientSocket);
    

    sqlite3_close(db);
    close(serverSocket);

    return EXIT_SUCCESS;
}

static void clientListen(int clientSocket){
    while(1){
        recv(clientSocket, message, sizeof(message), 0);
        if(strlen(message) > 0){
            if(strcmp(message, "!disconnect") == true){
                closeServer();
                break;
            }
            cout<<"[THREAD:"<<this_thread::get_id()<<"]Client:"<<message;
            memset(message, 0, DEFAULT_BUFFER_SIZE);     
        }
    }
}

static void closeServer(){
    sqlite3_close(db);
    close(serverSocket);
}

static void usrRegistr(char* msg){
    char* tmpUsrn = strsegm(msg);
    char* tmpPswd = strsegm(msg);
    
    sqlite3_bind_text(stmt, 1, tmpUsrn, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tmpPswd, -1, SQLITE_STATIC);
    
    cout<<"LOG: usr Registration"<<endl;

    if(sqlite3_step(stmt) != SQLITE_DONE){
        cerr<<"Errore nella query "<<sqlite3_errmsg(db)<<endl;
        strcpy(message, "false");
        send(serverSocket, message, strlen(message), 0);
    }

    memset(tmpUsrn, 0, sizeof(tmpUsrn));
    memset(tmpPswd, 0, sizeof(tmpPswd));

}

static void* srvShell(void *){
    char serverShell[DEFAULT_SHELL_BUFFER];

    while(1){
        sqlite3_exec(db, TABLE_INIT, callback, NULL, NULL);
    
        //ADMIN INPUT
        do{
            fgets(serverShell, DEFAULT_SHELL_BUFFER, stdin);
        }while(serverShell[0] == '\n');
        switch(str2int(serverShell)){
            case str2int("!shutdown\n"):
                closeServer();
                return nullptr;
            default:
                cout<<"Invalid Command"<<endl;
                break;
        }
        memset(serverShell, 0, DEFAULT_SHELL_BUFFER);
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