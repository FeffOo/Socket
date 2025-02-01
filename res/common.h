#pragma once
#include <iostream>
#include <unistd.h>

#ifdef _WIN32
    #include <Winsock.h>
#else
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

using namespace std;

#define DEFAULT_SERVER_PORT 6969
#define DEFAULT_BUFFER_SIZE 1024

#define ESCAPE_KEY 27 // ESC key

sockaddr_in serverAddress;

int clientSocket;
int serverSocket;