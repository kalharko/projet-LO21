#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tinydir.h"

#include "user_interface.h"
#include "database.h"



int ui_input_int(int min, int max)
{
  char inpt_char[12];
  int inpt_int;
  printf("Go to : ");
  scanf("%s", inpt_char);

  inpt_int = atoi(inpt_char);
  while (inpt_int > max || inpt_int < min){
    if (inpt_int == -1){
      return -1;
    }
    printf("Please input a number between %d and %d\n", min, max);
    printf("Go to : ");
    scanf("%s", inpt_char);
    inpt_int = atoi(inpt_char);
  }

  printf("\n");
  return inpt_int;
}


void ui_input_char(char * inpt_char, char * forbiden_char)
{
  fflush(stdin);
  char *test_result;
  scanf("%[^\n]", inpt_char);

  test_result = strpbrk(inpt_char, forbiden_char);
  while (test_result){
    printf("These characters are forbiden : \"%s\"\n", forbiden_char);
    printf("Please input again : ");
    scanf("%s", inpt_char);
    test_result = strpbrk(inpt_char, forbiden_char);
  }
}

int ui_welcome()
{
  printf("\n\nWelcome to my Expert Database I made as a school project.\nUTBM LO21 - A2020\n");
  printf("-Oscar Dewasmes\n\n");
  printf("No database is loaded.\n");

  printf("1 : Use existing database\n");
  printf("2 : Create a new database\n");
  printf("3 : help\n");
  printf("4 : quit\n");

  int inpt = ui_input_int(1,4);

  switch(inpt) {
  case 1:
    ui_load_database();
    break;

  case 2:
    ui_create_database();
    break;

  case 3:
     ui_welcome_help();
     break;

  case 4:
    return 1; //exit code
    break;

  default : //Raise error
    printf("Error : input value not treated in switch\n");
    printf("--- from ui_welcome() in user_interface.c");
  }

  return 0;
}


void ui_welcome_help()
{
  printf("Here are some explanations on how the program functions :\n");
  printf("From the main menu, you can chose between 4 options :\n");
  printf(" - By typing 1, you can chose between the existing databases one to load.\n");
  printf(" - By typing 2, you will get to create a new database from scratch.\n");
  printf(" - By typing 3, you will get to this help message.\n");
  printf(" - By typing 4, you will stop the execution of this program.\n\n");
}


void ui_load_database()
{
  printf("Chose a database to load :\n");

  int i = 1, len;
  char buffer[50];
  tinydir_dir dir;
  tinydir_file file;
  tinydir_open(&dir, "saves");
  tinydir_next(&dir);
  tinydir_next(&dir);

  //displays the databases to chose from
  while (dir.has_next)
  {
    tinydir_readfile(&dir, &file);

    len = strlen(file.name);
    strncpy(buffer, file.name, len-4);
    buffer[len-4] = '\0';
    printf("%d : %s", i, buffer);
    printf("\n");

    tinydir_next(&dir);
    i += 1;
  }
  tinydir_close(&dir);

  if (i == 1){ //if no database to chose from
    printf("No database to chose from !\nPlease create a new database\n");
    return;
  }

  int inpt = ui_input_int(1,i-1); //get user input
  Database d;

  i = 1;
  tinydir_open(&dir, "saves");
  tinydir_next(&dir);
  tinydir_next(&dir);
  //get the database to load from
  while (dir.has_next)
  {
    tinydir_readfile(&dir, &file);

    if (i == inpt){
      len = strlen(file.name);
      strncpy(buffer, file.name, len-4);
      buffer[len-4] = '\0';

      d = d_load(buffer);
      break;
    }
    tinydir_next(&dir);
    i += 1;
  }
  tinydir_close(&dir);

  //database is loaded, we go to ui_main()
  ui_main(d);
}


void ui_create_database()
{
  printf("Please input a name for this new database : ");
  char inpt_char[255];
  char forbiden_char[12] = "/\\. ";
  ui_input_char(inpt_char, forbiden_char);

  Database d;
  d = d_create_empty(d, inpt_char);

  //new database has been created, we go to ui_main()
  ui_main(d);

  return;
}


void ui_main(Database d)
{
  int inpt, length;
  char inpt_char[255];
  char forbiden_char[12] = "/\\.";

  printf("\n=======Main database interface=======\n");
  printf("Database %s is loaded.\n", d.name);

  bool loop = true;
  while (loop){
    printf("\n1 : show database statement\n");
    printf("2 : show database rules\n");
    printf("3 : add statement\n");
    printf("4 : edit statement\n");
    printf("5 : add rule\n");
    printf("6 : \n");
    printf("7 : \n");
    printf("8 : \n");
    printf("9 : \n");
    printf("0 : \n");

    inpt = ui_input_int(1,12);

    switch(inpt) {
    case 1: //show database statement
      s_print(d.statements);
      break;

    case 2: //show database rules
      r_print(d.rules, d.statements);
      break;

    case 3: //add statement
      printf("Please input the statement description :\n");
      ui_input_char(inpt_char, forbiden_char);
      d = d_append_statement(d, inpt_char);
      break;

    case 4: //edit statement
      ui_edit_statment(d);
      break;

    case 5: //add rule

      break;

    default : //Raise error
      printf("Error : input value not treated in switch\n");
      printf("--- from ui_main() in user_interface.c");
    }
  }
}


void ui_edit_statment(Database d)
{
  int inpt;
  char inpt_char[255];
  char forbiden_char[12] = "/\\.";
  int length = s_length(d.statements);
  if (length == 0){
    printf("This database has no statement !\n");
    return;
  }

  s_print(d.statements);
  printf("-1 : cancel action\n");
  printf("Please chose the statement to edit :\n");

  inpt = ui_input_int(0,10000);
  while (!s_contains(d.statements, inpt)){
    if (inpt == -1){
      return;
    }
    printf("Id not found in this database statement list.\n Please input again : ");
    inpt = ui_input_int(0,10000);
  }

  printf("Please input the new statement description :\n");
  ui_input_char(inpt_char, forbiden_char);

  s_edit_description(d.statements, inpt, inpt_char);
}









//eof
