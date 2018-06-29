#include "tcpserver_connection.h"
//~ #include "smppserver_connection.h"
#include "pdu_to_hex.h"

#include "smpp34.h"
#include "smpp34_dumpBuf.c"
#include "smpp34_dumpPdu.c"
#include "smpp34_pack.c"
#include "smpp34_params.c"
#include "smpp34_params.h"
#include "smpp34_structs.c"
#include "smpp34_structs.h"
#include "smpp34_unpack.c"


#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <signal.h>
#include <regex.h>

#define PORT 2775    /* the port client will be connecting to */

#define MAXDATASIZE 1500 /* max number of bytes we can get at once */

/////////////////   GLOBAL VARIABLES ///////////////////

