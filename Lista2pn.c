// ...bozbyc sie errorow w funkcji insertNextNode
// i warningow w funkcjach buildList oraz insertHeadNode
#include <stdio.h>


struct node
{
  int data;
  struct node *prev;
  struct node *next;
};


struct node *buildList()
{
  struct node *head = NULL, *one = NULL, *two = NULL;

  head = malloc(sizeof(struct node));
  one = malloc(sizeof(struct node));
  two = malloc(sizeof(struct node));

  head -> prev = NULL;
  head -> data = 1;
  head -> next = one;

  one -> prev = head;
  one -> data = 2;
  one -> next = two;

  two -> prev = one;
  two -> data = 3;
  two -> next = NULL;

  return head;
}


void insertHeadNode(struct node **headPtr, int data)
{
  struct node *newNode = malloc(sizeof(struct node));
  newNode -> prev = newNode;
  newNode -> data = data;
  newNode -> next = *headPtr;
  *headPtr = newNode;
}


void searchNode(struct node *head, int data)
{
  struct node *currentNode = head;

  while (currentNode != NULL)
  {
    if (currentNode -> data == data)
    {
      printf("Ten element znajduje sie na liscie\n");
      return;
    }
    currentNode = currentNode -> next;
  }
  printf("Ten element nie znajduje sie na liscie\n");
}


/*
void insertNextNode(struct node **nodePtr, int data)
{
  struct node *newNode = malloc(sizeof(struct node));

  if (nodePtr == NULL) insertHeadNode(nodePtr, data);
  else
  {
    newNode -> prev = *nodePtr;
    newNode -> data = data;
    newNode -> next = *nodePtr.next;
    if (nodePtr.next != NULL) nodePtr.next -> prev = *newNode;
    nodePtr -> next = *newNode;
  }
}
*/


void writeList(struct node *head)
{
  struct node *currentNode = head;

  while (currentNode != NULL)
  {
    printf("%d   ", currentNode -> data);
    currentNode = currentNode -> next;
  }
  printf("\n");
}


int main()
{
  struct node *head = buildList();

  writeList(head);

  insertHeadNode(&head, 4);

  //insertNextNode(&head, 5);

  writeList(head);

  searchNode(head, 0);

  return 0;
}
