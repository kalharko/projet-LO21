#ifndef RULE_H
#define RULE_H


#include "int_list.h"
#include "statement.h"



//Declaration of a rule, made of statements making the premise and a statement
//As conclusion
typedef struct rule {
  int id;
  i_list premise;
  int conclusion;
  struct rule * next;
} Rule;

typedef Rule * r_list;

  /* r_list manipulation prototypes */
//Insets a new rule at the head of the given r_list
r_list r_insert(r_list rule_list, int id, i_list premise, int conclusion);

//Remove the rule with the given id from the given r_list
r_list r_remove_id(r_list r, int id);

//Free the memory of every rule of the given r_list
r_list r_empty(r_list r);

//Return true if the given id is in the given r_list
bool r_contains(r_list r, int id);

//Returns a pointer to a rule if it's id is found in the given r_list
Rule * r_get_from_id(r_list r, int id);


  /* Rule manipulation prototypes */

//Adds a statement to a premise from it's id
r_list r_add_premise_id(r_list r, int id_rule, int id_statement);

//Remove a statement from the premise from it's id
r_list r_remove_premise_id(r_list r, int id_rule, int id_statement);

//Empty all the premises from the given rule
r_list r_empty_premise(r_list r, int id_rule);





//Sets a statement from it's id as conclusion of the given rule
r_list r_set_conclusion(r_list r, int id_rule, int id_statement);


//Displays the given rule's informations
void r_print(r_list r, s_list s);

#endif
