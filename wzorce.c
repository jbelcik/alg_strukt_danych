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
  printf("Algorytm oczywisty:\n");

  int i, j, guard = 0;

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


void rabinKarpMatcher(char string[], int stringSize, char pattern[], int patternSize)
{
  printf("Algorytm Rabina-Karpa:\n");

  int i, j,
      d = 128,
      q = 101,
      h = 1,
      p = 0,
      t = 0,
      guard = 0;

  for (i = 0; i < patternSize - 1; i++) h = (h * d) % q;

  for (i = 0; i < patternSize; i++)
  {
    p = (d * p + pattern[i]) % q;
    t = (d * t + string[i]) % q;
  }

  for (i = 0; i <= stringSize - patternSize; i++)
  {
    if (p == t)
    {
      for (j = 0; j < patternSize; j++)
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

    if (i < stringSize - patternSize)
    {
      t = (d * (t - string[i] * h) + string[i + patternSize]) % q;

      if (t < 0) t += q;
    }
  }

  if (guard == 0) printf("Wzorzec nie wystepuje w tym tekscie\n");
}

/*
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
  printf("Czas dzialania - %3.5lf\n\n", time1);

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  rabinKarpMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  double time2 = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);
  printf("Czas dzialania - %3.5lf\n\n", time2);
/*
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  kmpMatcher(s, ss, p, ps);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  double time3 = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);
  printf("Czas dzialania: %3.5lf\n", time3);
*/
  printf("Czasy dzialania:\n");
  printf("%3.5lf - algorytm oczywisty\n", time1);
  printf("%3.5lf - algorytm Rabina-Karpa\n", time2);
  //printf("%3.5lf - algorytm Knutha-Morrisa-Pratta\n", time3);

  return 0;
}
