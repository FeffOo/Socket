#include "res/common.h"

//Il suo compito principale è stampare i dati della riga, mostrando i nomi delle colonne e i valori associati.
static int callback(void* data, int argc, char** argv, char** azColName);

const char TABLE_INIT[] = "CREATE TABLE users( id_user INT NOT NULL PRIMARY KEY AUTO_INCREMENT, username CHAR(16) NOT NULL, passwd CHAR(16) NOT NULL, islogin BOOLEAN NOT NULL DEFAULT 0);";

//QUERY
string UPDATE_USER_STATUS = "UPDATE users SET islogin = 0 WHERE id_users = ?;";
string UsernameCheck = "SELECT COUNT(*) FROM users WHERE username = ?;";
string PasswdCheck = "SELECT COUNT(*) FROM passwd WHERE passwd = ?;";

int main(int argc, char *argv[]){
    
    sqlite3 *db;
    sqlite3_stmt* stmt;

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

    //LOGIN
    if(sqlite3_prepare_v2(db, UsernameCheck.c_str(), -1, &stmt, nullptr) == SQLITE_OK ){ 
        //USERNAME CHECK
        string tempString = message;
        recv(clientSocket, message, sizeof(message), 0);
        sqlite3_bind_text(stmt, 1, tempString.c_str(), -1,  SQLITE_STATIC);

        if(sqlite3_step(stmt) == SQLITE_ROW &&
            sqlite3_prepare_v2(db, PasswdCheck.c_str(), -1, &stmt, nullptr) == SQLITE_OK ){
            //PASSWD CHECK
            recv(clientSocket, message, sizeof(message), 0);
            sqlite3_bind_text(stmt, 1, tempString.c_str(), -1,  SQLITE_STATIC);
            
            if(sqlite3_step(stmt) == SQLITE_ROW){
                //SET STATUS login = true to the user
                isUserLogIn = true;
                sqlite3_bind_text(stmt, 1, to_string(isUserLogIn).c_str(), -1, SQLITE_STATIC);   
                sqlite3_step(stmt);
            }else{
                cout<<"[PASSWD]An error as occured:"<<sqlite3_errmsg(db)<<endl;
                return EXIT_FAILURE;
            }
        }else{
            cout<<"[USER]An error as occured:"<<sqlite3_errmsg(db)<<endl;
            return EXIT_FAILURE;
        }    
    }else{
        cout<<"[QUERY]An Error as occured"<<sqlite3_errmsg(db)<<endl;
        return EXIT_FAILURE;
    }

    //COMMUNITCATION LOOP
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
    sqlite3_finalize(stmt);

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