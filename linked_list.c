#include <stdio.h>
#include <stdlib.h>

struct node {
  void *data; // instead of store the data, we store the pointer
  struct node *next; // address
};

// defining the actions
// double pointer for the first node. bc it is empty
struct node **linked_list_new();
int linked_list_append(struct node **list, void *data);
int linked_list_insert(struct node **list, void *data, unsigned int index);
int linked_list_remove(struct node **list, unsigned int index);

struct node **linked_list_new(){
  struct node **list = malloc(sizeof(struct node *));
  if(list == NULL) return NULL;

  *list = NULL;

  return list;
}

int linked_list_append(struct node **list, void *data){
  if(list == NULL) return -1;

  struct node *new_node = malloc(sizeof(struct node));
  
  if(new_node == NULL) return -1;

  new_node->data = data;
  new_node->next = NULL;

  if(*list == NULL){
    *list = new_node;
    return 0;
  }

  struct node *current = *list;
  while(current->next != NULL){
    current = current->next;
  }
  current->next = new_node;
  return 0;
}

int linked_list_insert(struct node **list, void *data, unsigned int index){
  if(list == NULL) return -1;

  struct node *new_node = malloc(sizeof(struct node));
  if(new_node == NULL) return -1;

  new_node->data = data;
  new_node->next = NULL;

  if(index == 0){
    new_node->next = *list;
    *list = new_node;
    return 0;
  }

  if(*list == NULL) return -2;

  struct node *current = *list;
  for(int i = 1; i < index; i++){
    if(current->next == NULL) return -2;
    current = current->next;
  }

  new_node->next = current->next;
  current->next = new_node;

  return 0;
}

int linked_list_remove(struct node **list, unsigned int index){
  if(list == NULL) return -1;
  
  if(*list == NULL) return -2;

  if(index == 0){
    struct node *temp = *list;
    *list = (*list)->next;
    temp->data = NULL;
    temp->next = NULL;
    free(temp);
    return 0;
  }

  struct node *prev = NULL;
  struct node *current = *list;
  for(int i = 1; i < index; i++){
    if(current->next == NULL) return -2;
  
    prev = current;
    current = current->next;
  }
  prev->next = current->next;
  current->data = NULL;
  current->next = NULL;
  free(current);

  return 0;
}

int main(){
  struct node **list = linked_list_new();
  int a = 1;
  int b = 2;
  int c = 3;

  linked_list_append(list, &a); // we need to pass the address, not the int itself. bc it wants a void value.
  linked_list_append(list, &b);
  linked_list_append(list, &c);

  linked_list_insert(list, &c, 0);
  linked_list_insert(list, &b, 1);

  linked_list_remove(list, 0);

  struct node *current = *list;
  while(current != NULL){
    printf("%d\n", *(int *)current->data);
    current = current->next;
  }
  return 0;
}
