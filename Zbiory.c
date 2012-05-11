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

  int i, c, o, t, e = 10;
  nodePointer currentNode, Z[e];

  for (i = 0; i < e; i++) Z[i] = MakeSet(i);

  printf("Listowa reprezentacja zbiorow zlacznych\n");
  printf("Zbiory poczatkowe:\n");
  //writeSet(&Z[e], e);

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

  while (1)
  {
    printf("\n1 - wydrukuj zbiory\n");
    printf("2 - polacz zbiory\n");
    printf("3 - resetuj zbiory\n");
    printf("4 - zakoncz program\n");
    printf("Twoj wybor: ");
    scanf("%i", &c);

    switch (c)
    {
      case 1:
        //writeSet(&Z[e], e);
        printf("\n");

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
        break;
      
      case 2:
        printf("\nPodaj pierwszy zbior: ");
        scanf("%i", &o);
        printf("Podaj drugi zbior: ");
        scanf("%i", &t);

        Union(FindSet(Z[o]), FindSet(Z[t]));
        break;

      case 3:
        for (i = 0; i < e; i++) Z[i] = MakeSet(i);
        break;

      case 4:
        return 0;
        break;
    }
  }
}
