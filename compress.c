#include "cons.h"

unsigned int findPhrase(unsigned, unsigned); 

// Global data structure used in kvStore.c
struct dictionary_entry dict[TABLE_SIZE];  

// compressFile is called from main() in driverc.c

void compressFile(FILE *input, BIT_FILE *output)
{
  /* ********************************************************************
   * Synopsis: 
   * Read the input file one character at a time using the standard I/O *
   * function "getc". Write  the code words of the compressed output,   *
   * one code word at a time using the bitIO routine "outputBits".      *
   *                                                                    *
   * Method:
   * Initialize all the dictionary code word entries to UNUSED.         * 
   * For each phrase: Search the dictionary for an existing code word   *
   * using the function "findPhrase" defined in "kvstore.c". The        *
   * function returns an index into the dictionary array if found; else *
   * it returns an index of an unused entry in the array.               * 
   *                                                                    *
   * Your routine is responsible for writing new codes into the         *
   *  dictionary by adding the key and value  to "dict". This must only *
   * be done if  the code  is no more  than MAX_CODE.                   *
   *                                                                    *
   *********************************************************************/

}




