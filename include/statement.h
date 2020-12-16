#ifndef STATEMENT_H
#define STATEMENT_H


#include <stdbool.h>
#include "int_list.h"


//Declaration of a linked list of statements, with an id and a description
//it is set so every id is unique
typedef struct statement_elem{
  int id;
  char * description;
  struct statement_elem * next;
} statement_elem;

typedef statement_elem * s_list;


// s_list prototypes


  /* s_list manipulation */

//Insets a new statement at the tail of the given s_list
s_list s_insert(s_list s, int id, char * desc);

//Remove the statement with the given id from the given s_list
s_list s_remove_id(s_list s, int id);

//Free the memory of every statement of the given s_list
s_list s_empty(s_list s);


  /* s_list look up */

//Return true if the given id is in the given s_list
bool s_contains(s_list s, int id);

//Return a pointer to the statement with the given id in the given s_list
statement_elem * s_get_from_id(s_list s, int id);

//Returns the number of element in the given s_list
int s_length(s_list s);


  /* s_list display */

//Display the content of the s_list to the console
void s_print(s_list s);

//Display the statements that have the ids corresponding to those in the given i_list
//from the given s_list
void s_print_from_int_list(s_list s, i_list i);

//Display the statement with the given id in the given s_list
void s_print_from_id(s_list s, int id);

#endif
