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

DLL *make_list() {
  /* DLLI *new_item= make_item(input_str); */
  DLL *new_list= malloc(sizeof(DLL));
  new_list->head_item= NULL;
  new_list->tail_item= NULL;
  return new_list;
}

void insert_item(DLL* output_DLL, int const input_position, char const input_str []) {
  if (output_DLL->head_item == NULL && output_DLL->tail_item == NULL) {
    DLLI *new_item= make_item(input_str);
    output_DLL->head_item= new_item;
    output_DLL->tail_item= new_item;
    return;
  }
  
  if (0 == input_position) {
    DLLI *new_item= make_item(input_str);
    new_item->tail= output_DLL->head_item;
    output_DLL->head_item->head= new_item;
    output_DLL->head_item= new_item;
    return;
  }

  if (input_position > 0) {
    DLLI *current_item= output_DLL->head_item;
    for (int i = 0; i < input_position && current_item != NULL; i++) {
      current_item= current_item->tail;
    }
    
    DLLI *tmp_item= make_item(input_str);
    if (current_item != NULL) {
      tmp_item->head= current_item->head;
      tmp_item->tail= current_item;
      (current_item->head)->tail= tmp_item;
      current_item->head= tmp_item;
    }
    
    if (current_item == NULL) {
      output_DLL->tail_item->tail= tmp_item;
      tmp_item->head= output_DLL->tail_item;
      output_DLL->tail_item= tmp_item;
    }
  }

  if (input_position == -1) {
    DLLI *new_item= make_item(input_str);
    output_DLL->tail_item->tail= new_item;
    new_item->head= output_DLL->tail_item;
    output_DLL->tail_item= new_item;
  }
}

void print_list(DLL* input_dll) {
  DLLI *current_item= input_dll->head_item;
  while (current_item != NULL) {
    printf("%s -> ", current_item->string);
    current_item= current_item->tail;
  }
  printf("finish\n");
}

int is_empty_list(DLL* const input_list) {
  if (input_list->head_item == NULL && input_list->tail_item == NULL) {
    return 1;
  }
  return 0;
}

int delete_item(DLL* output_list, int input_item_number) {
  if (is_empty_list(output_list)) {
    return 1;
  }

  if (-1 == input_item_number) {
    DLLI *last_item= output_list->tail_item;
    if (last_item == output_list->head_item) {
      output_list->head_item= NULL;
      output_list->tail_item= NULL;
      free(last_item);
      return 0;
    }
    DLLI *previous_item= last_item->head;
    previous_item->tail=NULL;
    output_list->tail_item= previous_item;
    free(last_item);
    return 0;
  }

  if (0 == input_item_number) {
    DLLI *first_item= output_list->head_item;
    output_list->head_item= output_list->head_item->tail;
    if (output_list->tail_item == first_item) {
      output_list->tail_item= NULL;
    }
    free(first_item);
    return 0;
  }
  
  DLLI *current_item= output_list->head_item;
  int i=0;
  for (; i < input_item_number && current_item != NULL ; i++) {
    current_item= current_item->tail;
  }
  if (current_item == NULL) {return 1;}
  printf("%d --- %s\n", i, current_item->string);
  DLLI *previous_item= current_item->head;
  DLLI *next_item= current_item->tail;
  if (NULL == next_item) {
    return delete_item(output_list, -1);
  }
  previous_item->tail= next_item;
  next_item->head= previous_item;
  free(current_item);
  return 0;
}

int main() {
  DLL *my_list= make_list();
  insert_item(my_list, 0, "last");
  insert_item(my_list, 0, "1");
  insert_item(my_list, 0, "2");
  print_list(my_list);
  if (delete_item(my_list, 1) != 0) {
    printf("Some error on freeing list occured!\n");
    exit(1);
  }
  print_list(my_list);
  if (delete_item(my_list, 1) != 0) {
    printf("Some error on freeing list occured!\n");
    exit(1);
  }
  print_list(my_list);
  if (delete_item(my_list, 0) != 0) {
    printf("Some error on freeing list occured!\n");
    exit(1);
  }
  print_list(my_list);
  free(my_list);
  return 0;
}
