#include <stdlib.h>
#include <stdio.h>

#include "int_list.h"


  /* i_list manipulation */

i_list i_insert(i_list i, int value)
{
  if (!i_contains(i, value)){
    int_list_elem * new_elem;
    new_elem = (int_list_elem *) malloc(sizeof(int_list_elem));
    new_elem->value = value;
    new_elem->next = NULL;

    if (i == NULL){
      i = new_elem;
    }
    else{
      int_list_elem * current = i;
      while (current->next != NULL){
        current = current->next;
      }
      current->next = new_elem;
    }
  }
  return i;
}


i_list i_remove_value(i_list i, int value)
{
  // Case where the value to remove is in first position
  if(i->value == value){
    int_list_elem * toBfree = i;
    i = i->next;
    free(toBfree);
  }
  // Every other case
  else {
    int_list_elem * current = i;
    int_list_elem * last = current;
    while (current != NULL && current->value != value){
      last = current;
      current = current->next;
    }
    if (current == NULL){
      // Raise Error
      printf("Error : value %d not found in int_list\n", value);
      printf("--- from i_remove_value() in int_list.c");
    }
    else{
      int_list_elem * toBfree = current;
      last->next = current->next;
      free(toBfree);
    }
  }

  return i;
}


i_list i_empty(i_list i)
{
  int_list_elem * toBfree = NULL;
  int_list_elem * current = i;
  while (current->next != NULL){
    toBfree = current;
    current = current->next;
    free(toBfree);
  }
  free(current);
  return NULL;
}


i_list i_copy(i_list i)
{
  i_list new_list = NULL;
  int_list_elem * current = i;

  while (current != NULL){
    new_list = i_insert(new_list, current->value);
    current = current->next;
  }

  return new_list;
}


i_list i_concat(i_list i1, i_list i2)
{
  int_list_elem * current = i2;
  while (current != NULL){
    i1 = i_insert(i1, current->value);
    current = current->next;
  }

  return i1;
}



/* i_list look up */

bool i_contains(i_list i, int value)
{
  int_list_elem * current = i;
  while (current != NULL && current->value != value){
    current = current->next;
  }

  return current != NULL;
}



/* i_list debug */

void i_print(i_list i)
{
  printf("[");
  int_list_elem * current = i;
  while (current != NULL){
    printf(" %d ", current->value);
    if (current->next != NULL){
      printf(",");
    }
    current = current->next;
  }
  printf("]\n");
}
