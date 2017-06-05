/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode.cpp
*/

#include <stdio.h>

void encodeNumber (char *str_val, int number_val, int size_val)
{
    str_val[size_val] = 0;
    while (size_val > 0) {
        size_val--;
        str_val[size_val] = '0' + number_val % 10;
        number_val /= 10;
    }
}

int decodeNumber (char *str_val, int size_val)
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

void encodeIdIndex (char *str_val, int id_val, int id_size_val, int index_val, int index_size_val)
{
    encodeNumber(str_val, id_val, id_size_val);
    encodeNumber(str_val + id_size_val, index_val, index_size_val);
}

void decodeIdIndex (char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val)
{
    *id_ptr_val = decodeNumber(str_val, id_size_val);
    *index_ptr_val = decodeNumber(str_val + id_size_val, index_size_val);
}
