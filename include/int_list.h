#ifndef INT_LIST_H
#define INT_LIST_H

#include <stdbool.h>


// Declaration of a list of ints that is set so each value is unique in the list
typedef struct int_list_elem{
  int value;
  struct int_list_elem * next;
} int_list_elem;

typedef int_list_elem * i_list;


// i_list prototypes


  /* i_list manipulation */

//Appends the given value to the tail of the given i_list
i_list i_insert(i_list i, int value);

//Remove the given value from the given i_list
i_list i_remove_value(i_list i, int value);

//Free the memory of every element of the given i_list
i_list i_empty(i_list i);

//Returns the adress of a new identique i_list
i_list i_copy(i_list i);

//Returns a list with the values of the two given lists
i_list i_concat(i_list i1, i_list i2);


  /* i_list look up */

//Return true if the given value is in the given i_list
bool i_contains(i_list i, int value);



  /* i_list debug */

//Output to the console the content of the givent i_list
void i_print(i_list i);


#endif
