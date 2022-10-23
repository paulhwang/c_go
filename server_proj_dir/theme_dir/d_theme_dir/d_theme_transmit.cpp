/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_theme_class.h"

void DThemeClass::xmtData (char *data_val)
{
    if (true && this->debugOn()) {
        int len = 50;
        if (strlen(data_val) <= len) {
            printf("DThemeClass::xmtData() %s\n", data_val);
        }
        else {
            char data_buf[len + 1];
            memcpy(data_buf, data_val, len);
            data_buf[len] = 0;
            printf("DThemeClass::xmtData() %s\n", data_buf);
        }
    }


    if (!this->portObject()) {
        phwangAbendS("DThemeClass::xmtData", "null portObject()");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
