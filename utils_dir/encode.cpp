/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode.cpp
*/

#include "encode.h"

void encodeNumber (char *str_val, int data_val, int size_val)
{
    str_val[size_val] = 0;
    while (size_val > 0) {
        size_val--;
        str_val[size_val] = '0' + data_val % 10;
        data_val /= 10;
    }
}

int decodeNumber (char *str_val, int size_val)
{
    int data = 0;
    int factor = 1;

    while (size_val > 0) {
        size_val--;
        data += (*str_val - '0') * factor;
        factor *= 10;
    }
    return data;
}

