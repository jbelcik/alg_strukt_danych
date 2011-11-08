#include <stdio.h>


int HeapSize, Lenght;


void Heapify(int* A, int i)
{
  int l, r;

  l = 2*i + 1;
  r = 2*i + 2;

  if (l < HeapSize)
  {
    if (A[l] < A[i])
    {
      int pom;

      pom = A[l];
      A[l] = A[i];
      A[i] = pom;
    }
    if (r < HeapSize)
    {
      if (A[r] < A[i])
      {
        int pom;

        pom = A[r];
        A[r] = A[i];
        A[i] = pom;
      }
    }
  }
}


void BuildHeap(int* A)
{
  int i;
  HeapSize = Lenght;

  for (i = Lenght/2; i >= 0; i--) Heapify(A, i);
}


void HeapSort(int* A)
{
  BuildHeap(A);

  int pom, i, j;

  for (i = Lenght - 1; i >= 0; i--)
  {
    printf("%3i ", A[0]);

    pom = A[0];
    A[0] = A[i];
    A[i] = pom;
    HeapSize--;

    for (j = (HeapSize/2) - 1; j >= 0; j--) Heapify(A, j);
  }
}


void ReadData(int *A)
{
  int i = 0;
  FILE *file = fopen("data.txt", "r" );

  while(fscanf(file, "%i", &A[i++]) != EOF) Lenght ++;

  fclose(file);
}


int main()
{
  Lenght = 0;
  int tab[100], i;

  ReadData(tab);
  for (i = 0; i < Lenght; i++) printf("%3i ", tab[i]);
  printf("\n");
  HeapSort(tab);
  printf("\n");

  return 0;
}
