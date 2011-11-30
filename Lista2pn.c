#include <stdio.h>
#include <stdlib.h>


struct node
{
  int data;
  struct node *prev;
  struct node *next;
};


struct node *buildList()
{
  struct node *head = malloc(sizeof(struct node)),
              *one = malloc(sizeof(struct node)),
              *two = malloc(sizeof(struct node));

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
      printf("Podany element znajduje sie na liscie\n");
      return;
    }
    currentNode = currentNode -> next;
  }
  printf("Podany element nie znajduje sie na liscie\n");
}


void insertNextNode(struct node *head, int data, int newData)
{
  struct node *currentNode = head,
              *newNode = malloc(sizeof(struct node));
  
  while (currentNode != NULL)
  {  
    if (currentNode -> data == data)  
    {
      newNode -> prev = currentNode;
      newNode -> data = newData;
      newNode -> next = currentNode -> next;
      if (currentNode -> next != NULL) (currentNode -> next) -> prev = newNode;
      currentNode -> next = newNode;
      return;
    }
    currentNode = currentNode -> next;
  }
  printf("Podany element nie znajduje sie na liscie\n");
}


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

  insertNextNode(head, 2, 5);

  writeList(head);

  searchNode(head, 4);

  return 0;
}
