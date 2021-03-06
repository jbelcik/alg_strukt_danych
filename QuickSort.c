#include <stdio.h>


int Length;


void exc(int *x, int *y)
{
  int pom = *x;
  *x = *y;
  *y = pom;
}


void QuickSort(int *A, int beg, int end)
{
  if (beg + 1 < end)
  {
    int l = beg + 1, r = end, i = A[beg];
    
    while (l < r)
    {
      if (A[l] <= i) l++;
      else exc(&A[l], &A[--r]);
    }
    exc(&A[--l], &A[beg]);
    QuickSort(A, beg, l);
    QuickSort(A, r, end);
  }
}


void ReadData(int *A)
{
  int i = 0;
  FILE *file = fopen("1data.txt", "r" );

  while(fscanf(file, "%i", &A[i++]) != EOF) Length++;

  fclose(file);
}


int main()
{
  Length = 0;
  int tab[100], i;

  ReadData(tab);
  for (i = 0; i < Length; i++) printf("%3i ", tab[i]);
  printf("\n");
  QuickSort(tab, 0, Length);
  for (i = 0; i < Length; i++) printf("%3i ", tab[i]);
  printf("\n");

  return 0;
}
