#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

//For ThreadPool
#include <thread>
#include <chrono>

//Need to install manually in windows and linux --> https://www.geeksforgeeks.org/introduction-to-sqlite/
#include <sqlite3.h>

#include "common.cpp"

#ifdef _WIN32
    #include <Winsock.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#define DEFAULT_PORT 6969
#define DEFAULT_N_CONN 5 //NUMBER OF USER CONNECTED
#define DEFAULT_BUFFER_SIZE 1024

#define MAX_USERNAME_LENGHT 16
#define MIN_PASSWD_LEN 8

#define ESCAPE_KEY 27 // ESC key

using namespace std;
using namespace chrono_literals;
using uShort8 = uint8_t;

//trasforma una stringa in un numero intero usando un metodo chiamato "hashing
constexpr unsigned int str2int(const char* str, int h = 0);

typedef struct{
    char Username[MAX_USERNAME_LENGHT];
    char Password[MIN_PASSWD_LEN];
}UserData;

struct sockaddr_in serverAddress;

char message[DEFAULT_BUFFER_SIZE] = {0};
char dbLocalPath[] = {"res/users.db"};

bool isUp;
bool isUserLogIn;

int clientSocket;
int serverSocket;

uShort8 tempError;
