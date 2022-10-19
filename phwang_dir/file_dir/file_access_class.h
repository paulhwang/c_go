/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_access_class.h
*/

#pragma once

class FileAccessClass {
    FILE *fp_;

    void readNonemptyLine(char *buf_val, int *eof_val);

  public:
    FileAccessClass(void);
    ~FileAccessClass(void);

    int openFile(char const *filename_val, char const *mode_val);
    void readLine(char *buf_val, int *eof_val);
    int readBytes(char *buf_val, int buf_size_val, int *eof_val);
};
