/*
  Copyrights reserved
  Written by Paul Hwang
  File name: base_mgr_transmit.cpp
*/

#include "../../phwang_dir/phwang.h"
#include "base_mgr_class.h"

void BaseMgrClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);
    phwangTpTransmit(this->theTpTransferObject, data_val);
}