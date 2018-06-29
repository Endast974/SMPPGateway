//// CONNECTION TO SMPP SERVER ////////

#include "tcpserver_connection.h"

int tcpserver_connection(char *smppserver_address){
	
	int sockfd;  												// Variable for the Socket (sockfd = file descriptor ; numbytes = ?)											
    struct hostent *he;
    struct sockaddr_in their_addr; 										/* connector's address information */
    
    printf("address :%s\n",smppserver_address);							// Ask for the SMSC address
    int len = strlen(smppserver_address);
    smppserver_address[len - 1]='\0';

    if ((he=gethostbyname(smppserver_address)) == NULL) {  				/* get the host info */
        herror("gethostbyname");
        exit(1);
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {				// binding the socket
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;      								/* host byte order */
    their_addr.sin_port = htons(PORT);    								/* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8);     								/* zero the rest of the struct */

    if (connect(sockfd, (struct sockaddr *)&their_addr,					// TCP Connection to the recipient socket //
		sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    return sockfd;
}

