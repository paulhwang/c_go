/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_logit.cpp
*/

#include "../phwang.h"
#include "phwang_class.h"

void PhwangClass::logit (char const* str0_val, char const* str1_val)
{
    printf("%s() %s\n", str0_val, str1_val);
}

void PhwangClass::abend (char const* str0_val, char const* str1_val)
{
    phwangLogit(str0_val, str1_val);
    phwangLogit("*****Abend*****", str0_val);
    int *junk = 0;
    *junk = 0;
}

void PhwangClass::printBoard (char const* data_val, int board_size_val)
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
