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
  else
  {
    if (z -> klucz < y -> klucz)
    {
      y -> left = z;
    }
    else
    {
      y -> right = z;
    }
  }
}


void RBInsert(Wskwezla korzen, int k)
{
  Wskwezla x = (Wskwezla) malloc(sizeof(Twezla)), y;

  x -> klucz = k;

  treeInsert(korzen, x);

  x -> kolor = RED;

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


void RBDelete()
{
  
}


void WKInsertColors()
{
  
}


/* ----------------- program testujacy ---------------------- */

main(){
     nilInit();
     int n,k;
     Wskwezla korzen=nil;
     printf("podaj wysokosc drzewa (0..4) ");
     scanf("%d", &n);
     buduj(&korzen,n);
     drukuj(korzen);
     RBInsert(korzen, 1);
     drukuj(korzen);
}
