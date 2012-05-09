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
  nodePointer x;

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

  return 0;
}
