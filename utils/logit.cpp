/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include <stdio.h>

void LOGIT (char const* str0_val, char const* str1_val) {
  printf("%s() %s\n", str0_val, str1_val);
}

void ABEND (char const* str0_val, char const* str1_val) {
  LOGIT(str0_val, str1_val);
}


