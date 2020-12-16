#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "database.h"


//Takes as argument a int range, returns a user inputed integer contained in that range
int ui_input_int(int min, int max);

//
void ui_input_char(char * inpt_char, char * forbiden_char);

//Displays welcome message and start up options
int ui_welcome();

//Displays help for the welcome screen
void ui_welcome_help();

//screen to load a database from saved files
void ui_load_database();

//screen to set up a new database
void ui_create_database();

//main interaction screen with the loaded database
void ui_main(Database d);

//screen to edit a statment
void ui_edit_statment(Database d);



#endif
