
// COMPILE USING gcc entropy.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include <fenv.h>

#define SIZE 256

float entropy_calc(long byte_count[], int length)
{
      float entropy,count;
      int i;
      
      //shannon entropy's

      for (i = 0; i < SIZE; i++)
        {
          if (byte_count[i] != 0)
            {
              count = (float) byte_count[i] / (float) length;
              entropy += -count * log2f(count);
            }
        }
      return entropy;
}

int main(int argc, char **argv)
{
  FILE *inFile;
  int i,j,n,length;         // length of file
  float           count,entropy;
  long byte_count[SIZE];
  unsigned char   buffer[1024];

  /* do this for all files */
  for(j = 1; j < argc; j++)
    {
      memset(byte_count, 0, sizeof(long) * SIZE);

      inFile = fopen(argv[j], "rb");    // opens the file given on command line

      if(inFile == NULL)                // error-checking to see if file exists
        {
          printf("Files does not exist. `%s`\n", argv[j]);
          continue;
        }

      /* Read the whole file in parts of 1024 */
      while((n = fread(buffer, 1, 1024, inFile)) != 0)
        {
          /* Add the buffer to the byte_count */
          for (i = 0; i < n; i++)
            {
            	//printf("%d\n",(int)buffer[i]);
              byte_count[(int) buffer[i]]++;
              length++;
            }
        }
      fclose(inFile);

      float entropy = entropy_calc(byte_count, length);
      printf("%02.5f \t%s\n", entropy, argv[j]);
    }
  return 0;
}
