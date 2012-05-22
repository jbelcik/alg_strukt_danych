#include <stdio.h>
#include <string.h>
#define slowo1 "bdcaba"
#define slowo2 "abcbdab"

int n;

void LCS_Print(char *x, char *y, char b[][n], int i, int j)
{
  if(i == 0 || j == 0)
  {
    return;
  }
	if(b[i][j] == '\\')
  {
    LCS_Print(x, y, b, i - 1, j - 1);
		printf("%c", x[i]);
	}
  else
  {
		if(b[i][j] == '|')
    {
      LCS_Print(x, y, b, i - 1, j);
    }
		else
    {
      LCS_Print(x, y, b, i, j - 1);
    }
	}
}

void LCS_Length(char *X, char *Y)
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
		c[i][0] = 0;
		b[i][0] = '0';
	}

	for(j = 0; j <= n; j++)
  { 
		c[0][j] = 0;
		b[0][j] = '0';
	}

	for(i = 1; i < m; i++)
  {
		for(j = 1; j < n; j++)
    {
			if(x[i] == y[j])
      {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '\\';
			}
      else
      {
				if(c[i - 1][j] >= c[i][j - 1])
        {
					c[i][j] = c[i - 1][j];
					b[i][j] = '-';
				}
        else
        {
					c[i][j] = c[i][j - 1];
					b[i][j] = '|';
				}
			}
		}
	}

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
          printf("  %c  ", x[j]);
        }
        else
        {
          printf("  %c  :", x[j]);
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
      printf("  %c  :", y[i - 1]);

   		for(j = 1; j <= m; j++)
      {
        if(j == m)
        {
          printf("  %i  ", c[j - 1][i - 1]);
        }
        else
        {
          printf("  %i  :", c[j - 1][i - 1]);
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
          printf("  %c  ", x[j]);
        }
        else
        {
          printf("  %c  :", x[j]);
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
      printf("  %c  :", y[i - 1]);

      for(j = 1; j <= m; j++)
      {
        if(j == m)
        {
          printf("  %c  ", b[j - 1][i - 1]);
        }
        else
        {
          printf("  %c  :", b[j - 1][i - 1]);
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
