CC      = g++
CFLAGS  = -g
SERVERFLAGS     = -lsqlite3 -Llsqlquerys.h -LlThreadPool.cpp
RM      = rm -rf

default: all

all: client server

client: client.cpp
	$(CC) $(CFLAGS) -o client client.cpp

server:server.cpp
	$(CC) $(CFLAGSs) -o server server.cpp $(SERVERFLAGS)

clean veryclean:
	$(RM) server
	$(RM) client
