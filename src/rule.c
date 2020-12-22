#include <stdio.h>
#include <stdlib.h>

#include "rule.h"




/* r_list manipulation prototypes */

r_list r_insert(r_list rule_list, int id, i_list premise, int conclusion)
{
  if (!r_contains(rule_list, id)){
    Rule * new_rule;
    new_rule = (Rule *) malloc(sizeof(Rule));
    new_rule->id = id;
    new_rule->premise = i_copy(premise);
    new_rule->conclusion = conclusion;
    new_rule->next = NULL;

    if (rule_list == NULL){
      rule_list = new_rule;
    }
    else{
      Rule * current = rule_list;
      while (current->next != NULL){
        current = current->next;
      }
      current->next = new_rule;
    }
  }
  return rule_list;
}


r_list r_remove_id(r_list r, int id)
{
  if (r_contains(r, id)){
    Rule * toBfree = NULL;
    Rule * current = r;
    while (current->next != NULL && current->next->id != id){
      current = current->next;
    }
    toBfree = current->next;
    toBfree->premise = i_empty(toBfree->premise);
    current->next = current->next->next;
    free(toBfree);
  }

  return r;
}


r_list r_empty(r_list r)
{
  Rule * current = r;
  Rule * toBfree = NULL;
  while (current != NULL){
    toBfree = current;
    toBfree->premise = i_empty(toBfree->premise);
    current = current->next;
    free(toBfree);
  }
  return NULL;
}


bool r_contains(r_list r, int id)
{
  Rule * current = r;
  while (current != NULL && current->id != id){
    current = current->next;
  }
  return current != NULL;
}


Rule * r_get_from_id(r_list r, int id)
{
  if (r_contains(r, id)){
    Rule * current = r;
    while (current->id != id){
      current = current->next;
    }
    return current;
  }
  else{
    //Raise Error
    printf("Error : the rule id : %d is not contained in the given r_list\n", id);
    printf("--- from r_get_from_id() in rule.c\n");
    return NULL;
  }
}


/* Rule manipulation prototypes */

r_list r_add_premise_id(r_list r, int id_rule, int id_statement)
{
  Rule * rule2mod = r_get_from_id(r, id_rule);
  if (rule2mod != NULL){
    rule2mod->premise = i_insert(rule2mod->premise, id_statement);
  }
  return r;
}


r_list r_remove_premise_id(r_list r, int id_rule, int id_statement)
{
  Rule * rule2mod = r_get_from_id(r, id_rule);
  if (rule2mod != NULL){
    rule2mod->premise = i_remove_value(rule2mod->premise, id_statement);
  }
  return r;
}


r_list r_empty_premise(r_list r, int id_rule)
{
  Rule * rule2mod = r_get_from_id(r, id_rule);
  if (rule2mod != NULL){
    rule2mod->premise = i_empty(rule2mod->premise);
  }
  return r;
}


r_list r_set_conclusion(r_list r, int id_rule, int id_statement)
{
  Rule * rule2mod = r_get_from_id(r, id_rule);
  if (rule2mod != NULL){
    rule2mod->conclusion = id_statement;
  }
  return r;
}


void r_print(r_list r, s_list s)
{
  if (r == NULL){
    printf("The list of rule is empty !\n");
  }
  else{
    printf("\n|---------------------|\n");
    Rule * current = r;
    while (current != NULL){
      printf("Rule id : %d\n", current->id);
      printf("Premises :\n");
      s_print_from_int_list(s, current->premise);
      printf("Conclusion :\n");
      s_print_from_id(s, current->conclusion);
      printf("|---------------------|\n");
      current = current->next;
    }
  }
}


bool r_test(Rule * r, i_list facts)
{
  bool out = true;
  int_list_elem * current_int = r->premise;
  while (current_int != NULL && i_contains(facts, current_int->value)){
    current_int = current_int->next;
  }

  if (current_int == NULL){
    return true;
  }
  else{
    return false;
  }
}
