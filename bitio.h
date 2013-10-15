typedef struct bit_file {
FILE * file;		/* File pointer of open file */
unsigned char mode;     /* Read/Write mode */
unsigned data;		/* 1-byte data buffer */
unsigned char mask;	/* Indicates next valid bit of "data" */
} BIT_FILE;

/* *************************************************************************
 * BIT_FILE defines an in-memory data structure that is maintained by this *
 * program to keep track of open bit files. A new BIT_FILE structure is    *
 * allocated when the  bit file is opened. The pointer to this struct is   *
 * the file handle is used to identify this file.                          *
 ***************************************************************************/

BIT_FILE * openBitFile(char *, char *);
void	   closeBitFile(BIT_FILE *);

/* *************************************************************************
 * The fields of BIT_FILE are as follows:                                  *
 *                                                                         * 
 * "file" :  actual file pointer returned by a call to the standard I/O    *
 * library function fopen() to open the requested file.                    *
 *                                                                         * 
 * "mode" tracks whether the file has been opened for input ('r') or for   *
 * output ('w').                                                           *
 ***************************************************************************/

unsigned long inputBits(BIT_FILE *, int);

/* *************************************************************************
 * For a file opened for input:                                            *
 *                                                                         * 
 * A  byte is read from  the file using getchar() and buffered in the least*
 * significant byte of  "data". Bit 7 will contain the first and bit 0 the *
 * last bit that is read. The field "mask" keeps track of how many bits of *
 * the buffer have been returned so far. A simple way is to set "mask" to  *
 * 0x80 when a new byte is read, and to shift it one  bit to the right for *
 * every bit returned from the file buffer.                                *
 ***************************************************************************/





void  outputBits(BIT_FILE *, unsigned long, int);

/* *************************************************************************
 * For a file opened for output:                                           *
 *                                                                         * 
 * write data passed to outputBits() are stored bit-by-bit in the file     *
 * buffer  "data" from bit 7 to bit 0. When the byte is complete, it is    *
 * written to the file. Once again "mask" tracks how many bits of  "data"  *
 * at any time.                                                            *
 *                                                                         * 
 * Initialize "mask" to 0x80 and shift it right once for every bit copied  *
 * to the file buffer; when "data" is flushed to disk, reinitialize "mask" *
 * and set "data" to 0.                                                    *
 ***************************************************************************/












