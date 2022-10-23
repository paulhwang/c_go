/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_engine_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_engine_class.h"

void DEngineClass::xmtData (char *data_val)
{
    if (true && this->debugOn()) {
        int len = 50;
        if (strlen(data_val) <= len) {
            printf("DEngineClass::xmtData() %s\n", data_val);
        }
        else {
            char data_buf[len + 1];
            memcpy(data_buf, data_val, len);
            data_buf[len] = 0;
            printf("DEngineClass::xmtData() %s\n", data_buf);
        }
    }

    if (!this->portObject()) {
        phwangAbendS("DEngineClass::xmtData", "null portObject()");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
