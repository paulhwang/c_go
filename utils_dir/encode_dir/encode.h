/*
  Copyrights reserved
  Written by Paul Hwang
  File name: encode.h
*/

#pragma once

void encodeNumber(char *str_val, int data_val, int size_val);
int decodeNumber(char *str_val, int size_val);
void encodeIdIndex(char *str_val, int id_val, int id_size_val, int index_val, int index_size_val);
void decodeIdIndex(char *str_val, int *id_ptr_val, int id_size_val, int *index_ptr_val, int index_size_val);
