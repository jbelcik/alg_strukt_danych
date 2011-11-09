#include <stdio.h>
#define x 100


int Lenght;


void ReadData(int *A)
{
  int i = 0;
  FILE *file = fopen("data.txt", "r" );

  while(fscanf(file, "%i", &A[i++]) != EOF) Lenght++;

  fclose(file);
}


int main()
{
  Lenght = 0;
  int A[x], B[x], C[x], i;

  ReadData(A);

  int k = A[0];

  for (i = 0; i < Lenght; i++)
  {
    if (A[i] > k) k = A[i];
    printf("%3i ", A[i]);
  }
  printf("\n");

  for (i = 0; i < k + 1; i++) C[i] = 0;
  for (i = 0; i < Lenght; i++) C[A[i]]++;
  for (i = 1; i < k + 1; i++) C[i] += C[i - 1];
  for (i = Lenght - 1; i >= 0; i--)
  {
    B[C[A[i]] - 1] = A[i];
    C[A[i]]--;
  }

  for (i = 0; i < Lenght; i++) printf("%3i ", B[i]);
  printf("\n");

  return 0;
}
