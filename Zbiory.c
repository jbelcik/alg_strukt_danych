#include <stdio.h>
#include <stdlib.h>


typedef struct node *nodePointer;
typedef struct node
{
  int key, guard;
  nodePointer next, head, last;
} nodeType;


nodePointer NIL;


void NILinitialize(void)
{
  NIL = (nodePointer) malloc(sizeof(nodeType));
  NIL -> next = NIL -> head = NIL -> last = NULL;
}


nodePointer MakeSet(int k)
{
  nodePointer x = (nodePointer) malloc(sizeof(nodeType));

  x -> key = k;
  x -> guard = 0;
  x -> head = x;
  x -> last = x;
  x -> next = NIL;

  return x;
}


nodePointer FindSet(nodePointer x)
{
  return x -> head;
}


void Union(nodePointer x, nodePointer y)
{
  nodePointer currentNode = y;
  y -> guard = 1;

  x -> last -> next = currentNode;
  x -> last = currentNode -> last;

  while (currentNode != NIL)
  {
    currentNode -> head = x;
    currentNode = currentNode -> next;
  }
}


void writeSet(nodePointer Z[], int e)
{
  int i;
  nodePointer currentNode;

  for (i = 0; i < e; i++)
  {
    if (Z[i] -> guard == 0)
    {
      currentNode = Z[i];
      
      printf("Z[%i] = { ", i);
      
      while (currentNode != NIL)
      {
        printf("%i ", currentNode -> key);
        currentNode = currentNode -> next;
      }
      
      printf("}\n");
    }
  }
}


int main()
{
  NILinitialize();

  int c, o, t, e = 0;
  nodePointer Z[e];

  //for (i = 0; i < e; i++) Z[i] = MakeSet(i);

  //printf("Listowa reprezentacja zbiorow zlacznych\n");
  //printf("Zbiory poczatkowe:\n");
  //writeSet(Z, e);

  while (1)
  {
    printf("\n1 - wydrukuj zbiory\n");
    printf("2 - dodaj wierzcholek\n");
    printf("3 - dodaj krawedz\n");
    printf("4 - sprawdz czy dwa wierzcholki sa w takiej samej skladowej spojnosci grafu\n");
    printf("5 - zakoncz program\n");
    printf("Twoj wybor: ");
    scanf("%i", &c);

    switch (c)
    {
      case 1:
        if (e > 0)
        {
          printf("\n");
          writeSet(Z, e);
        }
        else printf("\nBrak zbiorow\n");
        break;

      case 2:
        printf("\nPodaj wierzchołek: ");
        scanf("%i", &o);

        Z[e++] = MakeSet(o);
        break;
      
      case 3:
        printf("\nPodaj pierwszy wierzcholek: ");
        scanf("%i", &o);
        printf("Podaj drugi wierzcholek: ");
        scanf("%i", &t);

        Union(FindSet(Z[o]), FindSet(Z[t]));
        break;

      case 4:
        printf("\nPodaj pierwszy wierzcholek: ");
        scanf("%i", &o);
        printf("Podaj drugi wierzcholek: ");
        scanf("%i", &t);

        if (FindSet(Z[o]) == FindSet(Z[t])) printf("\nTe wierzcholki sa w tej samej skladowej spojnosci grafu\n");
        else printf("\nTe wierzcholki nie sa w tej samej skladowej spojnosci grafu\n");
        break;

      case 5:
        return 0;
        break;
    }
  }
}
