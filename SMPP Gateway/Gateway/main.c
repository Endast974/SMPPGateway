#include "head.h"

int socketsmpp;

void gestionnaire(int numero)
{
	if (numero == SIGINT){
		char Unbind[] = "\x00\x00\x00\x10\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x01";
		if (send(socketsmpp, Unbind, sizeof(Unbind) + 1, 0) == -1){
              perror("send");
		      exit (1);
		}
	}
	
	/* Function for signal Handling. When a CTRL+C is detected on
	 * the keyboard, the UnBind packet will be send.
	 */
	
}

int main (){

//////// SIGNAL HANDLER /////////////

	int stop = 0;
	struct sigaction action;
	action.sa_handler = gestionnaire; /* pointeur de fonction */
	sigemptyset(&action.sa_mask); /* ensemble de signaux vide */
	action.sa_flags = 0; /* options par défaut */
	if (sigaction(SIGINT, &action, NULL) != 0)
	{
		fprintf(stderr, "Erreur sigaction\n");
		exit(1);
	}
	
	
	
//////// TCP CONNECTION /////////////

	char smppserver_address[16];										// Initialize and get the address of the SMPP Server
	memset(smppserver_address, '\0', sizeof(smppserver_address));
	printf("SMPP Server IP Address : ");
    fgets(smppserver_address, sizeof(smppserver_address), stdin);
    
   	socketsmpp = tcpserver_connection(smppserver_address);				// Connection Attempt
   	//printf("TCP connection done\n");
   	
   	   	
//////// PDU BIND TRANSCEIVER GENERATION  /////////////

	int  ret = 0;														// Stucture for BIND_Transceiver
	bind_transceiver_t pdu;
	
	//Init PDU

	memset(&pdu, 0, sizeof(bind_transceiver_t));
	pdu.command_length   = 0;
	pdu.command_id       = BIND_TRANSCEIVER;
	
	//defined in smpp34.h
	
	pdu.command_status   = ESME_ROK; 
	
	//defined in smpp34.h
	
	pdu.sequence_number  = 1;											
	snprintf(pdu.system_id, sizeof(pdu.system_id), "%s", "smppclient1"); //ID, pass and SMPP systemtype
	snprintf(pdu.password, sizeof(pdu.password), "%s", "password");
	snprintf(pdu.system_type, sizeof(pdu.system_type), "%s", "'VMA'");
	pdu.interface_version = SMPP_VERSION;
	pdu.addr_ton          = 0x00;
	pdu.addr_npi          = 0x00;

    uint8_t bufPDU[2048];
    int bufPDULen = 0;
    uint8_t bPrint[2048];


	/* All the displays for the following steps can be disabled but the
	 * instructions are mandatory to get the PDU and then to translate
	 * in a hexadecimal format */
	 
	 /* Linealize PDU to buffer ********************************************/
    memset(&bufPDU, 0, sizeof(bufPDU));
    ret = smpp34_pack(BIND_TRANSCEIVER, bufPDU, sizeof(bufPDU), &bufPDULen, &pdu);
    if( ret != 0 ){
        printf("Error in smpp34_pack():%d:\n%s\n", 
                                             smpp34_errno, smpp34_strerror);
        return( 0 );
    };
    //printf("parse smpp34_pack()\n%s\n", smpp34_strerror);

    /* Print PDU **********************************************************/
    memset(&bPrint, 0, sizeof(bPrint));
    ret = smpp34_dumpPdu(BIND_TRANSCEIVER, bPrint, sizeof(bPrint), &pdu);
    if( ret != 0){
        printf("Error in smpp34_dumpPdu():%d:\n%s\n", 
                                             smpp34_errno, smpp34_strerror);
        return( -1 );
    };
    //~ printf("parse smpp34_dumpPdu()\n%s\n", smpp34_strerror);
    //~ printf("-----------------------------------------------------------\n");
    //~ printf("%s\n", bPrint);
    //~ printf("-----------------------------------------------------------\n");

    /* Print Buffer *******************************************************/
    
       
    memset(bPrint, 0, sizeof(bPrint));
    ret = smpp34_dumpBuf(bPrint, sizeof(bPrint), bufPDU, bufPDULen);
    if( ret != 0 ){
        printf("Error in smpp34_dumpBuf():%d:\n%s\n", 
                                            smpp34_errno, smpp34_strerror );
        return( -1 );
    };
    printf("parse smpp34_dumpBuf()\n%s\n", smpp34_strerror);
    printf("-----------------------------------------------------------\n");
    printf("%s", bPrint);
    
    
     /* bPrint here is the string with hexadecimal characters to get and
      * this string is supposed t ogo the pdu_to_hex function to get a
      * string which can be sent to the SMPP Serv throughout the socket
      */
    
//////////////	PDU TO HEXADECIMAL FORMAT /////////////	

	char pdu_connection[300]; 											// PDU Connection is the string which was supposed to
	memset(&pdu, '\0', sizeof(pdu_connection));							// contain the hexadecimal PDU
	pdu_to_hex(pdu_connection, (char *)bPrint);							// Function to get these Hexadecimal PDU
	
	/* The previous instructions are supposed to get the PDU for sending
	 * it in the network. As it is not working yet, we are replacing 
	 * by the following string BindTransceiver and sending this one instead
	 */
		
	char BindTransceiver[] = "\x00\x00\x00\x2F\x00\x00\x00\x09\x00\x00\x00\x00\x00\x00\x00\x01\x73\x6D\x70\x70\x63\x6C\x69\x65\x6E\x74\x31\x00\x70\x61\x73\x73\x77\x6F\x72\x64\x00\x27\x56\x4D\x41\x27\x00\x34\x00\x00\x00";
		
///////////// SEND PDU ////////////////

	//~ if (send(socketsmpp, pdu_connection, sizeof(pdu_connection) + 1, 0) == -1){
              //~ perror("send");
		      //~ exit (1);
	//~ }
	//~ free(pdu_connection);
	
	printf("Sending the SMPP PDU BIND_TRANSCEIVER\n");
	
	if (send(socketsmpp, BindTransceiver, sizeof(BindTransceiver) + 1, 0) == -1){
              perror("send");
		      exit (1);
	}
	printf("now connected to the SMPP Server\n");
	
	
	while(!stop){
	
			// Loop for Messages translation and forwarding
			
			// ENQUIRI LINK
		
	}

	return 0;
}
	
