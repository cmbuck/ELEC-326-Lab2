/* **************************************************************************
 * A driver file to exercise the compress program.                            *
 *                                                                            *
  * Compile using "gcc driverc.c kvstore.c  bitio.c compress.c"               *
 *                                                                            *
 * Execute using:  "./a.out  X1 out1". This compresses the input file X1 and  *
 * creates a new file called "out1" witt the compressed result.               *
 *                                                                            *
 * You can check the results by comparing to the putput produced by "demo"    *
 * "./demo X1 out1d" compresses file "X1" to the output file "out1d".         *
 *                                                                            *
 * Compare the two output files using the "diff" command.                     *
 * "diff out1 out1d"                                                          *
 * If the files differ it will tell you so; else it will complete silently.   *
 *                                                                            *
 * You can also expand a compressed file using "expandfile"                   *
 * " ./expandfile out1 test1" takes the compressed file "out1" and            *
 * decompresses it into the file "test1". The file "test1" should be the same *
 * as the original input file "X1".
 * ************************************************************************* */

#include "cons.h"

void error(char *s)
{
  fprintf(stderr, "Error in %s\n", s);
  exit(1);
}

// Execution begins here

int main(int argc, char *argv[]) {
FILE *input;
BIT_FILE *output;

if (argc < 3)
  {
    fprintf(stderr, "Usage: compress <input file> <output file>\n");
    exit(1);
  }

fprintf(stderr, "Compressing file %s\n", argv[1]);

 if ((input = fopen(argv[1], "r")) == NULL) 
   error("Opening input file");
 
 if ( (output = openBitFile(argv[2], "w")) == NULL) 
   error("Opening output bit file");
 
fprintf(stderr, "Calling your function\n");


// Calls your function in the file "compress.c"
 compressFile(input,output);

 
 closeBitFile(output);
 if ( fclose(input) )
   error("Closing Input File");;

fprintf(stderr, "Compressed file: %s\n", argv[2]);
}










