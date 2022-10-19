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

int FileMgrClass::readBytes (char type, char *buf_val, int buf_size_val, int *eof_val)
{
    if (type == FileMgrClass::FIRST_READ) {

    }
    if (type == FileMgrClass::FIRST_WRITE) {
        
    }
    if (type == FileMgrClass::MORE_READ) {
        
    }
    if (type == FileMgrClass::MORE_WRITE) {
        
    }
}
