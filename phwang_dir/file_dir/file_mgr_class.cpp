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

FileMgrClass::FileMgrClass (int debug_on_val)
{
    memset(this, 0, sizeof(*this));
    this->debugOn_ = true && debug_on_val;

    if (true && this->debugOn_) {
        printf("FileMgrClass::FileMgrClass() starts");
    }

    memset(this, 0, sizeof(*this));
}

FileMgrClass::~FileMgrClass (void)
{
    if (true && this->debugOn_) {
        printf("FileMgrClass::~FileMgrClass() exits");
    }
}

int FileMgrClass::readBytesOpen (
    char const *file_name_val,
    char *buf_val,
    int buf_size_val,
    int *eof_ptr_val,
    int *fd_ptr_val)
{
    int fd = open(file_name_val, O_RDONLY, 0);
    if (fd == -1) {
        printf("***errno=%d\n", errno);
        phwangLogitS("FileMgrClass::readBytesOpen", "cannot open file");
        phwangAbendS("FileMgrClass::readBytesOpen", "cannot open file");
        return -1;
    }

    if (false && this->debugOn_) {
        printf("FileMgrClass::readBytesOpen() open file succeed. fd=%d\n", fd);
    }

    int length = read(fd, buf_val, buf_size_val);
    buf_val[length] = 0;
    if (length < buf_size_val) {
        *eof_ptr_val = 1;
        close(fd);
    }
    else {
        *eof_ptr_val = 0;
    }
    *fd_ptr_val = fd;
    return length;
}

int FileMgrClass::readBytesMore (
    int fd_val,
    char *buf_val,
    int buf_size_val,
    int *eof_ptr_val)
{
    int length = read(fd_val, buf_val, buf_size_val);
    buf_val[length] = 0;
    if (length < buf_size_val) {
        *eof_ptr_val = 1;
        close(fd_val);
    }
    else {
        *eof_ptr_val = 0;
    }
    return length;
}

int FileMgrClass::writeBytesOpen(
    char const *file_name_val,
    char eof_val,
    char *data_val,
    int *fd_ptr_val)
{
    int fd = creat(file_name_val, 0666);
    if (fd == -1) {
        printf("***errno=%d\n", errno);
        phwangLogitS("FileMgrClass::writeBytesOpen", "cannot create file");
        phwangAbendS("FileMgrClass::writeBytesOpen", "cannot create file");
        fd = 0;
        return -1;
    }

    if (false && this->debugOn_) {
        printf("FileMgrClass::writeBytesOpen() create succeed fd=%d eof=%c\n", fd, eof_val);
    }

    int length = write(fd, data_val, strlen(data_val));
    if (length == -1) {
        printf("FileMgrClass::writeBytesOpen() cannot write file  ***errno=%d\n", errno);
        phwangAbendS("FileMgrClass::writeBytesOpen", "cannot write file");
        return -1;
    }

    if (eof_val == 'Y') {
        close(fd);
    }

    *fd_ptr_val = fd;
}

int FileMgrClass::writeBytesMore(
    int fd_val,
    char eof_val,
    char *data_val)
{
    int length = write(fd_val, data_val, strlen(data_val));
    if (length == -1) {
        printf("FileMgrClass::writeBytesMore() cannot write file. fd=%d  ***errno=%d\n", fd_val, errno);
        phwangAbendS("FileMgrClass::writeBytesMore", "cannot write file");
        return -1;
    }

    if (false && this->debugOn_) {
        printf("FileMgrClass::writeBytesMore() fd=%d length=%d eof=%c\n", fd_val, length, eof_val);
    }

    if (eof_val == 'Y') {
        close(fd_val);
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
