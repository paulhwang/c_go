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

    if (!this->theTpTransferObject) {
        phwangAbendS("UFabricClass::transmitFunction", "null theTpTransferObject!\n   The reason could be the connnection from ThemeServer has not been accepted");
        return;
    }

    phwangPortTransmit(this->theTpTransferObject, data_val);
}
