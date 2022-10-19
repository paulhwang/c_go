/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_read_class.cpp
*/

#include <errno.h>
#include "../../phwang_dir/phwang.h"
#include "file_read_class.h"

FileReadClass::FileReadClass (void)
{
    phwangDebugS(true, "FileReadClass::FileReadClass", "start");

    memset(this, 0, sizeof(*this));
}

FileReadClass::~FileReadClass (void)
{
    phwangDebugS(true, "FileReadClass::~FileReadClass", "exit");
}

void FileReadClass::readLine (char *line_buf_val, int *eof_val) {
    int index = 0;

    while (1) {
        int c = getc(this->fp_);

        if (c == EOF) {
            *eof_val = 1;
            line_buf_val[index] = 0;
            return;
        }

        if (c == 13) {
            continue;
        }

        if (c == 10) {
            line_buf_val[index] = 0;
            break;
        }

        line_buf_val[index++] = c;
     }

     *eof_val = 0;
}

int FileReadClass::openFile (char const *file_name_val, char const *mode_val)
{
    int errno;

    this->fp_ = fopen(file_name_val, mode_val);
    if (this->fp_ == 0) {
        printf("***errno=%d\n", errno);
        phwangLogitS("FileReadClass::openFile", "cannot open file");
        return -1;
    }

    return 0;
}
