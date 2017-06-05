/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.h
*/

#pragma once

class PhwangClass {
 public:
    PhwangClass(void);
    ~PhwangClass(void);

    void encodeNumber(char *str_val, int number_val, int size_val);
    int decodeNumber(char *str_val, int size_val);
    void encodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
    void decodeIdIndex(char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);
};
