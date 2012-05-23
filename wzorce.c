#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define Limit 262144
#define StringFile "tekst.txt"
#define PatternFile "wzorzec.txt"
#define MLD 1000000000.0


void czytaj(char string[], int stringSize, char pattern[], int patternSize)
{
  char sign;
  FILE *f;

  if ((f = fopen(StringFile, "r")) == NULL)
  {
    printf("Wystapil blad podczas wczytywania pliku z tekstem\n");
    exit(1);
  }

  while ((sign = fgetc(f)) != EOF)
  {
    if (sign != '\n') string[stringSize++] = sign;
  }

  if ((f = fopen(PatternFile, "r")) == NULL)
  {
    printf("Wystapil blad podczas wczytywania pliku ze wzorcem\n");
    exit(1);
  }

  while ((sign = fgetc(f)) != EOF)
  {
    if (sign != '\n') pattern[patternSize++] = sign;
  }
}


void naiveStringMatcher(char string[], int stringSize, char pattern[], int patternSize)
{
  int i, j, k;

  for (i = 0; i <= stringSize - patternSize; i++)
  {
    if (pattern[0] == string[i])
    {
      k = i + 1;

      for (j = 1; j <= patternSize; j = j)
      {
        if (pattern[j++] == string[k++])
        {
          if (j == patternSize) printf("Algorytm oczywisty:\nWzorzec wystepuje z przesunieciem %i\n", i);
        }
      }
    }
  }
}

/*
void rabinLarpMatcher(char string[], int stringSize, char pattern[], int patternSize)
{

}


void kmpMatcher(char string[], int stringSize, char pattern[], int patternSize)
{

}
*/

int main()
{
  char s[Limit], p[Limit];
  int ss = 0,
      ps = 0;
  struct timespec start, stop;

  czytaj(s, ss, p, ps);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  naiveStringMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  printf("Czas dzialania: %3.5lf\n\n",(stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD));
/*
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  rabinKarpMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  printf("Czas dzialania: %3.5lf\n\n",(stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD));

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  kmpMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  printf("Czas dzialania: %3.5lf\n",(stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD));
*/
  return 0;
}
