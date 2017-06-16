/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.cpp
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

void PhwangClass::encodeNumber (char *str_val, int number_val, int size_val)
{
    str_val[size_val] = 0;
    while (size_val > 0) {
        size_val--;
        str_val[size_val] = '0' + number_val % 10;
        number_val /= 10;
    }
}

int PhwangClass::decodeNumber (char *str_val, int size_val)
{
    int number = 0;
    int factor = 1;

    printf("-decodeNumber=%s\n", str_val);
    while (size_val > 0) {
        size_val--;
        number += (str_val[size_val] - '0') * factor;
        factor *= 10;
    }
    printf("decodeNumber=%d\n", number);
    return number;
}

void PhwangClass::encodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    encodeNumber(str_val, id_val, id_size_val);
    encodeNumber(str_val + id_size_val, index_val, index_size_val);
}

void PhwangClass::decodeIdIndex (char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    *id_ptr_val = decodeNumber(str_val, id_size_val);
    *index_ptr_val = decodeNumber(str_val + id_size_val, index_size_val);
}