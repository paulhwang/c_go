/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_parse.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "../protocol_dir/net_port_protocol.h"
#include "test_class.h"

void TestClass::exportedparseFunction (char *data_val)
{
    this->debug(true, "exportedparseFunction", data_val);
}
