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


unsigned long long stringToInteger(char **A, int row)
{
  int j,
      l = strlen(A[row]) - 1;
  unsigned long long n = 0;

  for (j = l; j >= 0; j--) n += pow(system, (l - j)) * (int) A[row][j];

  return n;
}


unsigned long long modHash(unsigned long long k)
{
  return k % m;
}


int main()
{
  char **A;
  int i;
  unsigned long long k;

  A = (char**) malloc(m * sizeof(char*));

  read(A);

  for (i = 0; i < max; i++)
  {
    printf("%s\n", A[i]);
    k = stringToInteger(A, i);
    printf("%lli\n%lli\n\n", k, modHash(k));
  }

  free(A);

  return 0;
}
