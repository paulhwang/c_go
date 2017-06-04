/*
  Copyrights reserved
  Written by Paul Hwang
*/

#include <stdio.h>
#include <string.h>
#include "logit.h"

void phwangLogit (char const* str0_val, char const* str1_val)
{
  printf("%s() %s\n", str0_val, str1_val);
}

void phwangAbend (char const* str0_val, char const* str1_val)
{
  LOGIT(str0_val, str1_val);
}

void LOGIT (char const* str0_val, char const* str1_val)
{
  printf("%s() %s\n", str0_val, str1_val);
}

void ABEND (char const* str0_val, char const* str1_val)
{
  LOGIT(str0_val, str1_val);
}

void phwangPrintBoard (char const* data_val, int board_size_val)
{
    int i = strlen(data_val);
    while (i) {
        if (*data_val == '0') {
            printf(" +");
        }
        else if (*data_val == '1') {
            printf(" *");
        }
        else if (*data_val == '2') {
            printf(" O");
        }
        data_val++;
        i--;
        if (i % board_size_val == 0) {
            printf("\n");
        }
    }
}
