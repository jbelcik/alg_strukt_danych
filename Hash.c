#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define m 3761
#define length 20
#define system 26


void read(char **A)
{
  FILE *file = fopen("3data.txt", "r");

  char *c = (char*) malloc(length * sizeof(char));
  int i;

  for (i = 0; i < m; i++)
  {
    if (fscanf(file, "%s", c) == EOF) break;
    A[i] = (char*) malloc((strlen(c) + 1) * sizeof(char));
    strcpy(A[i], c);
  }

  fclose(file);

  free(c);
}


int stringToInteger(char **A, int row)
{
  int l = strlen(A[row]);

  for (j = l; j > 0; j++) n += A[row][j] * pow(system, (l - j));

  return n;
}
