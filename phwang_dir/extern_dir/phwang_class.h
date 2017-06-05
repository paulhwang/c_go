/*
  Copyrights reserved
  Written by Paul Hwang
  File name: phwang_class.h
*/

#pragma once

class PhwangClass {
 public:
    PhwangClass(void){}
    ~PhwangClass(void){}

    void logit(char const* str0_val, char const* str1_val);
    void abend(char const* str0_val, char const* str1_val);
    void printBoard(char const* data_val, int board_size_val);

    void encodeNumber(char *str_val, int number_val, int size_val);
    int decodeNumber(char *str_val, int size_val);
    void encodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
    void decodeIdIndex(char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);
};
