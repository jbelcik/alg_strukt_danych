#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define m 3761
#define length 20
#define system 26


int len;


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

  len = i;

  fclose(file);

  free(c);
}


unsigned long long stringToInteger(char **A, int row)
{
  int j,
      l = strlen(A[row]) - 1;
  unsigned long long n = 0;

  for (j = l; j >= 0; j--) n += pow(system, (l - j)) * ((int)A[row][j] - 32);

  return n;
}


unsigned long long modHash(unsigned long long k)
{
  return k % m;
}


int maximum(int a, int b)
{
  return (a > b) ? a : b;
}


int main()
{
  char **A;
  int T[m], i,
      zer = 0,
      max = 0;
  unsigned long long k;

  A = (char**) malloc(m * sizeof(char*));
  
  read(A);
  
  for (i = 0; i < m; i++) T[i] = 0;

  for (i = 0; i < len; i++)
  {
    k = stringToInteger(A, i);
    T[modHash(k)]++;
  }

  for (i = 0; i < m; i++)
  {
    if (T[i] == 0) zer++;
    else
    {
      max = maximum(T[i], max);
    }
  }

  double ave = len / m;

  printf("Ilosc zerowych pozycji:\n%i\n\nMaksymalna wartosc:\n%i\n\nSrednia wartosc pozycji niezerowych:\n%lf\n", zer, max, ave);

  free(A);

  return 0;
}
