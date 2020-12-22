#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "database.h"



Database d_create_empty(Database d, char * name)
{
  d.name = malloc(strlen(name)+1);
  strcpy(d.name, name);
  d.rules = NULL;
  d.statements = NULL;
  return d;
}


Database d_append_statement(Database d, char * description)
{
  int id = 0;
  while (s_contains(d.statements, id)){
    id ++;
  }
  d.statements = s_insert(d.statements, id, description);

  s_print_from_id(d.statements, id);

  return d;
}


Database d_append_rule(Database d, i_list premise, int conclusion)
{
  int id = 0;
  while (r_contains(d.rules, id)){
    id ++;
  }

  d.rules = r_insert(d.rules, id, i_copy(premise), conclusion);

  return d;
}



void d_save(Database d)
{
  char buffer[50];

  strcpy(buffer, "saves/");
  strcat(buffer, d.name);
  strcat(buffer, ".txt");
  FILE *fp;
  fp = fopen(buffer, "w");


  //writes the database statements to the file
  statement_elem * s_current = d.statements;
  while (s_current != NULL){
    sprintf(buffer, "%d", s_current->id);
    fputs(buffer, fp);
    fputs(" : ", fp);
    fputs(s_current->description, fp);
    fputs("\n", fp);

    s_current = s_current->next;
  }

  fputs("|\n", fp);

  //writes the database rules to the file
  int_list_elem * i_current;
  Rule * r_current = d.rules;
  while (r_current != NULL){
    sprintf(buffer, "%d", r_current->id);
    fputs(buffer, fp);
    fputs(" : ", fp);

    i_current = r_current->premise;
    while (i_current != NULL){
      sprintf(buffer, "%d", i_current->value);
      fputs(buffer, fp);
      if (i_current->next != NULL){
        fputs(",", fp);
      }
      else{
        fputs(";", fp);
      }
      i_current = i_current->next;
    }

    sprintf(buffer, "%d", r_current->conclusion);
    fputs(buffer, fp);
    fputs("\n", fp);

    r_current = r_current->next;
  }

  fputs("|\n", fp);

  fclose(fp);
}


Database d_load(char * name)
{
  Database d;
  d = d_create_empty(d, name);

  //open file
  FILE *fp;
  char current[255];
  char buffer[55] = "saves/";
  strcat(buffer,name);
  strcat(buffer,".txt");
  printf("opening : %s\n", buffer);
  fp = fopen(buffer, "r");
  if(fp == NULL) {
    perror("Error opening file ");
    return d;
  }

  //Load the statements
  char c[8], description[255];
  int head, head2, id;
  fgets(current, 255, fp);
  while(current[0]!='|')
  {
    //get statement id
    head = 0;
    while (current[head] != ' '){
      c[head] = current[head];
      head += 1;
    }
    c[head] = '\0';
    id = atoi(c);


    //get statement description
    head += 3;
    head2 = 0;
    while (current[head] != '\n'){
      description[head2] = current[head];
      head += 1;
      head2 += 1;
    }
    description[head2] = '\0';

    d.statements = s_insert(d.statements, id, description);
    fgets(current, 60, fp);
  }

  printf("statements loaded\n");

  //load the rules
  int id_premise, conclusion;
  i_list premise = NULL;
  premise = i_insert(premise, 2);
  fgets(current, 60, fp);
  while(current[0]!='|')
  {
    //get rule id
    head = 0;
    while (current[head] != ' '){
      c[head] = current[head];
      head += 1;
    }
    c[head] = '\0';
    id = atoi(c);


    //get rule premise
    premise = i_empty(premise);
    head += 3;
    while (current[head] != ';'){
      head2 = 0;
      while (current[head] != ',' && current[head] != ';'){
        c[head2] = current[head];
        head += 1;
        head2 += 1;
      }
      c[head2] = '\0';
      id_premise = atoi(c);
      premise = i_insert(premise, id_premise);

      if (current[head] != ';'){
        head += 1;
      }
    }


    //get conclusion
    head += 1;
    head2 = 0;
    while (current[head] != '\n'){
      c[head2] = current[head];
      head += 1;
      head2 += 1;
    }
    c[head2] = '\0';
    conclusion = atoi(c);


    d.rules = r_insert(d.rules, id, i_copy(premise), conclusion);
    fgets(current, 60, fp);
  }

  printf("rules loaded\n");
  printf("-%s database succesfully loaded-\n", d.name);

  return d;
}


void d_print(Database d)
{
  printf("================\n");
  printf("Database name : %s\n", d.name);

  printf("\nStatements :");
  s_print(d.statements);

  printf("\nRules :");
  r_print(d.rules, d.statements);

  printf("================\n");
}


  //Inference engine prototypes

i_list d_inference_engine(Database d, i_list facts)
{
  Rule * current_rule;
  i_list true_rules = NULL;
  i_list new_facts = NULL;
  int nb_true;

  while (nb_true > 0){
    nb_true = 0;
    current_rule = d.rules;

    while (current_rule != NULL){
      if (!i_contains(true_rules, current_rule->id)){
        if (r_test(current_rule, facts)){
          true_rules = i_insert(true_rules, current_rule->id);
          facts = i_insert(facts, current_rule->conclusion);
          new_facts = i_insert(new_facts, current_rule->conclusion);
          nb_true += 1;
        }
      }
      current_rule = current_rule->next;
    }

  }

  return new_facts;
}



//eof
