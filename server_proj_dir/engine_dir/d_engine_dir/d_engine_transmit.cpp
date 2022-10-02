/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_engine_class.h"

void DEngineClass::transmitFunction (char *data_val)
{
    phwangLogitS("DEngineClass::transmitFunction", data_val);

    if (!this->portObject()) {
        phwangAbendS("DEngineClass::transmitFunction", "null portObject()");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
