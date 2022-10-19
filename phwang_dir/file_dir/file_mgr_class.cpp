/*
  Copyrights reserved
  Written by Paul Hwang
  File name: file_mgr_class.cpp
*/

#include <errno.h>
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

void FileMgrClass::readLine (char *buf_val, int *eof_val)
{
}

int FileMgrClass::readBytes (char *buf_val, int buf_size_val, int *eof_val)
{
}

int FileMgrClass::openFile (char const *file_name_val, char const *mode_val)
{
    return 0;
}
