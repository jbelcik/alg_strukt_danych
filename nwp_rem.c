#include <stdio.h>
#include <string.h>
#define INFINITY 999
#include "Hnwp.h"

int n;

int LCS_Lookup(char *x, char *y, int i, int j, int c[][n], char b[][n])
{
  int c1 = 0, c2 = 0;

  if(c[i][j] < INFINITY)
  {
    return c[i][j];
  }

  if(x[i] == y[j])
  {
    c[i][j] = LCS_Lookup(x, y, i - 1, j - 1, c, b) + 1;
    b[i][j] = '\\';
  }
  else
  {
    c1 = LCS_Lookup(x, y, i - 1, j, c, b);
    c2 = LCS_Lookup(x, y, i, j - 1, c, b);

    if(c1 >= c2)
    {
      c[i][j] = c1;
      b[i][j] = '|';
    }
    else
    {
      c[i][j] = c2;
      b[i][j] = '-';
    }
  }

  return c[i][j];
}

void LCS_Rec(char *X, char *Y)
{
  int i, j, m;

  m = strlen(X) + 1;
  n = strlen(Y) + 1;

  int c[m][n];
  char b[m][n], x[m], y[n];

  x[0]='0';
  x[1]='\0';
  y[0]='0';
  y[1]='\0';
  strcat(x, X);
  strcat(y, Y);

  for(i = 1; i <= m; i++)
  {
    for(j = 1; j <= n; j++)
    {
      c[i][j] = INFINITY;
      b[i][j] = ' '; 
    }
  }

  for(i = 0; i <= m; i++)
  {
    c[i][0] = 0;
    b[i][0] = '0';
  }

  for(j = 0; j <= n; j++)
  {
    c[0][j] = 0;
    b[0][j] = '0';
  }

  for(i = 1; i <= m; i++)
  {
    c[i][0] = 0;
  }

  for(j = 0; j <= n; j++)
  {
    c[0][j] = 0;
  }

  LCS_Lookup(x, y, m, n, c, b);

  printf("\n\n\n");

  for(i = 0; i <= n; i++)
  {
    if(i == 0)
    {
      printf("          :");

      for(j = 0; j < m; j++)
      {
        if(j == m - 1)
        {
          printf("%3c  ", x[j]);
        }
        else
        {
          printf("%3c  :", x[j]);
        }
      }

      printf("\n     ");

      for(j = 0; j <= m; j++)
      {
        if(j == m)
        {
          printf(".....");
        }
        else
        {
          printf(".....:");
        }
      }

      printf("\n     ");
    }
    else
    {
      printf("%3c  :", y[i - 1]);

      for(j = 1; j <= m; j++)
      {
        if(j == m)
        {
          printf("%3i  ", c[j - 1][i - 1]);
        }
        else
        {
          printf("%3i  :", c[j - 1][i - 1]);
        }
      }

      printf("\n     ");

      if(i != n)
      {
        for(j = 0; j <= m; j++)
        {
          if(j == m)
          {
            printf(".....");
          }
          else
          {
            printf(".....:");
          }
        }
      }

      printf("\n     ");
    }
  }  

  printf("\n\n");

  for(i = 0; i <= n; i++)
  {
    if(i == 0)
    {
      printf("          :");

      for(j = 0; j < m; j++)
      {
        if(j == m - 1)
        {
          printf("%3c  ", x[j]);
        }
        else
        {
          printf("%3c  :", x[j]);
        }
      }

      printf("\n     ");

      for(j = 0; j <= m; j++)
      {
        if(j == m)
        {
          printf(".....");
        }
        else
        {
          printf(".....:");
        }
      }

      printf("\n     ");
    }
    else
    {
      printf("%3c  :", y[i - 1]);

      for(j = 1; j <= m; j++)
      {
        if(j == m)
        {
          printf("%3c  ", b[j - 1][i - 1]);
        }
        else
        {
          printf("%3c  :", b[j - 1][i - 1]);
        }
      }

      printf("\n     ");

      if(i != n)
      {
        for(j = 0; j <= m; j++)
        {
          if(j == m)
          {
            printf(".....");
          }
          else
          {
            printf(".....:");
          }
        }
      }

      printf("\n     ");
    }
  }

  printf("\n\n     Najdluzszy podciag: ");
  LCS_Print(x, y, b, j - 2, i - 2);
  printf("\n\n\n\n");
}

int main()
{
  char *x = slowo1;
  char *y = slowo2;

  LCS_Rec(x, y);

  return 0;
}
