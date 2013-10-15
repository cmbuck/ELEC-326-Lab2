#include "cons.h"
#define DEBUG(a)	//printf("%d\r\n", a);
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

	//initialize the dictionary to UNUSED
	int i,j,currentCode;
	struct dictionary_entry temp = {UNUSED, 0, 0};
	for (i = FIRST_CODE; i < TABLE_SIZE; i++)
		//dict[i].code = UNUSED;
		dict[i] = temp;
	
	unsigned int prefix, next, index;
	
	i = j = 0;
	currentCode = FIRST_CODE;
	prefix = getc(input);	DEBUG(i++);
	next = getc(input);		DEBUG(i++);
	//TODO: Handle case of empty file
	while (next != -1)
	{
		index = findPhrase(prefix, next);
		if (dict[index].code == UNUSED)
		{
			//add to dictionary
			if (currentCode <= MAX_CODE)
			{
				//dict[index] = {currentCode++, prefix, next};
				dict[index].code = currentCode++;
				dict[index].prefixcode = prefix;
				dict[index].character = next;
			}
			//output prefix
			outputBits(output, prefix, BITS);
			prefix = next;
			next = getc(input);		DEBUG(i++);
		}
		else
		{
			prefix = dict[index].code;
			next = getc(input);		DEBUG(i++);
			//continue;
		}
	}
	//next == END_OF_STREAM; output remaining prefix
	outputBits(output, prefix, BITS);
	outputBits(output, END_OF_STREAM, BITS);
	
}

