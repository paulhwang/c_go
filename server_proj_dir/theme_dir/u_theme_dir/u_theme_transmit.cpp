/*
  Copyrights reserved
  Written by Paul Hwang
  File name: game_u_server_transmit.cpp
*/

#include "../../../phwang_dir/phwang.h"
#include "u_theme_class.h"

void UThemeClass::transmitFunction (char *data_val)
{
    this->logit("transmitFunction", data_val);

    if (!this->theTpTransferObject) {
        this->abend("transmitFunction", "null theTpTransferObject");
        return;
    }

    phwangTpTransmit(this->theTpTransferObject, data_val);
}
