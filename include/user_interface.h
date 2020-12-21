#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "database.h"


//Takes as argument a int range, returns a user inputed integer contained in that range
int ui_input_int(int min, int max);

//Modifie the given inpt_char with a user input that do not contains any of
//the given forbiden characters
void ui_input_char(char * inpt_char, char * forbiden_char);

//Displays welcome message and start up options
int ui_welcome();

//Displays help for the welcome screen
void ui_welcome_help();

//Interface to load a database from saved files
void ui_load_database();

//Interface to set up a new database
void ui_create_database();

//Main interaction interface with the loaded database
void ui_main(Database d);

//Interface to edit a statment
void ui_edit_statment(Database d);


//Interface to add a rule to the database
void ui_add_rule(Database d);

//Interface to remove a rule from the given database
void ui_remove_rule(Database d);

//Interface to edit a rule's conclusion from the given database
void ui_edit_rule_conlusion(Database d);

#endif
