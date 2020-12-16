#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "statement.h"



/* s_list manipulation */

s_list s_insert(s_list s, int id, char * desc)
{
  if (!s_contains(s, id)){
    statement_elem *new_statement;
    new_statement = (statement_elem *) malloc(sizeof(statement_elem));
    new_statement->id = id;
    new_statement->description = malloc(strlen(desc)+1);
    strcpy(new_statement->description, desc);
    new_statement->next = NULL;

    if (s == NULL){
      s = new_statement;
    }
    else{
      statement_elem * current = s;
      while (current->next != NULL){
        current = current->next;
      }
      current->next = new_statement;
    }
  }

  return s;
}


s_list s_remove_id(s_list s, int id)
{
  if (s_contains(s, id)){
    statement_elem * toBfree = NULL;
    statement_elem * current = s;
    while (current->next != NULL && current->next->id != id){
      current = current->next;
    }
    toBfree = current->next;
    current->next = current->next->next;
    free(toBfree);
  }

  return s;
}


s_list s_empty(s_list s)
{
  statement_elem * current = s;
  statement_elem * toBfree = NULL;
  while (current != NULL){
    free(current->description);
    toBfree = current;
    current = current->next;
    free(toBfree);
  }
  return NULL;
}


void s_edit_description(s_list s, int id, char * desc)
{
  statement_elem * current = s_get_from_id(s, id);
  free(current->description);
  current->description = malloc(strlen(desc)+1);
  strcpy(current->description, desc);
}



/* s_list look up */

bool s_contains(s_list s, int id)
{
  statement_elem * current = s;
  while (current != NULL && current->id != id){
    current = current->next;
  }

  return current != NULL;
}


statement_elem * s_get_from_id(s_list s, int id)
{
  if (s_contains(s, id)){
    statement_elem * current = s;
    while (current->id != id){
      current = current->next;
    }
    return current;
  }
  else{
    //Raise Error
    printf("Error : the required statement is not contained in the given s_list %d\n", id);
    printf("--- from s_get_from_id() in statement.c\n");
    return NULL;
  }
}


int s_length(s_list s)
{
  statement_elem * current = s;
  int i =0;

  while (current != NULL){
    i += 1;
    current = current->next;
  }

  return i;
}



/* s_list display */

void s_print(s_list s)
{
  if (s == NULL) {
    printf("The list of statement is empty !\n");
  }
  else{
    printf("\n|---------------------|\n");
    statement_elem * current = s;
    while (current != NULL){
      printf("%d : %s\n", current->id, current->description);
      current = current->next;
    }
    printf("|---------------------|\n");
  }
}


void s_print_from_int_list(s_list s, i_list i)
{
  if (i == NULL){
    printf("The list of statement is empty !\n");
  }
  else{
    printf("------\n");
    int_list_elem * current_id = i;
    statement_elem * current_statement;
    while (current_id != NULL){
      //get the statement
      current_statement = s_get_from_id(s, current_id->value);
      if (current_statement == NULL){
        //Potential error origin
        printf("--- from s_print_from_int_list() in statement.c\n");
      }
      //display statement
      printf("id : %d -- %s\n", current_statement->id, current_statement->description);

      current_id = current_id->next;
    }
    printf("------\n");
  }
}


void s_print_from_id(s_list s, int id)
{
  statement_elem * current = s;
  current = s_get_from_id(s, id);
  if (current == NULL){
    //Potential error origin
    printf("--- from s_print_from_id() in statement.c\n");
  }
  printf("id : %d -- %s\n", id, current->description);

}












//eof
