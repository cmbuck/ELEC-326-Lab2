#include<stdio.h>
#include <stdlib.h>
#include "bitio.h"

BIT_FILE *openBitFile(char *name, char *mode)
{
/* ******************************************************************************* *
 *   Open bit file "name" for mode "r" (reading)  or "w" (writing).                *
 *                                                                                 *
 * Allocate memory space for a BIT_FILE structure. The pointer to this will        *
 * be the file handle returned to the caller. Use fopen() with the appropriate     *
 * arguments to open the file; save the file pointer returned by fopen() in        *
 *  the "file" field of BIT_FILE, and initialize the other fields appropriately.   *
 *  ****************************************************************************** */

  BIT_FILE *filehandle;

  filehandle = (BIT_FILE *) calloc(1, sizeof(BIT_FILE) );
  if (filehandle != NULL)    {
    filehandle -> data = 0;
    filehandle -> mask = 0x80;
    if (*mode == 'w') {
      filehandle -> mode = 'w';
      if ( (filehandle->file =  fopen(name, "w")) == NULL)
	error("Opening Bit File for writing");
    }
    else {
      filehandle -> mode = 'r';
      if ( (filehandle->file = fopen(name, "r")) == NULL)
	error("Opening Bit File for reading");
    }
  }
  return (filehandle);
}


     
void closeBitFile(BIT_FILE * filehandle)
{
/* ***********************************************************************************
 *  If the file had been opened for writing, and  "data" contains  a partial byte of *
 * data, flush the data to the file. Close the file using fclose() and free the      *
 * memory allocated for the BIT_FILE structure. Note that if "data" has between 1    *
 * and 7 bits of actual data at this time, the remaining bits of the byte are padded *
 * to 0.                                                                             *
 *  **********************************************************************************/

  if (filehandle -> mode == 'w') {
    if (filehandle -> mask != 0x80)
      if (putc(filehandle->data, filehandle->file) != filehandle -> data)
	error("CloseBitFile!\n");
  }
  fclose(filehandle -> file);
  free ((char *) filehandle);
}


unsigned long inputBits(BIT_FILE *filehandle, int count)
{
unsigned long mask, data;

  /* ***********************************************************************************
   *  Return the next unread "count" bits from the file.                               *
   *                                                                                   *
   *  Copy bits in the file buffer one-by-one to the long unsigned integer "data"      *
   *  beginning at the bit location indicated by the 1 bit of "mask".                  *
   *                                                                                   *
   *  If the file buffer is empty, use getc() to read the next byte from the file into *
   *  the buffer (filedata->data). If getc() returns EOF before "count" number of bits *
   *  are read, close the file and exit the program.                                   *                                                                        *                                                                                   *
   *  **********************************************************************************/

mask = 1L << (count -1);
data = 0;

while (mask != 0) {
  if (filehandle->mask == 0x80) {
    filehandle->data = getc(filehandle->file);
    if (filehandle->data == EOF) {
      closeBitFile(filehandle);
      fprintf(stderr,"EOF reached prematurely. Closing Input Bit File\n");
      exit(1);
    }
  }
  
  if (filehandle->data & filehandle->mask) 
    data |= mask;
  mask >>= 1;
  filehandle->mask >>= 1;
  
  if (filehandle->mask == 0)
    filehandle->mask = 0x80;
}
return (data);
}


void outputBits(BIT_FILE *filehandle, unsigned long data, int count)
{ 
  /* ***********************************************************************************
   *  Write the "count" number of bits of "data" to the file. The LSB  of "data" is    *
   * numbered zero; so bit (count-1) is to be written first. Assume count > 0 and less *                                                                        * than the number of bits in a long integer.                                        *
   * Copy the bits of "data" to the file buffer (filehandle->data) of the file one at  *
   * a time, beginning with the destination bit indicated by the "mask" field. When    * 
   * the buffer is full (holds a complete byte),use putc() to write the buffer to the  *
   * file.                                                                             *
   *  **********************************************************************************/
  unsigned long mask;
  
  mask = 1L << (count -1);
  while (mask != 0) {
    if (mask & data)
      filehandle->data |= filehandle->mask;
    filehandle->mask >>= 1;
    if (filehandle->mask == 0) {
      if ( putc(filehandle ->data, filehandle->file) != filehandle->data) 
	error("OutputBits!\n");
      filehandle -> data = 0;
      filehandle -> mask = 0x80;
    }
    mask >>= 1;
  }
}





