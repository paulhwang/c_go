/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_engine_class.h"

void DEngineClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        this->abend("transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
