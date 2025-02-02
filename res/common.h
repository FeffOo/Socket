#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "common.cpp"

#ifdef _WIN32
    #include <Winsock.h>
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#define DEFAULT_PORT 6969
#define DEFAULT_BUFFER_SIZE 1024

#define ESCAPE_KEY 27 // ESC key

using namespace std;
using uShort8 = uint8_t;

struct sockaddr_in serverAddress;
 
char message[DEFAULT_BUFFER_SIZE] = {0};

bool isUp;
int clientSocket;
int serverSocket;