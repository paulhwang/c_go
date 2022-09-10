/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_transmit.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

void TestClass::transmitFunction (char *data_val)
{
    phwangDebugS(true, "TestClass::transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        phwangAbendS("TestClass::transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
