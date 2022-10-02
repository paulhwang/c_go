/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"

void UFabricClass::transmitFunction (char *data_val)
{
    phwangLogitS("UFabricClass::transmitFunction", data_val);

    if (!this->portObject()) {
        phwangAbendS("UFabricClass::transmitFunction", "null theTpTransferObject! The reason could be the connnection from ThemeServer has not been accepted");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
