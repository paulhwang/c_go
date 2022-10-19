/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_mgr_class.h
*/

#pragma once

class FileMgrClass {
  public:
    FileMgrClass(void);
    ~FileMgrClass(void);

    void readNonemptyLine(char *buf_val, int *eof_val);
    int openFile(char const *filename_val, char const *mode_val);
    void readLine(char *buf_val, int *eof_val);
    int readBytes(char *buf_val, int buf_size_val, int *eof_val);
};
