/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_access_class.cpp
*/

#include <errno.h>
#include "../../phwang_dir/phwang.h"
#include "file_read_class.h"

FileAccessClass::FileAccessClass (void)
{
    phwangDebugS(true, "FileAccessClass::FileAccessClass", "start");

    memset(this, 0, sizeof(*this));
}

FileAccessClass::~FileAccessClass (void)
{
    phwangDebugS(true, "FileAccessClass::~FileAccessClass", "exit");
}

void FileAccessClass::readLine (char *buf_val, int *eof_val) {
    int index = 0;

    while (1) {
        int c = getc(this->fp_);

        if (c == EOF) {
            *eof_val = 1;
            buf_val[index] = 0;
            return;
        }
        else if (c == 13) {
            continue;
        }
        else if (c == 10) {
            buf_val[index] = 0;
            break;
        }

        buf_val[index++] = c;
    }

    *eof_val = 0;
}

int FileAccessClass::readBytes (char *buf_val, int buf_size_val, int *eof_val)
{
    int index = 0;

    while (index < buf_size_val) {
        int c = getc(this->fp_);

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

int FileAccessClass::openFile (char const *file_name_val, char const *mode_val)
{
    int errno;

    this->fp_ = fopen(file_name_val, mode_val);
    if (this->fp_ == 0) {
        printf("***errno=%d\n", errno);
        phwangLogitS("FileAccessClass::openFile", "cannot open file");
        return -1;
    }

    return 0;
}
