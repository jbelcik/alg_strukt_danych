#include <stdio.h>
#include <stdlib.h>


typedef struct node *nodePointer;
typedef struct node
{
  int key;
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
  x -> last -> next = y;
  x -> last = y -> last;

  while (y != NIL)
  {
    y -> head = x;
    y = y -> next;
  }
}


int main()
{
  NILinitialize();

  int i, e = 10;
  nodePointer Z[e];

  for (i = 0; i < e; i++) Z[i] = MakeSet(i);

  Union(FindSet(Z[0]),FindSet(Z[2]));
  Union(FindSet(Z[1]),FindSet(Z[2]));
  Union(FindSet(Z[3]),FindSet(Z[0]));
  Union(FindSet(Z[5]),FindSet(Z[6]));
  Union(FindSet(Z[7]),FindSet(Z[8]));

  nodePointer currentNode;

  for (i = 0; i < e; i++)
  {
    //if (Z[i] != NULL)
    //{
      currentNode = Z[i];

      printf("Z[%i] = { ", i);
    
      while (currentNode != NIL)
      {
        printf("%i ", currentNode -> key);
        currentNode = currentNode -> next;
      }
    
      printf("}\n");
    //}
  }

  return 0;
}
