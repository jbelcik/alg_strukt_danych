#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define x 300
#define y 300


int len = 0, cols;


int get(char **A, int row, int col)
{
  return (int)((strlen(A[row]) > col) ? A[row][col] : ' ');
}


int max(int a, int b)
{
  return (a > b) ? a : b;
}


void read(char ***A)
{
  FILE *file = fopen("2data.txt", "r");

  *A = (char **) malloc(x * sizeof(char*));

  int i;

  char *c = (char*) malloc(x * sizeof(char)); // char c[300] powoduje warningi

  for (i = 0; i < x; i++)
  {
    if (fscanf(file, "%s", c) == EOF) break;

    (*A)[i] = (char*) malloc((strlen(c) + 1) * sizeof(char));
    strcpy((*A)[i], c);
    cols = max(cols, strlen(c));
  }

  len = i;

  fclose(file);

  free(c);
}


int main()
{

  char **A, **B;

  read(&A);

  int i;

  printf("len: %i\ncols: %i\n", len, cols);

  printf("\nPrzed:\n");

  for (i = 0; i < len; i++) printf("%s\n", A[i]);

  B = (char **) malloc(len * sizeof(char*));

  int col;

  for (col = cols - 1; col >= 0; col--)
  {
    char C[x];

    int k = get(A, 0, col);

    for (i = 1; i < len; i++)
    {
      k = max(k, get(A, i, col));
    }
    for (i = 0; i <= k; i++) C[i] = 0;
    for (i = 0; i < len; i++) C[get(A, i, col)]++;
    for (i = 1; i <= k; i++) C[i] += C[i - 1];
    for (i = len - 1; i >= 0; i--)
    {
      int c = get(A, i, col);
      B[C[c] - 1] = A[i];
      C[c]--;
    }

    char **T = B;
    B = A;
    A = T;
  }

  printf("\nPo:\n");

  for (i = 0; i < len; i++)
  {
    printf("%s\n", A[i]);
    free(A[i]);
  }
  printf("\n");

  free(A);
  free(B);

  return 0;
}
