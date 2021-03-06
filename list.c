#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list = (List*) calloc(1,sizeof(List));
  list -> head = NULL;
  list -> current = NULL;
  list -> tail = NULL;
  return list;
}

void * firstList(List * list) {
  if(list -> head && list -> head -> data)
  {
    list -> current = list -> head;
    return list -> head -> data;
  }
  return NULL;
}

void * nextList(List * list) {
  if(list -> current && list -> current -> next)
  {
    list -> current =  list -> current -> next;
    return list -> current -> data;
  }
  return NULL;
}

void * lastList(List * list) {
    if (list -> tail && list-> tail -> data)
    {
      list -> current = list -> tail;
      return list -> tail -> data;
    }
  return NULL;
}

void * prevList(List * list) {
  if (list -> current && list-> current -> prev)
  {
    list -> current = list -> current -> prev;
    return list -> current -> data;
  }
  return NULL;
}

void pushFront(List * list, void * data) {
  
  Node* nodo= createNode(data);
  if ( list -> head != NULL)
  {
  nodo -> next =  list -> head;
  list -> head -> prev = nodo;
  list -> head = nodo;
  }
  else
  {
    list -> head = nodo;
    list -> tail = nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nodo= createNode(data);
  if ( list -> current -> next != NULL)
  {
    list -> current -> next -> prev = nodo;
    list -> current -> next = nodo;
    nodo -> prev = list -> current;
    nodo -> next = list -> current -> next;
  }
  else if(list -> current == list -> tail)
  {
    list -> tail = nodo;
    nodo -> prev  = list -> current;
    list -> current -> next = nodo;
  }
  else
  {
    list -> head = nodo;
    list -> tail = nodo;
  }
}



void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) { 
  void* copia = list -> current -> data;
  Node* nodo = list -> current;
  if (list -> current != list -> head && list -> current != list -> tail)
  {
    list -> current -> prev -> next = list -> current -> next;
    list -> current -> next -> prev = list -> current -> prev;
    list -> current = list -> current -> next;
    free (nodo);
  }
  else if (list -> current == list -> tail)
  {
    list -> current -> prev -> next = NULL;
    list -> tail = list -> current -> prev;
    list -> current = list -> tail;
    free (nodo);
  }
  else
  {
    list -> current -> next -> prev = NULL;
    list -> head = list -> current -> next;
    list -> current = list -> current;
    free (nodo);
  }
  
  return copia;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}