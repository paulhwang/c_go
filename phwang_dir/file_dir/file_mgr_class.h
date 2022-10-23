/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_mgr_class.h
*/

#pragma once

class FileMgrClass {
    int debugOn(void) {return true;}
    int readBytesFOpen_ (FILE *fp_val, char *buf_val, int buf_size_val, int *eof_val);

public:
    int const static MAX_FILE_IO_BUF_SIZE = 1024;
    int const static MAX_FILE_NAME_SIZE = 127;
    int const static FD_LEN_SIZE = 5;
    char const static FIRST_READ  = 'R';
    char const static MORE_READ   = 'r';
    char const static FIRST_WRITE = 'W';
    char const static MORE_WRITE  = 'w';

    FileMgrClass(void);
    ~FileMgrClass(void);

    int readBytesOpen(
        char const *file_name_val,
        char *buf_val,
        int buf_size_val,
        int *eof_ptr_val,
        int *fd_ptr_val);

    int readBytesMore(
        int fd_val,
        char *buf_val,
        int buf_size_val,
        int *eof_ptr_val);

    int writeBytesOpen(
        char const *file_name_val,
        char eof_val,
        char *data_val,
        int *fd_ptr_val);

    int readBytesMore(
        int fd_val,
        char eof_val,
        char *data_val);

    int readBytesFOpen(char type, char const *file_name_val, char *buf_val, int buf_size_val, int *eof_val);
};
