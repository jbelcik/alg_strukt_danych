#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define m 3761
#define length 20
#define system 26


int max;


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

  max = i;

  fclose(file);

  free(c);
}


int stringToInteger(char **A, int row)
{
  int j,
      n = 1,
      l = strlen(A[row]);

  for (j = l; j > 0; j++)n += pow(system, (l - 1)) * (int) A[row][j];

  return n;
}


int modHash(int k)
{
  return k % m;
}


int main()
{
  char **A;
  int i;

  A = (char**) malloc(m * sizeof(char*));

  read(A);

  for (i = 0; i < max; i++)
  {
    printf("%i\n", stringToInteger(A, i));
  }

  return 0;
}
