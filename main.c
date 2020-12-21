#include <stdio.h>
#include <string.h>

// #include "tinydir.h"

#include "int_list.h"
#include "statement.h"
#include "rule.h"
#include "database.h"
#include "user_interface.h"

//use compiler options :
//-I include -I lib src/*.c

//Compile command :
//gcc main.c src/*.c -o out.exe -I include -I lib




int main()
{



  printf("Start of the program\n");

  bool loop = true;
  while (loop){
    if (ui_welcome() == 1){
      loop = false;
    }
  }

  printf("\n\nEnd of the program\n");

  return 0;
}
