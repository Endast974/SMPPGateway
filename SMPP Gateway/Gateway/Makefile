CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=main

all: $(EXEC)

tcpserver_connection.o: tcpserver_connection.c
	$(CC) -o tcpserver_connection.o -c tcpserver_connection.c $(CFLAGS)
	
#~ smppserver_connection.o: smppserver_connection.c
#~ 	$(CC) -o smppserver_connection.o -c smppserver_connection.c $(CFLAGS)

pdu_to_hex.o: pdu_to_hex.c
	$(CC) -o pdu_to_hex.o -c pdu_to_hex.c $(CFLAGS)

main.o: main.c tcpserver_connection.h pdu_to_hex.h
	$(CC) -o main.o -c main.c $(CFLAGS)
	
main: tcpserver_connection.o pdu_to_hex.o main.o
	$(CC) -o main tcpserver_connection.o pdu_to_hex.o main.o $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(MAIN)
