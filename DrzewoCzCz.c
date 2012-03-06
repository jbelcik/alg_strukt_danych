//                                          pmp@inf.univ.gda.pl  2006
// budowanie i drukowanie drzew cz-cz z wartownikiem wspolnym
// dla wszystkich wezlow

#include <stdio.h>
#include <stdlib.h>

#define RED 1        /* stala oznaczajaca kolor wezla */
#define BLACK 0      /* stala oznaczajaca kolor wezla */
#define SZER_EKR 80  /* szerokosc ekranu */
#define IL_POZ   5   /* ilosc poziomow drzewa, ktore beda wydrukowane   
*/
                     /* gwiazdka bedzie sygnalizowac istnienie nizszych 
*/
                     /* poziomow                                        
*/

/* struktury danych do reprezentowania drzewa */
typedef struct wezel *Wskwezla; /* wskaznik na wezel drzewa  */
typedef struct wezel{
	int klucz;
	Wskwezla left, right, p;
	int kolor;
} Twezla ;  /* typ wezla */

/* drzewa z wartownikami: wezel wskazywany przez "nil" jest wartownikiem 
   zastepujacym NULL; dla korzenia pole "p" ma wartosc "nil"; 
   pole nil->p musi byc ustawione odpowiednio w przy usuwaniu 
*/
Wskwezla nil; 

/* funkcja inicjujaca nil; musi byc wywolana przed budowaniem drzewa */
void nilInit(void){
  nil= (Wskwezla) malloc(sizeof(Twezla));
  nil->p = NULL;
  nil->kolor = BLACK;
  nil->left = nil->right = NULL;  
}

/* funkcja drukujaca drzewo binarne na ekranie (tutaj tylko deklaracja) 
*/
/* funkcja drukuje drzewo o korzeniu "w"                                
*/
void drukuj(Wskwezla w);

/* funkcja budujaca pelne drzewo binarne o wysokosci n;       */
/* argument "korzen" to korzen tworzonego drzewa przekazany przez 
wskaznik */ 
/* kluczami sa kolejne parzyste liczby  naturalne zaczynajac od 2    */
void buduj(Wskwezla *korzen, int n);

/* ------------  implementacja ------------------------------------- */
char wydruk[IL_POZ+1][SZER_EKR];

 void drukujost(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       if (w==nil)   return; 
       wydruk[poziom][srodek]='*';
}

void drukujwew(Wskwezla w, int l, int p,int poziom){
       int srodek = (l+p)/2;
       int i,dl;
       char s[9];
       if (w==nil)    return;
       if (w->kolor==BLACK)
         dl=sprintf(s,"%d",w->klucz);
       else
         dl=sprintf(s,"%+d",w->klucz);
       for (i=0;i<dl;i++)
         wydruk[poziom][srodek-dl/2+i]=s[i];
       if (++poziom<IL_POZ){
         drukujwew(w->left,l,srodek,poziom) ;
         drukujwew(w->right,srodek+1,p,poziom) ;
       }
       else {
         drukujost(w->left,l,srodek,poziom) ;
         drukujost(w->right,srodek+1,p,poziom) ;
       }
}

void drukuj(Wskwezla w){
  int j,i;
  for (i=0;i<=IL_POZ;i++)
    for (j=0;j<SZER_EKR;j++)
      wydruk[i][j] = ' ';
  drukujwew(w,0,SZER_EKR,0);
  for (i=0;i<=IL_POZ;i++){
      for (j=0;j<SZER_EKR;j++)
        putchar(wydruk[i][j]);
      printf("\n");
  }
}

/* 2 do potegi n - fun. pomocnicza */
int potega(int n){
	if (n==0)  return 1;
	else       return 2*potega(n-1) ;
}

Wskwezla buduj1(int n, int przesuniecie, Wskwezla p){
  Wskwezla w; 
    if (n==0)   w=nil;
    else {
    w = (Wskwezla) malloc(sizeof(Twezla));
    w->p=p;
    w->klucz = (potega(n-1)+przesuniecie)*2;
    w->kolor = (n%2 ? RED : BLACK);
    w->left = buduj1(n-1,przesuniecie,w);
    w->right = buduj1(n-1,przesuniecie+potega(n-1),w);
    }
    return w;
}
void buduj(Wskwezla *korzen, int n){
  *korzen = buduj1(n+1,0,nil);
  (*korzen)->kolor=BLACK;
}

/* ------------- miejsce na inne funkcje -------------------- */


void leftRotate(Wskwezla korzen, Wskwezla x)
{
  Wskwezla y = x -> right;

  x -> right = y -> left;

  if (y -> left != nil)
  {
    y -> left -> p = x;
  }

  y -> p = x -> p;

  if (x -> p == nil)
  {
    korzen = y;
  }
  else if (x == x -> p -> left)
  {
    x -> p -> left = y;
  }
  else
  {
    x -> p -> right = y;
  }

  y -> left = x;
  x -> p = y;
}


void rightRotate(Wskwezla korzen, Wskwezla x)
{
  Wskwezla y = x -> left;

  x -> left = y -> right;

  if (y -> right != nil)
  {
    y -> right -> p = x;
  }

  y -> p = x -> p;

  if (x -> p == nil)
  {
    korzen = y;
  }
  else if (x == x -> p -> right)
  {
    x -> p -> right = y;
  }
  else
  {
    x -> p -> left = y;
  }

  y -> right = x;
  x -> p = y;
}


void treeInsert(Wskwezla korzen, Wskwezla z)
{
  Wskwezla y = nil,
           x = korzen;

  while (x != nil)
  {
    y = x;

    if (z -> klucz < x -> klucz)
    {
      x = x -> left;
    }
    else
    {
      x = x -> right;
    }
  }

  z -> p = y;

  if (y == nil)
  {
    korzen = z;
  }
  else if (z -> klucz < y -> klucz)
  {
    y -> left = z;
  }
  else
  {
    y -> right = z;
  }
}


void RBInsert(Wskwezla korzen, int k)
{
  Wskwezla x = (Wskwezla) malloc(sizeof(Twezla)), y;

  x -> klucz = k;

  treeInsert(korzen, x);

  x -> kolor = RED;
  x -> left = nil;
  x -> right = nil;

  while (x != korzen && x -> p -> kolor == RED)
  {
    if (x -> p == x -> p -> p -> left)
    {
      y = x -> p -> p -> right;

      if (y -> kolor == RED)
      {
        x -> p -> kolor = BLACK;
        y -> kolor = BLACK;
        x -> p -> p -> kolor = RED;
        x = x -> p -> p;
      }
      else
      {
        if (x == x -> p -> right)
        {
          x = x -> p;
          leftRotate(korzen, x);
        }

        x -> p -> kolor = BLACK;
        x -> p -> p -> kolor = RED;
        rightRotate(korzen, x -> p -> p);
      }
    }
    else
    {
      y = x -> p -> p -> left;

      if (y -> kolor == RED)
      {
        x -> p -> kolor = BLACK;
        y -> kolor = BLACK;
        x -> p -> p -> kolor = RED;
        x = x -> p -> p;
      }
      else
      {
        if (x == x -> p -> left)
        {
          x = x -> p;
          rightRotate(korzen, x);
        }

        x -> p -> kolor = BLACK;
        x -> p -> p -> kolor = RED;
        leftRotate(korzen, x -> p -> p);
      }
    }
  }

  korzen -> kolor = BLACK;
}

Wskwezla RBSearch(Wskwezla x, int k)
{
  while(x != NULL && x != nil && x -> klucz != k)
  {
    if (k < x -> klucz)
    {
      x = x -> left;
    }
    else
    {
      x = x -> right;
    }
  }

  return x;
}

Wskwezla treeMinimum(Wskwezla x)
{
  while (x -> left != NULL && x -> left != nil)
  {
    x = x -> left;
  }

  return x;
}


Wskwezla treeSuccessor(Wskwezla x)
{
  Wskwezla y = NULL;

  if (x -> right != NULL && x -> right != nil)
  {
    return treeMinimum(x -> right);
  }

  y = x -> p;

  while (y != nil && x == y -> right)
  {
    x = y;
    y = y -> p;
  }

  return y;
}


void RBDeleteFixup(Wskwezla korzen, Wskwezla x)
{
  Wskwezla w = NULL;

  while (x != korzen && x -> kolor == BLACK)
  {
    if (x == x -> p -> left)
    {
      w = x -> p -> right;

      if (w -> kolor == RED)
      {
        w -> kolor = BLACK;
        x -> p -> kolor = RED;
        leftRotate(korzen, x -> p);
        w = x -> p -> right;
      }

      if (w -> left -> kolor == BLACK && w -> right -> kolor == BLACK)
      {
        w -> kolor = RED;
        x = x -> p;
      }
      else
      {
        if (w -> right -> kolor == BLACK)
        {
          w -> left -> kolor = BLACK;
          w -> kolor = RED;
          rightRotate(korzen, w);
          w = x -> p -> right;
        }

        w -> kolor = x -> p -> kolor;
        x -> p -> kolor = BLACK;
        w -> right -> kolor = BLACK;
        leftRotate(korzen, x -> p);
        x = korzen;
      }
    }
    else
    {
      w = x -> p -> left;

      if (w -> kolor == RED)
      {
        w -> kolor = BLACK;
        x -> p -> kolor = RED;
        rightRotate(korzen, x -> p);
        w = x -> p -> left;
      }

      if (w -> right -> kolor == BLACK && w -> left -> kolor == BLACK)
      {
        w -> kolor = RED;
        x = x -> p;
      }
      else
      {
        if (w -> left -> kolor == BLACK)
        {
          w -> right -> kolor = BLACK;
          w -> kolor = RED;
          leftRotate(korzen, w);
          w = x -> p -> left;
        }

        w -> kolor = x -> p -> kolor;
        x -> p -> kolor = BLACK;
        w -> right -> kolor = BLACK;
        rightRotate(korzen, x -> p);
        x = korzen;
      }
    }

    x -> kolor = BLACK;
  }
}


void RBDelete(Wskwezla korzen, int k)
{
  Wskwezla z = RBSearch(korzen, k),
           y = NULL,
           x = NULL;

  if (z != NULL && z != nil)
  {
    if (z -> left == nil || z -> right == nil)
    {
      y = z;
    }
    else
    {
      y = treeSuccessor(z);
    }

    if (y -> left != nil)
    {
      x = y -> left;
    }
    else
    {
      x = y -> right;
    }

    x -> p = y -> p;

    if (y -> p == nil)
    {
      korzen = x;
    }
    else if (y == y -> p -> left)
    {
      y -> p -> left = x;
    }
    else
    {
      y -> p -> right = x;
    }

    if (y != z)
    {
      z -> klucz = y -> klucz;
    }

    if (y -> kolor == BLACK)
    {
      RBDeleteFixup(korzen, x);
    }
  }
  else
  {
    printf("\nnie ma takiego elementu\n");
  }
}


void WKInsertColors(Wskwezla korzen)
{
  int random, i, w = 0, l = 0;
  Wskwezla z;
  
  for(i = 0; i < 100; i++)
  {
    random = rand() % 100;
    printf("%i\n", random);
    z = RBSearch(korzen, random);

    if (z != NULL && z != nil)
    {
      RBInsert(korzen, random);
      w++;
    }
    else
    {
      l++;
    }
  }

  printf("\nwstawienia = %i\nwyszukania = %i\n", w, l);
}


/* ----------------- program testujacy ---------------------- */

int main()
{
  nilInit();

  int n, k, w;
  Wskwezla korzen = nil;

  printf("podaj wysokosc drzewa (0...4): ");
  scanf("%i", &n);

  buduj(&korzen,n);
  drukuj(korzen);

  while (1)
  {
    printf("\n1 - wydrukuj drzewo\n");
    printf("2 - wstaw element\n");
    printf("3 - usun element\n");
    printf("4 - WKInsertColors\n");
    printf("5 - wyjdz\n");
    printf("wybor: ");
    scanf("%i", &w);

    switch (w)
    {
      case 1:
        drukuj(korzen);
        break;

      case 2:
        printf("\npodaj element: ");
        scanf("%i", &k);
        RBInsert(korzen, k);
        break;
        
      case 3:
        printf("podaj element: ");
        scanf("%i", &k);
        RBDelete(korzen, k);
        break;

      case 4:
        WKInsertColors(korzen);
        break;

      case 5:
        return 0;
        break;
    }
  }

  return 0;
}
