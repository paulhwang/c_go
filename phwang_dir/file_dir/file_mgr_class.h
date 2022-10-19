/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_mgr_class.h
*/

#pragma once

class FileMgrClass {
  public:
    char const static FIRST_READ  = 'R';
    char const static MORE_READ   = 'r';
    char const static FIRST_WRITE = 'W';
    char const static MORE_WRITE  = 'w';

    FileMgrClass(void);
    ~FileMgrClass(void);

    int readBytes(char type, char *buf_val, int buf_size_val, int *eof_val);
};
