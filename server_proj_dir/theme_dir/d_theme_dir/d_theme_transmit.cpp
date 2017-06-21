/*
  Copyrights reserved
  Written by Paul Hwang
  File name: d_theme_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "d_theme_class.h"

void DThemeClass::transmitFunction (char *data_val)
{
    this->debug(true, "transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        this->abend("transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
