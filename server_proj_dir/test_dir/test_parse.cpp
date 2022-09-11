/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_parse.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

void TestClass::exportedparseFunction (char *data_val)
{
    phwangDebugS(true, "TestClass::exportedparseFunction", data_val);
}
