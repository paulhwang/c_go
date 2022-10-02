/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_theme_class.h"

void DThemeClass::transmitFunction (char *data_val)
{
    phwangDebugS(true, "DThemeClass::transmitFunction", data_val);

    if (!this->portObject()) {
        phwangAbendS("DThemeClass::transmitFunction", "null portObject()");
        return;
    }

    phwangPortTransmit(this->portObject(), data_val);
}
