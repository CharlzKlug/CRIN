/* gcc -Wall -Werror -Wextra main.c */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct DoubleLinkedListItem{
  struct DoubleLinkedListItem* head;
  struct DoubleLinkedListItem* tail;
  char string[100];
};

typedef struct DoubleLinkedListItem DLLI;

DLLI *make_item(char const str []) {
  DLLI *new_item= malloc(sizeof(DLLI));
  strncpy(new_item->string, str, 100);
  new_item->head= NULL;
  new_item->tail= NULL;
  return new_item;
}

struct DoubleLinkedList {
  DLLI *head_item;
  DLLI *tail_item;
};

typedef struct DoubleLinkedList DLL;

DLL *make_list(char const input_str []) {
  DLLI *new_item= make_item(input_str);
  DLL *new_list= malloc(sizeof(DLL));
  new_list->head_item= new_item;
  new_list->tail_item= new_item;
  return new_list;
}

void insert_item(DLL* output_DLL, int input_position, char const input_str []) {
  if (0 == input_position) {
    DLLI *new_item= make_item(input_str);
    new_item->tail= output_DLL->head_item;
    output_DLL->head_item->head= new_item;
    output_DLL->head_item= new_item;
    return;
  }
  DLLI *current_item= output_DLL->head_item;
  printf("Started searching...\n");
  for (int i = 0; i < input_position && current_item != NULL; i++) {
    current_item= current_item->tail;
  }
  printf("Searching finished...\n");
  printf("Current string is %s\n", current_item->string);
  DLLI *tmp_item= make_item(input_str);
  tmp_item->head= current_item->head;
  tmp_item->tail= current_item;
  printf("After set tmp_item pointers\n");
  (current_item->head)->tail= tmp_item;
  printf("After set tail\n");
  current_item->head= tmp_item;
  printf("After everything\n");
}

void print_list(DLL* input_dll) {
  DLLI *current_item= input_dll->head_item;
  do {
    printf("%s -> ", current_item->string);
    current_item= current_item->tail;
  } while (current_item != NULL);
  printf("finish\n");
}

/* DLLI *delete_item(DLLI* input_head_list, int input_item_number) { */
/*   DLL *tmp_item= input_head_list; */
/*   for (int i=input_item_number; i > 0 && tmp_item->tail != NULL; i--) { */
/*     tmp_item= tmp_item->tail; */
/*   } */
/* } */

int main() {
  /* DLLI *item= make_item("123"); */
  DLL *my_list= make_list("123");
  insert_item(my_list, 0, "456");
  insert_item(my_list, 0, "789");
  insert_item(my_list, 1, "k1");
  print_list(my_list);
  free(my_list);
  return 0;
}
