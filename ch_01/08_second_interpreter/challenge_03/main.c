/* gcc -Wall -Werror -Wextra main.c */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct DoubleLinkedList{
  struct DoubleLinkedList* head;
  struct DoubleLinkedList* tail;
  char string[100];
};

typedef struct DoubleLinkedList DLL;

DLL *make_item(char const str []) {
  DLL *new_item= malloc(sizeof(DLL));
  strncpy(new_item->string, str, 100);
  new_item->head= NULL;
  new_item->tail= NULL;
  return new_item;
}

DLL *delete_item(DLL* input_head_list, int input_item_number) {
  DLL *tmp_item= input_head_list;
  for (int i=input_item_number; i > 0 && tmp_item->tail != NULL; i--) {
    tmp_item= tmp_item->tail;
  }
}

int main() {
  DLL *head_list= make_item("123");
  
  free(head_list);
  return 0;
}
