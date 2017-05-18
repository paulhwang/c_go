/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include "stdio.h"

void LOGIT (char * func_name, char *param) {
  printf("%s() %s\n", func_name, param);
}

void ABEND (char * func_name, char *param) {
  LOGIT(func_name, param);
}


