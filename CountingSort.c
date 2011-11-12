#include <stdio.h>
#define x 100


int Length;


void ReadData(int *A)
{
  int i = 0;
  FILE *file = fopen("data.txt", "r" );

  while(fscanf(file, "%i", &A[i++]) != EOF) Length++;

  fclose(file);
}


int main()
{
  Length = 0;
  int A[x], B[x], C[x], i;

  ReadData(A);

  int k = A[0];

  for (i = 0; i < Length; i++)
  {
    if (A[i] > k) k = A[i];
    printf("%3i ", A[i]);
  }
  printf("\n");

  for (i = 0; i <= k; i++) C[i] = 0;
  for (i = 0; i < Length; i++) C[A[i]]++;
  for (i = 1; i <= k; i++) C[i] += C[i - 1];
  for (i = Length - 1; i >= 0; i--)
  {
    B[C[A[i]] - 1] = A[i];
    C[A[i]]--;
  }

  for (i = 0; i < Length; i++) printf("%3i ", B[i]);
  printf("\n");

  return 0;
}
