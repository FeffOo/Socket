CC      = g++
CFLAGS  = -g
RM      = rm -f


default: all

all: client server

client: client.cpp
	$(CC) $(CFLAGS) -o client client.cpp

server: server.cpp
	$(CC) $(CFLAGS) -o server server.cpp

clean veryclean:
	$(RM) server
	$(RM) client