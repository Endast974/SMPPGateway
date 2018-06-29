//// CONVERT SMPP PDU TO HEX FORMAT ////////

#include "pdu_to_hex.h"

void pdu_to_hex(char *pdu_connection, char *pdu){

	int err, size_pdu = 0;								
	regex_t preg;
	const char *str_request = pdu;										// str_request = pdu = bPrint ; String to analyze
	const char *str_regex = "([0-9|A-F]{2} )";							// Regular Expression to get hexadecimal characters from an unpacked PDU
																		// This regex will detect twice a number or the letters A B C D E F  + a space at the end
	int j=0;

	while(strcmp(&str_request[j], "\0")){								// Loop to browse the bPrint/str_request String with 3 characters on a sliding window
		char current[4];
		memset(&current, '\0', sizeof(current)); 
		current[0] = str_request[j];									// To get 3 characters. According to the regex, the first should a number or an hexa letter
		current[1] = str_request[j+1];									// the second a number or an hexa letter
		current[2] = str_request[j+2];									// The last a space
		printf("La chaine courante est :%s;\n",current);
		printf("j = %d\n",j);
		j++;
			
		err = regcomp (&preg, str_regex, REG_EXTENDED);					// Test the Regex validity
		if (err == 0)
		{
			int match;
		    size_t nmatch = 0;
		    regmatch_t *pmatch = NULL;
		      
		    nmatch = preg.re_nsub;
		    pmatch = malloc (sizeof (*pmatch) * nmatch);
		    if (pmatch)
		    {
				match = regexec (&preg, current, nmatch, pmatch, 0);	// Compare the current with the Regex
		        regfree (&preg);
		         if (match == 0)										// if Matched
		         {
		            char *hex = NULL;
		            int start = pmatch[0].rm_so;
		            int end = pmatch[0].rm_eo;
		            size_t size = end - start;
		              
		            //printf("size : %d\n",size); 
		               
		            hex = malloc (sizeof (*hex) * (size + 1));
		            if (hex)
		            {
		               strncpy (hex, &current[start], size);			// Copy the current characters in hex string variables
		               hex[size] = '\0';
		               
		               //pdu_connection[size_pdu] = strtol(hex, NULL,16);
                       size_pdu++;		               
		               hex[2]='\0';
		               //printf ("%s matched\n", hex);
		               
		               //strcat(pdu_connection, "\\x");
		               strncat(pdu_connection, hex, 2);					// concatenate the Hex decimals into the pdu_connection
		               
		               //pdu_connection += snprintf(pdu_connection, sizeof(pdu_connection), "0x%2x\n", dst);
		               
		               ///////////// TESTS //////////
		               
		               //~ char carac_hex[1];
		               //~ memset(&carac_hex, '\\x', sizeof(carac_hex));            
	               
             
		               ////////////////////////       
		               	              		                
		               printf("Concatened result is :%s\n\n",pdu_connection);
		               //free(hex);
		               //free (dst);
		            }
		         }
		         else if (match == REG_NOMATCH)
		         {
		            printf ("%s  does not match to  two hex caracteres + a space\n\n", current);
		         }
		         else
		         {
					char *text;
		            size_t size;
		            size = regerror (err, &preg, NULL, 0);
		            text = malloc (sizeof (*text) * size);
		            if (text)
		            {
		               regerror (err, &preg, text, size);
		               fprintf (stderr, "%s\n", text);
		               free (text);
		            }
		            else
		            {
		               fprintf (stderr, "Not enough memory\n");
		               exit (EXIT_FAILURE);
		            }
		         }
		      }
		      else
		      {
		         fprintf (stderr, "Not enough memory\n");
		         exit (EXIT_FAILURE);
		      }
		   }
		}	
}
