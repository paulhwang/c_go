/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_read_class.h
*/

#pragma once

class FileReadClass {
    FILE *fp_;

    void readNonemptyLine(char *buf_val, int *eof_val);

  public:
    FileReadClass(void);
    ~FileReadClass(void);

    int openFile(char const *filename_val, char const *mode_val);
    void readLine(char *buf_val, int *eof_val);
    int readBytes(char *buf_val, int buf_size_val, int *eof_val);
};
