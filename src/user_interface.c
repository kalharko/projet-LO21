#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user_interface.h"
#include "database.h"

#if defined(_WIN32)
  #include "tinydir.h"
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

#else
  #include <dirent.h>
  void ui_load_database()
  {
    printf("Chose a database to load :\n");

    int i = 1, len;
    char buffer[50];
    DIR *dir;
    //Displays the databases to chose from
    struct dirent *current_dir;
    dir = opendir("saves");
    readdir(dir);
    readdir(dir);
    if (dir) {
      while ((current_dir = readdir(dir)) != NULL) {
        printf("%d : %s\n", i, current_dir->d_name);
        i += 1;
      }
      closedir(dir);
    }

    if (i == 1){ //if no database to chose from
      printf("No database to chose from !\nPlease create a new database\n");
      return;
    }

    int inpt = ui_input_int(1,i-1); //get user input
    Database d;

    i = 1;
    dir = opendir("saves");
    readdir(dir);
    readdir(dir);
    //get the database to load from
    while ((current_dir = readdir(dir)) != NULL) {
      if (i == inpt){
        len = strlen(current_dir->d_name);
        strncpy(buffer, current_dir->d_name, len-4);
        buffer[len-4] = '\0';

        d = d_load(buffer);
        break;
      }
      i += 1;
    }
    closedir(dir);

    //database is loaded, we go to ui_main()
    ui_main(d);
  }
#endif



int ui_input_int(int min, int max)
{
  char inpt_char[12];
  int inpt_int;
  printf("Go to : ");
  fflush(stdin);
  scanf("%s", inpt_char);

  inpt_int = atoi(inpt_char);
  while (inpt_int > max || inpt_int < min){
    if (inpt_int == -1){
      return -1;
    }
    printf("Please input a number between %d and %d\n", min, max);
    printf("Go to : ");
    fflush(stdin);
    scanf("%s", inpt_char);
    inpt_int = atoi(inpt_char);
  }

  printf("\n");
  return inpt_int;
}


void ui_input_char(char * inpt_char, char * forbiden_char)
{
  char *test_result;
  fflush(stdin);
  scanf("%[^\n]", inpt_char);

  test_result = strpbrk(inpt_char, forbiden_char);
  while (test_result){
    printf("These characters are forbiden : \"%s\"\n", forbiden_char);
    printf("Please input again : ");
    fflush(stdin);
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
    printf("6 : remove rule\n");
    printf("7 : edit rule premise\n");
    printf("8 : edit rule conclusion\n");
    printf("9 : use the inference engine\n");
    printf("0 : quit\n");

    inpt = ui_input_int(0,12);

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
      ui_add_rule(d);
      break;

    case 6: //remove rule
      ui_remove_rule(d);
      break;

    case 7: //edit rule premise
      ui_edit_rule_premise(d);
      break;

    case 8: //edit rule conclusion
      ui_edit_rule_conlusion(d);
      break;

    case 9: //go to the inference engine menu
      ui_inference_engine(d);
      break;

    case 0: //quit
      printf("Save database ?\n1 : Yes\n2 : No\n");
      inpt = ui_input_int(1,2);
      if (inpt == 1){
        d_save(d);
      }
      loop = false;
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


void ui_add_rule(Database d)
{
  s_print(d.statements);
  printf("Chose from the database's statments those that are part of this new rule premise.\n");
  printf("You can for example input : \"1,3,4\" to select statments 1,3 and 4 to be in the premise\n");
  printf("Selected statments : ");

  char inpt_char[255];
  char forbiden_char[85] = "/\\. ;':|()!@#$%^&*_+-=<>?[]{}abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ui_input_char(inpt_char, forbiden_char);

  i_list premise = NULL;
  premise = i_insert(premise, 2);
  int head, head2, inpt, id_premise;
  char c[12];
  bool loop = true;

  while (loop){
    premise = i_empty(premise);
    loop = false;
    ui_input_char(inpt_char, forbiden_char);

    head = 0;
    while (inpt_char[head] != '\0'){
      head2 = 0;
      while (inpt_char[head] != ',' && inpt_char[head] != '\0'){
        c[head2] = inpt_char[head];
        head += 1;
        head2 += 1;
      }
      c[head2] = '\0';
      id_premise = atoi(c);
      if (!s_contains(d.statements, id_premise)){
        printf("Id not found in this database statement list.\n Please input again : ");
        loop = true;
      }

      premise = i_insert(premise, id_premise);

      if (inpt_char[head] != '\0'){
        head += 1;
      }
    }
  }

  printf("Selected statments for the premise : ");
  i_print(premise);

  printf("\nNow chose a unique statment to be used as this new rule conclusion :\n");
  inpt = ui_input_int(0,10000);
  while (!s_contains(d.statements, inpt)){
    printf("Id not found in this database statement list.\n Please input again : ");
    inpt = ui_input_int(0,10000);
  }

  d = d_append_rule(d, premise, inpt);
}


void ui_remove_rule(Database d)
{
  if (d.rules == NULL){
    printf("This database hase no rules!\n");
    return;
  }

  r_print(d.rules, d.statements);
  printf("-1 : cancel\n");
  printf("Please chose a rule to delete\n");

  int inpt;
  inpt = ui_input_int(0,10000);
  while (!r_contains(d.rules, inpt)){
    if (inpt == -1){
      return;
    }
    printf("Id not found in this database statement list.\n Please input again : ");
    inpt = ui_input_int(0,10000);
  }

  d.rules = r_remove_id(d.rules, inpt);
}


void ui_edit_rule_premise(Database d)
{
  if (d.rules == NULL){
    printf("This database hase no rules!\n");
    return;
  }

  //Get the rule that the user want to edit the conclusion
  r_print(d.rules, d.statements);
  printf("-1 : cancel\n");
  printf("Please input the id of the rule that need to change premise\n");

  int inpt, rule_id;
  inpt = ui_input_int(0,10000);
  while (!r_contains(d.rules, inpt)){
    if (inpt == -1){
      return;
    }
    printf("Id not found in this database statement list.\n Please input again : ");
    inpt = ui_input_int(0,10000);
  }
  rule_id = inpt;

  //Inpute new premise
  s_print(d.statements);
  printf("Chose from the database's statments those that are part of this new rule premise.\n");
  printf("You can for example input : \"1,3,4\" to select statments 1,3 and 4 to be in the premise\n");
  printf("Selected statments : ");

  char inpt_char[255];
  char forbiden_char[85] = "/\\. ;':|()!@#$%^&*_+-=<>?[]{}abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ui_input_char(inpt_char, forbiden_char);

  i_list premise = NULL;
  premise = i_insert(premise, 2);
  int head, head2, id_premise;
  char c[12];
  bool loop = true;

  while (loop){
    premise = i_empty(premise);
    loop = false;
    ui_input_char(inpt_char, forbiden_char);

    head = 0;
    while (inpt_char[head] != '\0'){
      head2 = 0;
      while (inpt_char[head] != ',' && inpt_char[head] != '\0'){
        c[head2] = inpt_char[head];
        head += 1;
        head2 += 1;
      }
      c[head2] = '\0';
      id_premise = atoi(c);
      if (!s_contains(d.statements, id_premise)){
        printf("Id not found in this database statement list.\n Please input again : ");
        loop = true;
      }

      premise = i_insert(premise, id_premise);

      if (inpt_char[head] != '\0'){
        head += 1;
      }
    }
  }

  printf("Selected statments for the premise : ");
  i_print(premise);

  r_get_from_id(d.rules, rule_id)->premise = i_copy(premise);
}


void ui_edit_rule_conlusion(Database d)
{
  if (d.rules == NULL){
    printf("This database hase no rules!\n");
    return;
  }

  //Get the rule that the user want to edit the conclusion
  r_print(d.rules, d.statements);
  printf("-1 : cancel\n");
  printf("Please the rule that need to change conclusion\n");

  int inpt, rule_id, statment_id;
  inpt = ui_input_int(0,10000);
  while (!r_contains(d.rules, inpt)){
    if (inpt == -1){
      return;
    }
    printf("Id not found in this database statement list.\n Please input again : ");
    inpt = ui_input_int(0,10000);
  }
  rule_id = inpt;

  //Get the statment that will be the new conclusion of the previously chose rule
  s_print(d.statements);
  printf("-1 : cancel\n");
  printf("Chose a statment to be the conclusion of the previously chosen rule\n");

  inpt = ui_input_int(0,10000);
  while (!s_contains(d.statements, inpt)){
    if (inpt == -1){
      return;
    }
    printf("Id not found in this database statement list.\n Please input again : ");
    inpt = ui_input_int(0,10000);
  }
  statment_id = inpt;

  //Make the change
  r_get_from_id(d.rules, rule_id)->conclusion = statment_id;
}


void ui_inference_engine(Database d)
{
  s_print(d.statements);
  printf("-1 : cancel");
  printf("Please insert a serie of facts.\n");
  printf("i.e. a serie of statments that are true\n");
  printf("You can for example input : \"1,3,4\" to select statments 1,3 and 4 to be in the premise\n");
  printf("Selected statments : ");

  char inpt_char[255];
  char forbiden_char[85] = "/\\. ;':|()!@#$%^&*_+-=<>?[]{}abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ui_input_char(inpt_char, forbiden_char);

  i_list facts = NULL;
  facts = i_insert(facts, 2);
  int head, head2, id_premise;
  char c[12];
  bool loop = true;

  while (loop){
    facts = i_empty(facts);
    loop = false;
    ui_input_char(inpt_char, forbiden_char);

    head = 0;
    while (inpt_char[head] != '\0'){
      head2 = 0;
      while (inpt_char[head] != ',' && inpt_char[head] != '\0'){
        c[head2] = inpt_char[head];
        head += 1;
        head2 += 1;
      }
      c[head2] = '\0';
      id_premise = atoi(c);
      if (!s_contains(d.statements, id_premise)){
        printf("Id not found in this database statement list.\n Please input again : ");
        loop = true;
      }

      facts = i_insert(facts, id_premise);

      if (inpt_char[head] != '\0'){
        head += 1;
      }
    }
  }

  printf("Selected statments for the fact list :\n");
  i_print(facts);

  printf("Inference engine running.\n");

  i_list new_facts = NULL;
  new_facts = d_inference_engine(d, facts);

  printf("Inference engine finished running.\n");
  printf("New facts deduced by the inference engine :\n");
  i_print(new_facts);
  s_print_from_int_list(d.statements, new_facts);

  printf("Totality of the true statments :\n");
  i_list concat = NULL;
  concat = i_concat(facts, new_facts);
  i_print(concat);
}





//eof
