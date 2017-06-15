/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_fabric_class.h"

void DFabricClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);
    phwangTpTransmit(this->theTpTransferObject, data_val);
}
