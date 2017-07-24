/*
  Copyrights reserved
  Written by Paul Hwang
  File name: test_transmit.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "test_class.h"

void TestClass::transmitFunction (char *data_val)
{
    this->debug(true, "transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        this->abend("transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
