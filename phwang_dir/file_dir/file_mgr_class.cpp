/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_mgr_class.cpp
*/

#include <errno.h>
#include <fcntl.h>
#include "../../phwang_dir/phwang.h"
#include "file_mgr_class.h"
#include "file_access_class.h"

FileMgrClass::FileMgrClass (void)
{
    phwangDebugS(true, "FileMgrClass::FileMgrClass", "start");

    memset(this, 0, sizeof(*this));
}

FileMgrClass::~FileMgrClass (void)
{
    phwangDebugS(true, "FileMgrClass::~FileMgrClass", "exit");
}

int FileMgrClass::readBytesOpen (char type, char const *file_name_val, char *buf_val, int buf_size_val, int *eof_val)
{
    if (type == FileMgrClass::FIRST_READ) {
        int fd = open(file_name_val, O_RDONLY, 0);
        if (fd == -1) {
            printf("***errno=%d\n", errno);
            phwangLogitS("FileMgrClass::readBytesOpen", "cannot open file");
            phwangAbendS("FileMgrClass::readBytesOpen", "cannot open file");
            return -1;
        }
        printf("fd=%d\n", fd);
        phwangLogitS("FileMgrClass::readBytesOpen", "open file succeed");
        int length = read(fd, buf_val, buf_size_val);
        buf_val[length] = 0;
        if (length < buf_size_val) {
            *eof_val = 1;
        }
        else {
            *eof_val = 0;
        }
        return length;
    }
    else if (type == FileMgrClass::FIRST_WRITE) {
    }
    else if (type == FileMgrClass::MORE_READ) {
    }
    else if (type == FileMgrClass::MORE_WRITE) {
    }
    else {
        phwangAbendS("FileMgrClass::readBytesOpen", "bad type");
    }
}

int FileMgrClass::readBytesFOpen (char type, char const *file_name_val, char *buf_val, int buf_size_val, int *eof_val)
{
    if (type == FileMgrClass::FIRST_READ) {
        FILE *fp = fopen(file_name_val, "r");
        if (fp == 0) {
            printf("***errno=%d\n", errno);
            phwangLogitS("FileMgrClass::readBytesFOpen", "cannot open file");
            phwangAbendS("FileMgrClass::readBytesFOpen", "cannot open file");
            return -1;
        }
        return this->readBytesFOpen_(fp, buf_val, buf_size_val, eof_val);
    }
    else if (type == FileMgrClass::FIRST_WRITE) {
        FILE *fp = fopen(file_name_val, "w");
        if (fp == 0) {
            printf("***errno=%d\n", errno);
            phwangLogitS("FileMgrClass::readBytesFOpen", "cannot open file");
            phwangAbendS("FileMgrClass::readBytesFOpen", "cannot open file");
            return -1;
        }
    }
    else if (type == FileMgrClass::MORE_READ) {
        
    }

    else if (type == FileMgrClass::MORE_WRITE) {
        
    }

    else {
        phwangAbendS("FileMgrClass::readBytesFOpen", "bad type");
    }
}

int FileMgrClass::readBytesFOpen_ (FILE *fp_val, char *buf_val, int buf_size_val, int *eof_val)
{
    int index = 0;

    while (index < buf_size_val) {
        int c = getc(fp_val);

        if (c == EOF) {
            *eof_val = 1;
            buf_val[index] = 0;
            return index;
        }
        /*
        else if (c == 13) {
            continue;
        }
        else if (c == 10) {
            buf_val[index] = 0;
            break;
        }
        */

        buf_val[index++] = c;
    }

    *eof_val = 0;
    buf_val[index] = 0;
    return index;
}
