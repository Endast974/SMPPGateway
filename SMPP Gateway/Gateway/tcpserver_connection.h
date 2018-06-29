#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <unistd.h>

#define PORT 2775    /* the port client will be connecting to */
#define MAXDATASIZE 1500 /* max number of bytes we can get at once */

int tcpserver_connection(char *smppserver_address);
