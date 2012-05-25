#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define Limit 262144
#define StringFile "tekst.txt"
#define PatternFile "wzorzec.txt"
#define MLD 100000000.0


int readString(char string[])
{
  int stringSize = 0;
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

  return stringSize;
}


int readPattern(char pattern[])
{
  int patternSize = 0;
  char sign;
  FILE *f;

  if ((f = fopen(PatternFile, "r")) == NULL)
  {
    printf("Wystapil blad podczas wczytywania pliku ze wzorcem\n");
    exit(1);
  }

  while ((sign = fgetc(f)) != EOF)
  {
    if (sign != '\n') pattern[patternSize++] = sign;
  }

  return patternSize;
}


void naiveStringMatcher(char string[], int stringSize, char pattern[], int patternSize)
{
  int i, j, guard = 0;

  printf("Algorytm oczywisty:\n");

  for (i = 0; i <= stringSize - patternSize; i++)
  {
    if (pattern[0] == string[i])
    {
      for (j = 1; j < patternSize; j++)
      {
        if (pattern[j] == string[i + j])
        {
          if (j == patternSize - 1)
          {
            printf("Wzorzec wystepuje z przesunieciem %i\n", i);
            guard = 1;
          }
        }
        else break;
      }
    }
  }

  if (guard == 0) printf("Wzorzec nie wystepuje w tym tekscie\n");
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
  struct timespec start, stop;

  int ss = readString(s),
      ps = readPattern(p);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  naiveStringMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  double time1 = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);
  printf("Czas dzialania: %3.5lf\n\n", time1);
/*
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  rabinKarpMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  double time2 = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);
  printf("Czas dzialania: %3.5lf\n\n", time2);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  kmpMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  double time3 = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);
  printf("Czas dzialania: %3.5lf\n", time3);
*/
  printf("Czasy dzialania:\n");
  printf("Algorytm oczywisty: %3.5lf\n", time1);
  //printf("Algorytm Knutha-Morrisa-Pratta: %3.5lf\n", time2);
  //printf("Algorytm Rabina-Karpa: %3.5lf\n", time3);

  return 0;
}
