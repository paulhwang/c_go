/*
  Copyrights reserved
  Written by Paul Hwang
  File name: u_fabric_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_fabric_class.h"

void UFabricClass::xmtData (char *data_val)
{
    if (true && this->debugOn_) {
        int len = 50;
        if (strlen(data_val) <= len) {
            printf("UFabricClass::xmtData() %s\n", data_val);
        }
        else {
            char data_buf[len + 1];
            memcpy(data_buf, data_val, len);
            data_buf[len] = 0;
            printf("UFabricClass::xmtData() %s\n", data_buf);
        }
    }

    if (!this->portObject()) {
        phwangAbendS("UFabricClass::xmtData", "null theTpTransferObject! The reason could be the connnection from ThemeServer has not been accepted");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
