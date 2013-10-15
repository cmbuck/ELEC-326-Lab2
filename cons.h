#include <stdio.h>
#include <stdlib.h>
#include "bitio.h"

#define BITS 13                       /* Number of bits in a code word */
#define MAX_CODE ( (1 << BITS) - 1)  /* Maximum value of a code word */

    /***************************************************************************
     *  Code value 256 is used to mark tjet end of the compressed file.         *
     *  The codes 0 through 255 are used to represent single-character phrases. *
     *  They are implicit and do not need to be stored in the dictionary.       *
     * First code value to be used to represent a string if FIRST_CODE.         *
     ****************************************************************************/

#define END_OF_STREAM 256   
#define FIRST_CODE 257   

    /************************************************************************************
     * Dictionary is a Key-Value store represented by an array of TABLE_SIZE structs of *
     * type "dictionary_entry".                                                         *
     *                                                                                  *
     * The key is the string and the value is the code. The key is stored as two        *
     * fields: "prefixcode: and "character"  that identify the string; the value is     *
     * represented by an unsigned integer using BITS number of bits.                    *  
     ************************************************************************************/

struct dictionary_entry {
  unsigned code;            /*  Code for phrase. Initialized to UNUSED */
  unsigned prefixcode;      /*  Code for "prefix" */
  unsigned char character;  /*  Code for "nextchar" */
};

#define TABLE_SIZE 19001    /* Dictionary size: a prime larger than MAX_CODE */
#define UNUSED -1      

#define LINEAR 0            /* Chooses between simple and hash based dictionary. */
                            /* Make LINEAR 0 to exercise your  hash function */


void error(char *);




