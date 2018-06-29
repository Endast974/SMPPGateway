////// SEND SMPP PDU BIND TRANSCEIVER TO SMPP SERVER ////////////


// This file is not integrated to the project yet

#include "smppserver_connection.h"

extern int  smpp34_errno;												// Global variables to get errors in SMPP Structures
extern char smpp34_strerror[2048];

void smppserver_connection(int socket, char *smppserver_id, char *smppserver_password){
	
	bind_transceiver_t b;												// Structure declaration

    memset(&b, 0, sizeof(bind_transceiver_t));

    /* Init PDU ***********************************************************/
    
    b.command_length   = 0;
    b.command_id       = BIND_TRANSCEIVER;
    b.command_status   = ESME_ROK;
    b.sequence_number  = 1;
    snprintf((char*)b.system_id, sizeof(b.system_id), "%s", smppserver_id);
    snprintf((char*)b.password, sizeof(b.password), "%s", smppserver_password);
    snprintf((char*)b.system_type, sizeof(b.system_type), "%s", "VMA");
    b.interface_version= 0x34;
    b.addr_ton         = 0x00;
    b.addr_npi         = 0x00;
    snprintf((char*)b.address_range, sizeof(b.address_range), "%s", "address_range");
     
    /* PDU to char *******************************************************/
    
    int ret = 0;														// Variables for PDU Unpack and description
    uint8_t bufPDU[2048];
    int bufPDULen = 0;
    uint8_t bPrint[2048];
    
    memset(bPrint, 0, sizeof(bPrint));
    ret = smpp34_dumpBuf(bPrint, sizeof(bPrint), bufPDU, bufPDULen);
    if( ret != 0 ){
        printf("Error in smpp34_dumpBuf():%d:\n%s\n", 
                                            smpp34_errno, smpp34_strerror );
        return( -1 );
    };
    //~ printf("parse smpp34_dumpBuf()\n%s\n", smpp34_strerror);
    //~ printf("-----------------------------------------------------------\n");
    //printf("%s", bPrint);
     
     /* bPrint here is the string with hexadecimal characters to get and
      * this string is supposed t ogo the pdu_to_hex function to get a
      * string which can be sent to the SMPP Serv throughout the socket
      */
     
     
     
}
