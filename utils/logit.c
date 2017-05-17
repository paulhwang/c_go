#include "stdio.h"

void logit (char * func_name, char *param) {
  printf("%s() %s\n", func_name, param);
}

void debug (int debug_val, char * func_name, char *param) {
  if (debug_val) {
    logit(func_name, param);
  }
}

void abend (char * func_name, char *param) {
  logit(func_name, param);
}


