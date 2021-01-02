#ifndef DATABASE_H
#define DATABASE_H

#include "statement.h"
#include "rule.h"


typedef struct Database{
  char * name;
  r_list rules;
  s_list statements;
}Database;


// Database prototypes

//Returns an empty database initialized with it's name
Database d_create_empty(Database d, char * name);

//Appends a statement to the database
Database d_append_statement(Database d, char * description);

//Appends a rule to the database
Database d_append_rule(Database d, i_list premise, int conclusion);




//Saves the database to a .txt file
void d_save(Database d);

//Loads a database from a .txt file
Database d_load(char * name);


//Displays the name of the given database followed by it's statements and rules
void d_print(Database d);


//Inference engine prototypes

//Inference engine function :
//Parameters :
//    -d, the database to be tested.
//    -facts, a list of integer that represent the ids of the statments that are true before the
//                engine runs.
//Returns :
//    -new_facts, a list of integer that represent the ids of the statments that were false befor
//                the engine runs and that are true after.

i_list d_inference_engine(Database d, i_list facts);

#endif
